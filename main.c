
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "os/os.h"
#include "filetrans/filetrans.h"
#include "mqtt/mqtt.h"
#include "json/ujdecode.h"

#define BUFFER_SIZE 1024
#define SHORT_BUFFER_SIZE 256
#define PATH_MAX_LEN 128
#define MTID_MAX_LEN 32

#define METHOD_CALL_HEADER		"Method/Call/"
#define METHOD_RETURN_HEADER	"Method/Return/"
#define METHOD_STATUS_HEADER	"Method/Status/"
#define CALL_IDS_INDEX			(sizeof(METHOD_CALL_HEADER)-1)
#define STATUS_IDS_INDEX		(sizeof(METHOD_STATUS_HEADER)-1)
#define RETURN_MSG_FORMAT		"{\"@id\": \"messageID\", \"id\": \"%s\",\"return\": \"%s\"}"
#define STATUS_MSG_FORMAT		"{\"@id\": \"messageID\", \"id\": \"%s\",\"status\": \"%s\", \"progress\": %.0f}"


typedef struct MethodConf {
	FileTransProtocol fileTransProtocol;
	char *ids;
	char *methodId;
	char *address;
	char *user;
	char *password;
	char *source;
	char *destination;
	FileTransOperation operation;
} MethodConf;


typedef enum OpResult {
	OK = 0,
	WRONG_JSON,
	WRONG_ARGS,
	WRONG_PROTO,
	EXEC,
	NOT_EXEC,
} OpResult;


static const char *methodResults[] = {
	"OK",
	"WRONG_JSON",
	"WRONG_ARGS",
	"WRONG_PROTO",
	"EXECUTING",
	"NOT_EXECUTE",
};


static MethodConf *_conf;
static char _buffer[BUFFER_SIZE];
static Thread backgroundThread;


static inline MethodConf* getUploadConf()
{
	return (MethodConf *)calloc(1, sizeof(MethodConf));
}


void freeUploadConf()
{
	if (NULL != _conf)
	{
		free(_conf->ids);
		free(_conf->methodId);
		free(_conf->address);
		free(_conf->user);
		free(_conf->password);
		free(_conf->source);
		free(_conf->destination);
		free(_conf);
		_conf = NULL;
	}
}


size_t json2cs(UJObject input, char **output) {
	size_t ret = 0;
	wcstombs(_buffer, UJReadString(input, &ret), BUFFER_SIZE);
	*output = strdup(_buffer);
	return ret;
}


FileTransProtocol json2Protocol(UJObject input)
{
	const wchar_t *protocol = UJReadString(input, NULL);
	if (wcscmp(protocol, L"FTP") == 0)
	{
		return FTP;
	} else if (wcscmp(protocol, L"SFTP") == 0)
	{
		return SFTP;
	} else
	{
		return UNAVAILABLE;
	}
}


FileTransOperation json2Operation(UJObject input)
{
	const wchar_t *op = UJReadString(input, NULL);
	if (wcscmp(op, L"pull") == 0)
	{
		return PULL;
	} else if (wcscmp(op, L"push") == 0)
	{
		return PUSH;
	} else
	{
		return UNDEFINDED;
	}
}


void setUploadConf(UJObject mtid, UJObject protocol, UJObject address,
		UJObject user, UJObject pwd, UJObject src, UJObject dst, UJObject op)
{
	_conf->fileTransProtocol = json2Protocol(protocol);
	json2cs(mtid, &_conf->methodId);
	json2cs(address, &_conf->address);
	json2cs(user, &_conf->user);
	json2cs(pwd, &_conf->password);
	json2cs(src, &_conf->source);
	json2cs(dst, &_conf->destination);
	_conf->operation = json2Operation(op);
}


UJObject parseJSON(const char* input)
{
	size_t cbInput = strlen(input);
	void *state;

	UJObject obj = UJDecode(input, cbInput, NULL, &state);
	if (NULL == obj) printf("JSON Error: %s\n", UJGetError(state));

	UJFree(state);
	return obj;
}


void parseArgsToConf(UJObject input, const char *ids)
{
	const wchar_t *jsonKeys[] = {
		// L"@id",
		L"id",
		L"args",
	};
	UJObject
		// id,
		mtid,
		args;
	if (UJObjectUnpack(input, 2, "SO", jsonKeys, /*&id,*/ &mtid, &args) == 2)
	{
		// printf("mtid: %ls\n", UJReadString(mtid, NULL));
		const wchar_t *argsKeys[] = {
			L"protocol",
			L"address",
			L"user",
			L"password",
			L"source",
			L"destination",
			L"operation",
		};
    	UJObject
			protocol,
			address,
			user,
			password,
			source,
			destination,
			operation;

		if (UJObjectUnpack(args, 7, "SSSSSSS", argsKeys,
				&protocol, &address, &user, &password, &source, &destination, &operation) == 7)
		{
			_conf = getUploadConf();
			_conf->ids = strdup(ids);
			setUploadConf(mtid, protocol, address, user, password, source, destination, operation);
		}
	}
}


static inline void pubReturnMsg(const char *ids, const char *retMsg)
{
	char pubTopic[PATH_MAX_LEN];
	snprintf(pubTopic, PATH_MAX_LEN, METHOD_RETURN_HEADER"%s", ids);
	printf("PUB: %s\n", pubTopic);
	publish_msg(pubTopic, retMsg);
}


void returnMsg(OpResult oret, const char *methodId, const char *ids)
{
	snprintf(_buffer, BUFFER_SIZE, RETURN_MSG_FORMAT, methodId, methodResults[oret]);
	pubReturnMsg(ids, _buffer);
}


void statusMsg(const char *methodId, const char *ids)
{
	const char *status = methodResults[NOT_EXEC];
	double progressPercent = .0;
	char msgBuffer[SHORT_BUFFER_SIZE];

	if (_conf != NULL && strcmp(methodId, _conf->methodId) == 0)
	{
		progressPercent = getProgressPercent() * 100;
		status = methodResults[EXEC];
	}
	snprintf(msgBuffer, SHORT_BUFFER_SIZE, STATUS_MSG_FORMAT, methodId, status, progressPercent);
	pubReturnMsg(ids, msgBuffer);
}


static inline void action(int isPull)
{
	if (0 != setupServ(_conf->address, _conf->user, _conf->password, _conf->fileTransProtocol))
	{
		returnMsg(WRONG_PROTO, _conf->methodId, _conf->ids);
		return;
	}
	(isPull ? uploadFile : downloadFile)(_conf->source, _conf->destination);
	cleanupServ();
	printf("%s %s finished: %s -> %s\n", isPull ? "pull" : "push",
		_conf->methodId, _conf->source, _conf->destination);
	returnMsg(OK, _conf->methodId, _conf->ids);
}


void* fileOps(void *arg)
{
	switch (_conf->operation)
	{
	case PULL:
		action(true);
		break;
	case PUSH:
		action(false);
		break;
	default:
		printf("operation not supported.\n");
		break;
	}
	freeUploadConf();
	return NULL;
}


OpResult handleMethodCall(const struct mosquitto_message *msg)
{
	UJObject json = parseJSON((char *)msg->payload);
	if (NULL != json)
	{
		if (NULL != _conf)
		{
			ThreadJoin(backgroundThread, NULL);
		}
		parseArgsToConf(json, msg->topic+CALL_IDS_INDEX);
		if (NULL != _conf)
		{
			ThreadCreate(&backgroundThread, NULL, fileOps, NULL);
		} else {
			return WRONG_ARGS;
		}
	} else {
		return WRONG_JSON;
	}
	return OK;
}


OpResult handleMethodStatus(const struct mosquitto_message *msg)
{
	UJObject json = parseJSON((char *)msg->payload);
	if (NULL != json)
	{
		const wchar_t *jsonKeys[] = { L"id" };
		UJObject mtid;
		if (UJObjectUnpack(json, 1, "S", jsonKeys, /*&id,*/ &mtid) == 1)
		{
			char mtidBuffer[MTID_MAX_LEN];
			wcstombs(mtidBuffer, UJReadString(mtid, NULL), MTID_MAX_LEN);
			statusMsg(mtidBuffer, msg->topic+STATUS_IDS_INDEX);
		} else {
			return WRONG_ARGS;
		}
	} else {
		return WRONG_JSON;
	}
	return OK;
}


static inline int check_prefix(const char *str, const char *pre)
{
	return strncmp(str, pre, strlen(pre)) == 0;
}


void on_mqtt_msg(struct mosquitto *mosq, void *obj, const struct mosquitto_message *msg)
{
	/* This blindly prints the payload, but the payload can be anything so take care. */
	printf("%d - received: %s %d %s\n", msg->mid, msg->topic, msg->qos, (char *)msg->payload);
	OpResult oret;
	if (check_prefix(msg->topic, METHOD_CALL_HEADER))
	{
		oret = handleMethodCall(msg);
		if (OK != oret)
		{
			returnMsg(oret, "-1", msg->topic+CALL_IDS_INDEX);
		}
	}
	else if (check_prefix(msg->topic, METHOD_STATUS_HEADER))
	{
		oret = handleMethodStatus(msg);
		if (OK != oret)
		{
			statusMsg("-1", msg->topic+STATUS_IDS_INDEX);
		}
	}
}


int setupMqtt()
{
	const char *topicsToSub[] = {
		METHOD_CALL_HEADER"DevID/ClientID",
		METHOD_STATUS_HEADER"DevID/ClientID",
	};
	return initMqttFileTrans("pi-ubt.local", 1883, 60, topicsToSub, 2, on_mqtt_msg);
}


int main(int argc, char *argv[])
{
	setupMqtt();
	return 0;
}

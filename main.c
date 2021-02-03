
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "os/os.h"
#ifdef _WIN32
#define sem_t HANDLE
#define sem_init(sem,pshare,max_count) ((*sem = CreateSemaphore(NULL, max_count, max_count, NULL))!=NULL?0:-1)
#define sem_post(sem) (ReleaseSemaphore(*sem,1,NULL)?0:-1)
#define sem_trywait(sem) (WaitForSingleObject(*sem, 0)==WAIT_OBJECT_0?0:-1)
#else
#include <semaphore.h>
#endif

#include "filetrans/filetrans.h"
#include "mqtt/mqtt.h"
#include "json/njdecode.h"

#define QUEUE_SIZE 8
#define MSG_BUFFER_SIZE 256
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
	Thread preJob;
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
	QUEUE_FULL,
} OpResult;


static const char *methodResults[] = {
	"OK",
	"WRONG_JSON",
	"WRONG_ARGS",
	"WRONG_PROTO",
	"EXECUTING",
	"NOT_EXECUTE",
	"QUEUE_FULL",
};


static MethodConf *_conf;
static Thread lastJob;
static sem_t queue;


static inline MethodConf* getMethodConf()
{
	return (MethodConf *)calloc(1, sizeof(MethodConf));
}


static inline void freeMethodConf()
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


static inline void json2cs(const NJObject input, char **output) {
	NJReadString(output, input);
}


void setMethodConf(MethodConf *conf, NJObject mtid, NJObject protocol, NJObject address,
		NJObject user, NJObject pwd, NJObject src, NJObject dst, NJObject op)
{
	char *proto, *opr;
	json2cs(mtid, &conf->methodId);
	json2cs(protocol, &proto);
	json2cs(address, &conf->address);
	json2cs(user, &conf->user);
	json2cs(pwd, &conf->password);
	json2cs(src, &conf->source);
	json2cs(dst, &conf->destination);
	json2cs(op, &opr);
	conf->fileTransProtocol = cs2Protocol(proto);
	conf->operation = cs2Operation(opr);
	free(proto);
	free(opr);
}


void printConf(MethodConf *conf)
{
	printf("config: \"%s,%s,%d,%d,%s,%s,%s,%s,%s\"\n",
			conf->ids, conf->methodId, conf->fileTransProtocol, conf->operation,
			conf->address, conf->user, conf->password, conf->source, conf->destination);
}


NJObject parseJSON(const char *input)
{
	NJObject obj = NJDecode(input);
	if (NULL == obj) printf("JSON format error.\n");
	return obj;
}


bool parseArgsToConf(NJObject json, MethodConf *conf)
{
	const char *jsonKeys[] = {
		// "@id",
		"id",
		"args",
	};
	NJObject
		// id,
		mtid,
		args;
	if (NJObjectUnpack(json, "SO", jsonKeys, /*&id,*/ &mtid, &args) == 2)
	{
		printf("got: mtid, args\n");
		const char *argsKeys[] = {
			"protocol",
			"address",
			"user",
			"password",
			"source",
			"destination",
			"operation",
		};
    	NJObject
			protocol,
			address,
			user,
			password,
			source,
			destination,
			operation;

		if (NJObjectUnpack(args, "SSSSSSS", argsKeys,
				&protocol, &address, &user, &password, &source, &destination, &operation) == 7)
		{
			setMethodConf(conf, mtid, protocol, address, user, password, source, destination, operation);
			return true;
		}
	}
	return false;
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
	static char returnMsgBuffer[MSG_BUFFER_SIZE];
	snprintf(returnMsgBuffer, MSG_BUFFER_SIZE, RETURN_MSG_FORMAT, methodId, methodResults[oret]);
	pubReturnMsg(ids, returnMsgBuffer);
}


void statusMsg(OpResult oret, const char *methodId, const char *ids)
{
	static char statusMsgBuffer[MSG_BUFFER_SIZE];
	const char *status = methodResults[oret];
	double progressPercent = .0;

	if (oret == NOT_EXEC && _conf != NULL && strcmp(methodId, _conf->methodId) == 0)
	{
		progressPercent = getProgressPercent() * 100;
		status = methodResults[EXEC];
	}
	snprintf(statusMsgBuffer, MSG_BUFFER_SIZE, STATUS_MSG_FORMAT, methodId, status, progressPercent);
	pubReturnMsg(ids, statusMsgBuffer);
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


static inline void fileOps()
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
}


void* backgroundJob(void *cur)
{
	if (NULL != _conf)
	{
		ThreadJoin(((MethodConf*)cur)->preJob, NULL);
	}
	_conf = cur;
	fileOps();
	freeMethodConf(&_conf);
	sem_post(&queue);
	return NULL;
}


OpResult handleMethodCall(const struct mosquitto_message *msg)
{
	OpResult ret;
	NJObject json = parseJSON((char *)msg->payload);
	if (NULL != json)
	{
		MethodConf *cur = getMethodConf();
		if (parseArgsToConf(json, cur))
		{
			cur->ids = strdup(msg->topic+CALL_IDS_INDEX);
			cur->preJob = lastJob;
			printConf(cur);
			ThreadCreate(&lastJob, NULL, backgroundJob, cur);
			ret = OK;
		} else {
			free(cur);
			ret = WRONG_ARGS;
		}
		NJFree(&json);
	} else {
		ret = WRONG_JSON;
	}
	return ret;
}


OpResult handleMethodStatus(const struct mosquitto_message *msg)
{
	OpResult ret;
	NJObject json = parseJSON((char *)msg->payload);
	if (NULL != json)
	{
		const char *jsonKeys[] = { "id" };
		NJObject mtid;
		if (NJObjectUnpack(json, "S", jsonKeys, /*&id,*/ &mtid) == 1)
		{
			char *mtidcs;
			json2cs(mtid, &mtidcs);
			statusMsg(NOT_EXEC, mtidcs, msg->topic+STATUS_IDS_INDEX);
			free(mtidcs);
			ret = OK;
		} else {
			ret = WRONG_ARGS;
		}
		NJFree(&json);
	} else {
		ret = WRONG_JSON;
	}
	return ret;
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
		if (0 == sem_trywait(&queue))
		{
			oret = handleMethodCall(msg);
			if (OK != oret)
			{
				returnMsg(oret, "-1", msg->topic+CALL_IDS_INDEX);
				sem_post(&queue);
			}
		}
		else
		{
			returnMsg(QUEUE_FULL, "-1", msg->topic+CALL_IDS_INDEX);
		}
	}
	else if (check_prefix(msg->topic, METHOD_STATUS_HEADER))
	{
		oret = handleMethodStatus(msg);
		if (OK != oret)
		{
			statusMsg(oret, "-1", msg->topic+STATUS_IDS_INDEX);
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
	sem_init(&queue, 0, QUEUE_SIZE);
	setupMqtt();
	return 0;
}

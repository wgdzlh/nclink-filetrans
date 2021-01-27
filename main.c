
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "filetrans/filetrans.h"
#include "mqtt/mqtt.h"
#include "json/ujdecode.h"

#define BUFFER_SIZE 40


typedef enum FileTransProtocol {
	FTP = 0,
	SFTP,
	UNAVAILABLE
} FileTransProtocol;


typedef enum FileTransOperation {
	PUSH = 0,
	PULL,
	ADD,
	DEL,
	LIST,
	UNDEFINDED
} FileTransOperation;

typedef struct UploadConf {
	FileTransProtocol fileTransProtocol;
	char *methodId;
	char *address;
	char *user;
	char *password;
	char *source;
	char *destination;
	FileTransOperation operation;
} UploadConf;


UJObject parseJSON(const char* input)
{
	size_t cbInput = strlen(input);
	void *state;

	UJObject obj = UJDecode(input, cbInput, NULL, &state);
	if (NULL == obj) printf("Error: %s\n", UJGetError(state));

	UJFree(state);
	return obj;
}


UploadConf* getUploadConf()
{
	UploadConf *t = (UploadConf *)malloc(sizeof(UploadConf));
	t->methodId = (char *)malloc(BUFFER_SIZE);
	t->address = (char *)malloc(BUFFER_SIZE);
	t->user = (char *)malloc(BUFFER_SIZE);
	t->password = (char *)malloc(BUFFER_SIZE);
	t->source = (char *)malloc(BUFFER_SIZE);
	t->destination = (char *)malloc(BUFFER_SIZE);
	return t;
}


void freeUploadConf(UploadConf *t)
{
	if (NULL != t)
	{
		free(t->methodId);
		free(t->address);
		free(t->user);
		free(t->password);
		free(t->source);
		free(t->destination);
		free(t);
	}
}


void json2cs(UJObject input, char *output) {
	// sprintf(output, "%ls", UJReadString(input, NULL));
	wcstombs(output, UJReadString(input, NULL), BUFFER_SIZE);
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


void setUploadConf(UploadConf *t, UJObject protocol, UJObject address,
		UJObject user, UJObject pwd, UJObject src, UJObject dst, UJObject op)
{
	t->fileTransProtocol = json2Protocol(protocol);
	json2cs(address, t->address);
	json2cs(user, t->user);
	json2cs(pwd, t->password);
	json2cs(src, t->source);
	json2cs(dst, t->destination);
	t->operation = json2Operation(op);
}


UploadConf* parseArgs(UJObject input)
{
	UploadConf *ret = NULL;
	const wchar_t *jsonKeys[] = {
		L"@id",
		L"id",
		L"args",
	};
	UJObject
		id,
		mtid,
		args;
	if (UJObjectUnpack(input, 3, "SSO", jsonKeys, &id, &mtid, &args) == 3)
	{
		printf("mtid: %ls\n", UJReadString(mtid, NULL));
		ret = getUploadConf();
		json2cs(mtid, ret->methodId);
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
			setUploadConf(ret, protocol, address, user, password, source, destination, operation);
		}
		else
		{
			freeUploadConf(ret);
			ret = NULL;
		}
	}
	return ret;
}


void on_mqtt_msg(struct mosquitto *mosq, void *obj, const struct mosquitto_message *msg)
{
	/* This blindly prints the payload, but the payload can be anything so take care. */
	printf("%d - received: %s %d %s\n", msg->mid, msg->topic, msg->qos, (char *)msg->payload);
	UJObject json = parseJSON((char *)msg->payload);
	if (NULL != json)
	{
		UploadConf *conf = parseArgs(json);
		if (NULL != conf)
		{
			switch (conf->operation)
			{
			case PULL:
				setupServ(conf->address, conf->user, conf->password);
				uploadFile(conf->source, conf->destination);
				cleanupServ();
				printf("pull %s finished: %s -> %s\n", conf->methodId, conf->source, conf->destination);
				char outMsg[BUFFER_SIZE*2];
				sprintf(outMsg, "{\"@id\": \"messageID\", \"id\": \"%s\",\"return\": \"OK\"}", conf->methodId);
				const char *ids = msg->topic + 12;
				char buff[BUFFER_SIZE];
				sprintf(buff, "Method/Return/%s", ids);
				printf("%s\n", buff);
				publish_msg(buff, outMsg);
				break;
			case PUSH:
				setupServ(conf->address, conf->user, conf->password);
				downloadFile(conf->source, conf->destination);
				printf("push finished: %s -> %s\n", conf->source, conf->destination);
				cleanupServ();
				break;
			default:
				printf("operation not supported.\n");
				break;
			}
			freeUploadConf(conf);
		}
	}
}


int setupMqtt()
{
	const char *topicsToSub[] = {
		"Method/Call/DevID/ClientID",
	};
	return initMqttFileTrans("pi-ubt.local", 1883, 60, topicsToSub, 1, on_mqtt_msg);
}


int main(int argc, char *argv[])
{
	setupMqtt();
	return 0;
}

#ifndef __MQTT_H__
#define __MQTT_H__

#include "mosq/mosquitto.h"
#ifdef __cplusplus
extern "C" {
#endif

int initMqttFileTrans(const char *brokerAddress, const int port, const int keepalive,
    const char *topics[], const size_t numTopics, void (*callback)(struct mosquitto *, void *, const struct mosquitto_message *));
void publish_msg(const char *topic, const char *payload);
int testMqtt();

#ifdef __cplusplus
}
#endif

#endif

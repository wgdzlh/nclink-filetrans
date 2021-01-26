/*!
 * @file mqtt.h
 * @brief Mqtt通讯相关接口
 * @note
 * @version V1.00
 * @date 2020/03/16
 * @author Wang Xiao
 * @copyright
 */

#ifndef __MQTT_H__
#define __MQTT_H__
///最大Topic字符串长度,含字符串结束符
#define MAX_TOPIC_LENGTH (128)
#define MAX_TOPIC_NUM (32)
#ifdef __cplusplus
extern "C" {
#endif

///Mqtt接收消息时的回调函数定义
typedef void MessageCallBack(const char *topic, void *payload, int payloadLength);

/**
 * @brief Mqtt连接函数
 * @param ip 服务器IP
 * @param port 服务器端口号
 * @param userId 用户名
 * @param password 密码
 * @param reconnectSec 重连间隔
 * @param callback 消息回调函数
 * @return 返回启动状态
 * -0成功
 * --1失败
*/
int MqttConnect(const char *ip, int port, const char *clientId, const char *userName, const char *password,
                int reconnectSec, MessageCallBack *callback);

/**
 * @brief Mqtt断开连接函数
*/
void MqttDisconnect();

/**
 * @brief Mqtt消息发送函数
 * @param topic 消息主题
 * @param payload 消息内容
 * @param size 消息内容字节数
 * @param qos 服务质量
 * @return 返回启动状态
 * -0成功
 * --1失败
*/
int MqttPublish(const char *topic, const unsigned char *payload, int size, int qos);

/**
 * @brief 添加订阅主题
 * @param topic 消息主题
 * @param qos 服务质量
 * @return 返回添加状态
 * -0成功
 * --1失败
*/
int MqttAddTopic(const char *topic, int qos);

/**
 * @brief 删除订阅主题
 * @return 返回删除状态
 * -0表示启动成功
 * --1表示启动失败
*/
int MqttRemoveTopic(const char *topic);

/**
 * @brief 删除全部订阅主题
 * @return 返回删除状态
 * -0表示启动成功
 * --1表示启动失败
*/
int MqttRemoveAllTopics();

/**
 * @brief 订阅添加的主题
 * @return 返回订阅状态
 * -0成功
 * --1失败
*/
int MqttSubscribeTopics();

#ifdef __cplusplus
}
#endif
#endif

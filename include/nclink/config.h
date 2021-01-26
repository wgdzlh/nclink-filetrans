/*!
 * @file config.h
 * @brief 协议相关编译配置项
 * @note
 * @version V1.00
 * @date 2020/03/23
 * @author Wang Xiao
 * @copyright
 */
#ifndef __CONFIG_H__
#define __CONFIG_H__

///启用参数检查
#define PARAMS_CHECK_ENABLE 1
///启用严格参数检查
#define STRICT_PARAMS_CHECK_ENABLE 1
///启用权限检查
#define PRIVILEGE_CHECK_ENABLE 1
///服务器重连间隔秒数
#define MQTT_RECONNECT_INTERVAL 3
///最大消息大小字节数
#define MAX_MESSAGE_SIZE (512*1024)
///采样消息缓冲区大小
#define SAMPLE_MESSAGE_BUFFER_SIZE (1024 * 1024 * 2)
///模型文件最大大小
#define MAX_MODEL_SIZE (128*1024)
///最大消息id长度
#define MAX_MID_LEN    (1024)
///最大消息设备id长度
#define MAX_GUID_LEN    (128)
///查询、设置消息中的最大请求项数
#define MAX_REQUEST_NUMBER    (64)
///查询、采样项中indexes字段最大项数
#define MAX_INDEX_NUMBER    (1024)
///查询、采样消息中keys字段最大项数
#define MAX_KEY_NUMBER        (1024)
///最大采样通道数
#define MAX_SAMPLE_NODE        (32)
///最大reason字段长度
#define MAX_ERR_LEN    (1024)
///模型结点路径缓冲区大小
#define PATH_BUFFER_SIZE (256*1024)
///最大数据结点数
#define MAX_NODE_NUMBER (2048)
///临时缓冲区大小，用于分配小块内存临时使用
#define TEMP_BUFFER_SIZE (1024*1024)
///解析JSON请求时使用的内存大小
#define REQUEST_JSON_HEAP_SIZE (1024*1024*8)
///解析模型JSON文件时使用的内存大小
#define MODEL_JSON_HEAP_SIZE (1024*1024*1)
///自动生成采样驱动
#define AUTO_CREATE_SAMPLE_DRIVER_ENABLE (1)
#endif

/*!
 * @file interface.h
 * @brief 协议栈入口
 * @note
 * @version V1.00
 * @date 2020/03/24
 * @author Wang Xiao
 * @copyright
 */
#ifndef _INTERFACE_H_
#define _INTERFACE_H_

#include "sample_manager.h"

#ifdef __cplusplus
extern "C" {
#endif

/**
 * @brief 协议栈初始化
 * @param sampleDataUploader 采样数据上传回调函数
 * @return 初始化状态
 *  -0 成功
 *  --1 失败
*/
int InterfaceInit(SampleDataUploader *sampleDataUploader);

/**
 * @brief 协议栈资源释放
*/
void InterfaceDeinit();

/**
 * @brief 获取设备ID函数
 * @return 设备ID字符串
*/
const char *Guid();

/**
 * @brief 获取注册消息字符串
 * @return 注册消息字符串
*/
const char *RegisterRequestMessage();

/**
 * @brief 获取版本校对消息字符串
 * @return 版本校对消息字符串
*/
const char *ProbeVersionMessage();

/**
 * @brief 模型查询函数
 * @return 模型查询响应消息
*/
const char *ProbeQuery();

/**
 * @brief 模型设置函数
 * @return 模型设置响应消息
*/
const char *ProbeSet(const char *message);

/**
 * @brief 查询函数
 * @return 查询响应消息
*/
const char *Query(const char *message);

/**
 * @brief 设置函数
 * @return 设置响应消息
*/
const char *Set(const char *message);

#ifdef __cplusplus
}
#endif
#endif

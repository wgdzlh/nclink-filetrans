/*!
 * @file driver.h
 * @brief 数据驱动相关函数
 * @note
 * @version V1.00
 * @date 2020/03/23
 * @author Wang Xiao
 * @copyright
 */
#ifndef __DRIVER_H__
#define __DRIVER_H__

#include "nclinkdef.h"
#include "model.h"
#include "default_sample_driver.h"

#ifdef __cplusplus
extern "C"{
#endif

/**
 * driver组件初始化
 * @return 初始化状态
 *  -0 成功
 *  --1 失败
 */
int DriverInit();

/**
 * driver组件资源释放
 */
void DriverDeinit();

/**
 * 设置指定path对应数据的驱动
 * @param [in] path 数据在模型中的路径
 * @param [in] dataDriver 数据的驱动
 * @return 设置状态
 *  -0 成功
 *  --1 失败
 * @note 本函数由driver实现者在设备初始化函数中调用
 */
int SetDataDriver(const char *path, DataDriver *dataDriver);

/**
 * 获取指定path对应数据的驱动
 * @param [in] path 数据在模型中的路径
 * @return 数据的驱动对象
 * @note 协议栈在设备初始化函数调用之后，会调用此函数
 */
DataDriver *GetDataDriver(const char *path);

/**
 * 设置指定采样通道的驱动
 * @param [in] sampleChannel 采样通道的id
 * @param [in] sampleDriver 采样通道的驱动
 * @return 设置状态
 *  -0 成功
 *  --1 失败
 * @note 本函数由driver实现者在设备初始化函数中调用
 */
int SetSampleDriver(const char *sampleChannel, SampleDriver *sampleDriver);

/**
 * 获取指定采样通道的驱动
 * @param [in] sampleChannel 采样通道的id
 * @return 采样通道的驱动对象
 * @note 协议栈在设备初始化函数调用之后，会调用此函数
 */
SampleDriver *GetSampleDriver(const char *sampleChannel);

/**
 * 设置指定采样通道的驱动为协议栈默认驱动
 * @param [in] sampleChannel 采样通道的id
 * @return 设置状态
 *  -0 成功
 *  --1 失败
 * @note 本函数由driver实现者在设备初始化函数中调用
 */
int SetDefaultSampleDriver(const char *sampleChannel);

/**
* 设置设备id
* @param [in] guid 设备id
* @return 设置状态
*  -0 成功
*  --1 失败
* @note 本函数由driver实现者在设备初始化函数中调用,若模型文件中已定义设备id,此函数设置的值不起作用
*/
int SetGuid(const char *guid);

/**
* 获取设备id
* @return 设备id
* @note 协议栈在设备初始化函数调用之后，会调用此函数
*/
const char *GetGuid();

/**
* 设备初始化
* @param [in] guid 设备id
* @return 设置状态
*  -0 成功
*  --1 失败
* @note 本函数由driver实现者在设备初始化函数中调用,若模型文件中已定义设备id,此函数设置的值不起作用
*/
extern int DeviceInit();

/**
* 设备资源释放函数
* @note driver实现者实现此函数,协议栈退出时会调用此函数
*/
extern void DeviceDeinit();

#ifdef __cplusplus
};
#endif
#endif

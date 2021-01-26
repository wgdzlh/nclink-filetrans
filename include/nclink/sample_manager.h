/*!
 * @file sample_manager.h
 * @brief NC-Link启动、初始化、交互、终止等功能
 * @note
 * @version V1.00
 * @date 2020/03/24
 * @author Wang Xiao
 * @copyright
 */
#ifndef __SAMPLE_MANAGER_H__
#define __SAMPLE_MANAGER_H__

#include "nclinkdef.h"

#ifdef __cplusplus
extern "C" {
#endif

///采样上传回调函数定义
typedef void SampleDataUploader(const char *sampleChannel, const char *sampleMessage);

/**
 * @brief 采样管理器初始化函数
 * @param [in]nodes 模型文件中的采样通道节点数组
 * @param [in]number 采样节点个数
 * @return 初始化状态
 *  -0 成功
 *  --1 失败
*/
int SampleManagerInit(SampleNode **nodes, unsigned int number,SampleDataUploader* sampleDataUploader);

/**
 * @brief 采样管理器启动函数    
 * @return 启动状态
 *  -0 成功
 *  --1 失败
*/
int SampleManagerStart();

/**
 * @brief 采样管理器停止函数
*/
void SampleManagerStop();

/**
 * @brief 采样管理器资源释放函数
*/
void SampleManagerDeinit();

#ifdef __cplusplus
}
#endif
#endif

/*!
 * @file model.h
 * @brief 提供给driver使用的模型信息获取接口
 * @note
 * @version V1.00
 * @date 2020/03/21
 * @author Wang Xiao
 * @copyright
 */
#ifndef __MODEL_H_
#define __MODEL_H_

#include "nclinkdef.h"

#ifdef __cplusplus
extern "C" {
#endif

/**
 * @brief 获取模型文件对象
 * @return 模型文件对象
 */
const RootNode *GetModel();

/**
 * @brief id对应的节点对象
 * @param [in] id 节点id
 * @return 节点对象
 */
const BaseNode *GetNodeOfId(const char *id);

/**
 * @brief id对应的节点路径
 * @param [in] id 节点id
 * @return 节点路径
 */
const char *GetPathOfId(const char *id);

/**
 * @brief 获取全部采样节点
 * @param [out] number 采样节点个数
 * @return 采样节点对象指针数组
 */
const SampleNode **GetSampleNodes(unsigned int *number);

#ifdef __cplusplus
};
#endif
#endif

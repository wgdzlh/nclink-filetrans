/*!
 * @file default_sample_driver.h
 * @brief 默认采样驱动
 * @note
 * @version V1.00
 * @date 2020/03/23
 * @author Wang Xiao
 * @copyright
 */
#ifndef __DEFAULT_SAMPLE_DRIVER_H_
#define __DEFAULT_SAMPLE_DRIVER_H_

#include "nclinkdef.h"

#ifdef __cplusplus
extern "C" {
#endif

/**
 * @brief 创建默认采样驱动
 * @param node 采样结点
 * @return 采样驱动对象
 */
SampleDriver *DefaultSampleDriverCreate(const SampleNode *node);

#ifdef __cplusplus
}
#endif
#endif

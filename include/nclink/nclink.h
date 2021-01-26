/*!
 * @file nclink.h
 * @brief NC-Link启动、初始化、交互、终止等功能
 * @note
 * @version V1.00
 * @date 2020/03/16
 * @author Wang Xiao
 * @copyright
 */

#ifndef _NCLINK_H_
#define _NCLINK_H_

#ifdef __cplusplus
extern "C" {
#endif

/**
 * @brief NC-Link模块启动函数
 * @return 返回启动状态
 * -0 成功
 * --1 失败
*/
int NCLinkStart();

/**
 * @brief NC-Link模块终止函数
*/
void NCLinkStop();

#ifdef __cplusplus
}
#endif
#endif

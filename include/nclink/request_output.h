/*!
 * @file request_output.h
 * @brief 用于接收数据接口传递回来的数据
 * @note
 * @version V1.00
 * @date 2020/03/24
 * @author Wang Xiao
 * @copyright
 */

#ifndef __REQUEST_OUTPUT_H__
#define __REQUEST_OUTPUT_H__

typedef void *RequestOutput;

#ifdef __cplusplus
extern "C" {
#endif

/**
 * @brief 创建输出对象
 * @param [in]buffer 输出对象的缓冲区
 * @param [in]size 缓冲区大小
 * @return 输出对象
 */
RequestOutput RequestOutputCreate(void *buffer, int size);

/**
 * @brief 重置输出对象
 * @param [in]output 输出对象
 * @return 状态
 *  -0 成功
 *  --1 失败
 */
int RequestOutputReset(RequestOutput output);

/**
 * @brief 添加值
 * @param [in]output 输出对象
 * @param [in]value 要添加的值
 * @return 状态
 *  -0 成功
 *  --1 失败
 */
int RequestOutputAdd(RequestOutput output, void *value);

/**
 * @brief 获取输出对象中值的个数
 * @param [in]output 输出对象
 * @return 状态
 *  -0 成功
 *  --1 失败
 */
int RequestOutputGetSize(RequestOutput output);

/**
 * @brief 新建整形数值
 * @param [in]output 输出对象
 * @param [in]value 整数数值
 * @return 状态
 *  -0 成功
 *  --1 失败
 */
void *RequestOutputNewInteger(RequestOutput output, long long value);

/**
 * @brief 新建浮点数值
 * @param [in]output 输出对象
 * @param [in]value 浮点数值
 * @return 状态
 *  -0 成功
 *  --1 失败
 */
void *RequestOutputNewFloat(RequestOutput output, double value);

/**
 * @brief 新建布尔数值
 * @param [in]output 输出对象
 * @param [in]value 布尔值
 * @return 状态
 *  -0 成功
 *  --1 失败
 */
void *RequestOutputNewBool(RequestOutput output, int value);

/**
 * @brief 新建字符串数值
 * @param [in]output 输出对象
 * @param [in]value 字符串值
 * @return 状态
 *  -0 成功
 *  --1 失败
 */
void *RequestOutputNewString(RequestOutput output, const char *value);

/**
 * @brief 新建数组
 * @param [in]output 输出对象
 * @param [in]size 数组大小
 * @return 状态
 *  -0 成功
 *  --1 失败
 */
void *RequestOutputNewArray(RequestOutput output, int size);

/**
 * @brief 新建链表
 * @param [in]output 输出对象
 * @return 状态
 *  -0 成功
 *  --1 失败
 */
void *RequestOutputNewList(RequestOutput output);

/**
 * @brief 新建键值对集合
 * @param [in]output 输出对象
 * @return 状态
 *  -0 成功
 *  --1 失败
 */
void *RequestOutputNewKVSet(RequestOutput output);

/**
 * @brief 新建UInt8型原始数据数组
 * @param [in]output 输出对象
 * @param [in]data 原始数据
 * @param [in]count 原始数据数值个数
 * @return 状态
 *  -0 成功
 *  --1 失败
 */
void *RequestOutputNewRawUInt8Array(RequestOutput output, unsigned char *data, int count);

/**
 * @brief 新建UInt16型原始数据数组
 * @param [in]output 输出对象
 * @param [in]data 原始数据
 * @param [in]count 原始数据数值个数
 * @return 状态
 *  -0 成功
 *  --1 失败
 */
void *RequestOutputNewRawUInt16Array(RequestOutput output, unsigned short *data, int count);

/**
 * @brief 新建UInt32型原始数据数组
 * @param [in]output 输出对象
 * @param [in]data 原始数据
 * @param [in]count 原始数据数值个数
 * @return 状态
 *  -0 成功
 *  --1 失败
 */
void *RequestOutputNewRawUInt32Array(RequestOutput output, unsigned int *data, int count);

/**
 * @brief 新建UInt64型原始数据数组
 * @param [in]output 输出对象
 * @param [in]data 原始数据
 * @param [in]count 原始数据数值个数
 * @return 状态
 *  -0 成功
 *  --1 失败
 */
void *RequestOutputNewRawUInt64Array(RequestOutput output, unsigned long long *data, int count);

/**
 * @brief 新建Int8型原始数据数组
 * @param [in]output 输出对象
 * @param [in]data 原始数据
 * @param [in]count 原始数据数值个数
 * @return 状态
 *  -0 成功
 *  --1 失败
 */
void *RequestOutputNewRawInt8Array(RequestOutput output, char *data, int count);

/**
 * @brief 新建Int16型原始数据数组
 * @param [in]output 输出对象
 * @param [in]data 原始数据
 * @param [in]count 原始数据数值个数
 * @return 状态
 *  -0 成功
 *  --1 失败
 */
void *RequestOutputNewRawInt16Array(RequestOutput output, short *data, int count);

/**
 * @brief 新建Int32型原始数据数组
 * @param [in]output 输出对象
 * @param [in]data 原始数据
 * @param [in]count 原始数据数值个数
 * @return 状态
 *  -0 成功
 *  --1 失败
 */
void *RequestOutputNewRawInt32Array(RequestOutput output, int *data, int count);

/**
 * @brief 新建Int64型原始数据数组
 * @param [in]output 输出对象
 * @param [in]data 原始数据
 * @param [in]count 原始数据数值个数
 * @return 状态
 *  -0 成功
 *  --1 失败
 */
void *RequestOutputNewRawInt64Array(RequestOutput output, long long *data, int count);

/**
 * @brief 新建Float32型原始数据数组
 * @param [in]output 输出对象
 * @param [in]data 原始数据
 * @param [in]count 原始数据数值个数
 * @return 状态
 *  -0 成功
 *  --1 失败
 */
void *RequestOutputNewRawFloat32Array(RequestOutput output, float *data, int count);

/**
 * @brief 新建Float64型原始数据数组
 * @param [in]output 输出对象
 * @param [in]data 原始数据
 * @param [in]count 原始数据数值个数
 * @return 状态
 *  -0 成功
 *  --1 失败
 */
void *RequestOutputNewRawFloat64Array(RequestOutput output, double *data, int count);

/**
* @brief 新建二进制数据对象
* @param [in]output 输出对象
* @param [in]data 二进制数据
* @param [in]count 二进制数据字节数
* @return 状态
*  -0 成功
*  --1 失败
*/
void *RequestOutputNewBinary(RequestOutput output, unsigned char *data, int count);

/**
 * @brief 向键值对集合中添加键值对
 * @param [in]output 输出对象
 * @param [in]keyValueSet 键值对集合对象
 * @param [in]key 键
 * @param [in]value 值
 * @return 状态
 *  -0 成功
 *  --1 失败
 */
int RequestOutputKVSetAdd(RequestOutput output, void *keyValueSet, const char *key, void *value);

/**
 * @brief 向数组中添加数值对象
 * @param [in]output 输出对象
 * @param [in]array 数组对象
 * @param [in]index 索引
 * @param [in]value 值
 * @return 状态
 *  -0 成功
 *  --1 失败
 */
int RequestOutputArraySet(RequestOutput output, void *array, int index, void *value);

/**
 * @brief 向链表末尾添数值对象
 * @param [in]output 输出对象
 * @param [in]list 数组对象
 * @param [in]value 值
 * @return 状态
 *  -0 成功
 *  --1 失败
 */
int RequestOutputListAdd(RequestOutput output, void *list, void *value);

/**
 * @brief 将输出对象输出到字符串
 * @param [in]output 输出对象
 * @param [in]buffer 字符串缓冲区
 * @param [in]bufferSize 缓冲区大小
 * @return 状态
 *  -0 成功
 *  --1 失败
 */
int RequestOutputWriteString(RequestOutput output, char *buffer, int bufferSize);

#ifdef __cplusplus
}
#endif

#endif

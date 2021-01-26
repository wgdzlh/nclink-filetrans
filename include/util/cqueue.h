/*!
 * @file cqueue.h
 * @brief 队列封装
 * @note
 * @version V1.00
 * @date 2020/03/23
 * @author Wang Xiao
 * @copyright
 */
#ifndef _CQUEUE_H_
#define _CQUEUE_H_

///队列存储的数值类型
typedef enum {
    Q_V_T_Int,
    Q_V_T_Long,
    Q_V_T_Float,
    Q_V_T_Double,
    Q_V_T_Pointer
} QueueValueType;

///队列中存储的值
typedef union {
    int intVal;
    long long longVal;
    float floatVal;
    double doubleVal;
    void *ptrVal;
} QueueValue;

///队列对象
typedef void* Queue;

/**
 * 创建队列
 * @param [in]size 队列大小
 * @return 队列对象
 */
Queue QueueCreate(int size);

/**
 * 向队列顶部压入数据
 * @param [in]queue 队列对象
 * @param [in]valueType 数据类型
 * @param [in]value 数据值
 * @return 状态
 *  -0 成功
 *  --1 失败
 */
int QueuePushValue(Queue queue, QueueValueType valueType,QueueValue value);

/**
 * 从队列顶部中弹出数据
 * @param [in]queue 队列对象
 * @param [out]valueType 数据类型
 * @param [out]value 数据值
 * @return 状态
 *  -0 成功
 *  --1 失败
 */
int QueuePopValue(Queue queue, QueueValueType* valueType, QueueValue* value);

/**
 * 获取队列中元素个数
 * @param [in]queue 队列对象
 * @return 元素个数
 */
int QueueGetNumber(Queue queue);

/**
 * 释放队列对象
 * @param [in]queue 队列对象
 */
void QueueDestroy(Queue queue);

#endif  // _CQUEUE_H_

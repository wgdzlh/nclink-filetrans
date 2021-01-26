/*!
 * @file cpool.h
 * @brief 对象池封装
 * @note
 * @version V1.00
 * @date 2020/03/23
 * @author Wang Xiao
 * @copyright
 */
#ifndef __CPOOL_H__
#define __CPOOL_H__

///对象池对象
typedef void *Pool;

/**
 * @brief 创建对象池
 * @param [in]poolSize 对象池大小
 * @param [in]objectSize 对象大小
 * @return 对象池对象
 */
Pool PoolCreate(int poolSize, int objectSize);

/**
 * @brief 从对象池获取空闲对象
 * @param [in]pool 对象池对象
 * @return 获取的对象指针
 */
void *PoolGetObject(Pool pool);

/**
 * @brief 返还从对象池获取的对象
 * @param [in]pool 对象池对象
 * @return 状态
 *  -0 成功
 *  --1 失败
 */
int PoolReturnObject(Pool pool, void *object);


/**
 * @brief 释放对象池对象
 * @param [in]pool 对象池对象
 */
void PoolDestroy(Pool pool);

#endif
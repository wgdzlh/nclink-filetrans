/*!
 * @file chash.h
 * @brief hash表封装
 * @note
 * @version V1.00
 * @date 2020/03/16
 * @author Wang Xiao
 * @copyright
 */
#ifndef __CHASH_H__
#define __CHASH_H__

#include <stdlib.h>
#include <string.h>
#include <stdio.h>

#ifdef __cplusplus
extern "C" {
#endif

///hash表中的值类型
typedef enum {
    M_V_T_Int,
    M_V_T_Long,
    M_V_T_Float,
    M_V_T_Double,
    M_V_T_Pointer
} HashMapValueType;

///hash表中存储数值
typedef union {
    int intVal;
    long long longVal;
    float floatVal;
    double doubleVal;
    void *ptrVal;
} HashMapValue;

#define LEVEL0_SIZE (8)
#define LEVEL1_SIZE (8)
#define LEVEL2_SIZE (8)
#define LEVEL3_SIZE (8)
///存储的数据类型
///内部节点结构
typedef struct _Node
{
    struct _Node *next;
    struct _Node *prev;
    struct _Node *nextVal;
    struct _Node *prevVal;
    char *key;                  ///节点对应的key
    HashMapValueType type;      ///节点存储的数据类型
    HashMapValue value;         ///存储的值
} Node;
///HashMap数据结构
typedef struct _InnerHashMap
{
    Node *_map[LEVEL0_SIZE][LEVEL1_SIZE][LEVEL2_SIZE][LEVEL3_SIZE];
    Node *nodes;
} *InnerHashMap;
///hash表对象
typedef InnerHashMap HashMap;

/**
 * @brief 创建hash表对象
 * @return hash表对象
 */
HashMap HashMapCreate();

/**
 * @brief 释放hash表对象
 * @param [in] map hash表对象
 */
void HashMapDestroy(HashMap map);

/**
 * @brief 设置数值
 * @param [in] map hash表对象
 * @param [in] key 数据的key
 * @param [in] valueType 数值类型
 * @param [in] hashMapValue 数值
 * @return 设置状态
 *  -0 成功
 *  --1 失败
 */
int HashMapSetValue(HashMap map, const char *key, HashMapValueType valueType, HashMapValue value);

/**
 * 获取指定key对应的值
 * @param innerHashMap hash表对象
 * @param key 数据的key
 * @param valueType 存储的数据类型
 * @param value 数据指针
 * @return 获取状态
 *  -0 成功
 *  --1 失败
 */
int HashMapGetValue(HashMap innerHashMap, const char *key, HashMapValueType *valueType, HashMapValue *value);

/**
 * 删除指定key对应的值
 * @param innerHashMap hash表结构指针
 * @param key 数据的key
 * @return 删除状态
 *  -0 成功
 *  --1 失败
 */
int HashMapDelete(HashMap hashMap, const char *key);

#ifdef __cplusplus
}
#endif
#endif

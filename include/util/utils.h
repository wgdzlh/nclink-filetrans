/*!
 * @file utils.h
 * @brief 一些工具函数的封装
 * @note
 * @version V1.00
 * @date 2020/03/23
 * @author Wang Xiao
 * @copyright
 */
#ifndef __UTILS_H__
#define __UTILS_H__

#include <stdarg.h>
#include <stdio.h>
#include <string.h>
#include "json/ujdecode.h"
#include "iconv/iconv.h"

#define LOGGER_TAG "UTILS"
#include "log/logger.h"
typedef enum
{
    False,
    True
} Bool;

#define ENTER LOG_V("ENTER %s", __FUNCTION__)
#define RETURN LOG_V("LEAVE %s",__FUNCTION__);return;
#define RETURN_VAL(ret) do{LOG_V("LEAVE %s %d", __FUNCTION__, ret);return (ret);}while(0)

///字符串编码表
static unsigned char EncodeTable[256][2] = {
        {'0', '0'}, {'0', '1'}, {'0', '2'}, {'0', '3'}, {'0', '4'}, {'0', '5'}, {'0', '6'}, {'0', '7'}, {'0', '8'}, {'0', '9'}, {'0', 'A'}, {'0', 'B'}, {'0', 'C'}, {'0', 'D'}, {'0', 'E'}, {'0', 'F'},
        {'1', '0'}, {'1', '1'}, {'1', '2'}, {'1', '3'}, {'1', '4'}, {'1', '5'}, {'1', '6'}, {'1', '7'}, {'1', '8'}, {'1', '9'}, {'1', 'A'}, {'1', 'B'}, {'1', 'C'}, {'1', 'D'}, {'1', 'E'}, {'1', 'F'},
        {'2', '0'}, {'2', '1'}, {'2', '2'}, {'2', '3'}, {'2', '4'}, {'2', '5'}, {'2', '6'}, {'2', '7'}, {'2', '8'}, {'2', '9'}, {'2', 'A'}, {'2', 'B'}, {'2', 'C'}, {'2', 'D'}, {'2', 'E'}, {'2', 'F'},
        {'3', '0'}, {'3', '1'}, {'3', '2'}, {'3', '3'}, {'3', '4'}, {'3', '5'}, {'3', '6'}, {'3', '7'}, {'3', '8'}, {'3', '9'}, {'3', 'A'}, {'3', 'B'}, {'3', 'C'}, {'3', 'D'}, {'3', 'E'}, {'3', 'F'},
        {'4', '0'}, {'4', '1'}, {'4', '2'}, {'4', '3'}, {'4', '4'}, {'4', '5'}, {'4', '6'}, {'4', '7'}, {'4', '8'}, {'4', '9'}, {'4', 'A'}, {'4', 'B'}, {'4', 'C'}, {'4', 'D'}, {'4', 'E'}, {'4', 'F'},
        {'5', '0'}, {'5', '1'}, {'5', '2'}, {'5', '3'}, {'5', '4'}, {'5', '5'}, {'5', '6'}, {'5', '7'}, {'5', '8'}, {'5', '9'}, {'5', 'A'}, {'5', 'B'}, {'5', 'C'}, {'5', 'D'}, {'5', 'E'}, {'5', 'F'},
        {'6', '0'}, {'6', '1'}, {'6', '2'}, {'6', '3'}, {'6', '4'}, {'6', '5'}, {'6', '6'}, {'6', '7'}, {'6', '8'}, {'6', '9'}, {'6', 'A'}, {'6', 'B'}, {'6', 'C'}, {'6', 'D'}, {'6', 'E'}, {'6', 'F'},
        {'7', '0'}, {'7', '1'}, {'7', '2'}, {'7', '3'}, {'7', '4'}, {'7', '5'}, {'7', '6'}, {'7', '7'}, {'7', '8'}, {'7', '9'}, {'7', 'A'}, {'7', 'B'}, {'7', 'C'}, {'7', 'D'}, {'7', 'E'}, {'7', 'F'},
        {'8', '0'}, {'8', '1'}, {'8', '2'}, {'8', '3'}, {'8', '4'}, {'8', '5'}, {'8', '6'}, {'8', '7'}, {'8', '8'}, {'8', '9'}, {'8', 'A'}, {'8', 'B'}, {'8', 'C'}, {'8', 'D'}, {'8', 'E'}, {'8', 'F'},
        {'9', '0'}, {'9', '1'}, {'9', '2'}, {'9', '3'}, {'9', '4'}, {'9', '5'}, {'9', '6'}, {'9', '7'}, {'9', '8'}, {'9', '9'}, {'9', 'A'}, {'9', 'B'}, {'9', 'C'}, {'9', 'D'}, {'9', 'E'}, {'9', 'F'},
        {'A', '0'}, {'A', '1'}, {'A', '2'}, {'A', '3'}, {'A', '4'}, {'A', '5'}, {'A', '6'}, {'A', '7'}, {'A', '8'}, {'A', '9'}, {'A', 'A'}, {'A', 'B'}, {'A', 'C'}, {'A', 'D'}, {'A', 'E'}, {'A', 'F'},
        {'B', '0'}, {'B', '1'}, {'B', '2'}, {'B', '3'}, {'B', '4'}, {'B', '5'}, {'B', '6'}, {'B', '7'}, {'B', '8'}, {'B', '9'}, {'B', 'A'}, {'B', 'B'}, {'B', 'C'}, {'B', 'D'}, {'B', 'E'}, {'B', 'F'},
        {'C', '0'}, {'C', '1'}, {'C', '2'}, {'C', '3'}, {'C', '4'}, {'C', '5'}, {'C', '6'}, {'C', '7'}, {'C', '8'}, {'C', '9'}, {'C', 'A'}, {'C', 'B'}, {'C', 'C'}, {'C', 'D'}, {'C', 'E'}, {'C', 'F'},
        {'D', '0'}, {'D', '1'}, {'D', '2'}, {'D', '3'}, {'D', '4'}, {'D', '5'}, {'D', '6'}, {'D', '7'}, {'D', '8'}, {'D', '9'}, {'D', 'A'}, {'D', 'B'}, {'D', 'C'}, {'D', 'D'}, {'D', 'E'}, {'D', 'F'},
        {'E', '0'}, {'E', '1'}, {'E', '2'}, {'E', '3'}, {'E', '4'}, {'E', '5'}, {'E', '6'}, {'E', '7'}, {'E', '8'}, {'E', '9'}, {'E', 'A'}, {'E', 'B'}, {'E', 'C'}, {'E', 'D'}, {'E', 'E'}, {'E', 'F'},
        {'F', '0'}, {'F', '1'}, {'F', '2'}, {'F', '3'}, {'F', '4'}, {'F', '5'}, {'F', '6'}, {'F', '7'}, {'F', '8'}, {'F', '9'}, {'F', 'A'}, {'F', 'B'}, {'F', 'C'}, {'F', 'D'}, {'F', 'E'}, {'F', 'F'}
};
///字符串解码表
static unsigned char DecodeTable[16][16] = {
        {0x00, 0x01, 0x02, 0x03, 0x04, 0x05, 0x06, 0x07, 0x08, 0x09, 0x0a, 0x0b, 0x0c, 0x0d, 0x0e, 0x0f},
        {0x10, 0x11, 0x12, 0x13, 0x14, 0x15, 0x16, 0x17, 0x18, 0x19, 0x1a, 0x1b, 0x1c, 0x1d, 0x1e, 0x1f},
        {0x20, 0x21, 0x22, 0x23, 0x24, 0x25, 0x26, 0x27, 0x28, 0x29, 0x2a, 0x2b, 0x2c, 0x2d, 0x2e, 0x2f},
        {0x30, 0x31, 0x32, 0x33, 0x34, 0x35, 0x36, 0x37, 0x38, 0x39, 0x3a, 0x3b, 0x3c, 0x3d, 0x3e, 0x3f},
        {0x40, 0x41, 0x42, 0x43, 0x44, 0x45, 0x46, 0x47, 0x48, 0x49, 0x4a, 0x4b, 0x4c, 0x4d, 0x4e, 0x4f},
        {0x50, 0x51, 0x52, 0x53, 0x54, 0x55, 0x56, 0x57, 0x58, 0x59, 0x5a, 0x5b, 0x5c, 0x5d, 0x5e, 0x5f},
        {0x60, 0x61, 0x62, 0x63, 0x64, 0x65, 0x66, 0x67, 0x68, 0x69, 0x6a, 0x6b, 0x6c, 0x6d, 0x6e, 0x6f},
        {0x70, 0x71, 0x72, 0x73, 0x74, 0x75, 0x76, 0x77, 0x78, 0x79, 0x7a, 0x7b, 0x7c, 0x7d, 0x7e, 0x7f},
        {0x80, 0x81, 0x82, 0x83, 0x84, 0x85, 0x86, 0x87, 0x88, 0x89, 0x8a, 0x8b, 0x8c, 0x8d, 0x8e, 0x8f},
        {0x90, 0x91, 0x92, 0x93, 0x94, 0x95, 0x96, 0x97, 0x98, 0x99, 0x9a, 0x9b, 0x9c, 0x9d, 0x9e, 0x9f},
        {0xa0, 0xa1, 0xa2, 0xa3, 0xa4, 0xa5, 0xa6, 0xa7, 0xa8, 0xa9, 0xaa, 0xab, 0xac, 0xad, 0xae, 0xaf},
        {0xb0, 0xb1, 0xb2, 0xb3, 0xb4, 0xb5, 0xb6, 0xb7, 0xb8, 0xb9, 0xba, 0xbb, 0xbc, 0xbd, 0xbe, 0xbf},
        {0xc0, 0xc1, 0xc2, 0xc3, 0xc4, 0xc5, 0xc6, 0xc7, 0xc8, 0xc9, 0xca, 0xcb, 0xcc, 0xcd, 0xce, 0xcf},
        {0xd0, 0xd1, 0xd2, 0xd3, 0xd4, 0xd5, 0xd6, 0xd7, 0xd8, 0xd9, 0xda, 0xdb, 0xdc, 0xdd, 0xde, 0xdf},
        {0xe0, 0xe1, 0xe2, 0xe3, 0xe4, 0xe5, 0xe6, 0xe7, 0xe8, 0xe9, 0xea, 0xeb, 0xec, 0xed, 0xee, 0xef},
        {0xf0, 0xf1, 0xf2, 0xf3, 0xf4, 0xf5, 0xf6, 0xf7, 0xf8, 0xf9, 0xfa, 0xfb, 0xfc, 0xfd, 0xfe, 0xff}
};

/**
 * @brief 编码转换
 * @param [in]srcCharset 输入编码
 * @param [in]toCharset 输出编码
 * @param [in]inBuffer 输入字符串
 * @param [in]inLength 输入字符串长度
 * @param [in/out]outBuffer 输出缓冲区
 * @param [in]outLength 输出缓冲区大小
 * @return 状态
 *  -0 成功
 *  --1 失败
 */
static inline int CodeConvert(const char *srcCharset, const char *toCharset, char *inBuffer, size_t inlen, char *outBuffer, size_t outLength)
{
    iconv_t cd = NULL;
    char **pin = &inBuffer;
    char **pout = &outBuffer;

    if (srcCharset == NULL || toCharset == NULL || inBuffer == NULL || outBuffer == NULL)
    {
        RETURN_VAL(-1);
    }
    cd = iconv_open(toCharset, srcCharset);
    if (cd == 0)
    {
        return 1;
    }
    if ((signed)iconv(cd, pin, &inlen, pout, &outLength) == -1)
    {
        return 1;
    }
    iconv_close(cd);
    RETURN_VAL(0);
}

/**
 * @brief 将字符串中的小写字母转换为大写
 * @param [in,out]str 输入字符串
 * @note 输入字符串会被覆盖
 */
static inline int UpperCaseString(char *str)
{
    int i = 0;
    if (str == NULL)
    {
        RETURN_VAL(-1);
    }
    while (str[i] != '\0')
    {
        if (str[i] >= 'a' && str[i] <= 'z')
        {
            str[i] -= 32;
        }
        i++;
    }
}

/**
 * @brief 将字符串中的大写字母转换为小写
 * @param [in,out]str 输入字符串
 * @note 输入字符串会被覆盖
 */
static inline int LowerCaseString(char *str)
{
    int i = 0;
    if (str == NULL)
    {
        RETURN_VAL(-1);
    }
    while (str[i] != '\0')
    {
        if (str[i] >= 'A' && str[i] <= 'Z')
        {
            str[i] += 32;
        }
        i++;
    }
}

/**
 * @brief 统计字符串行数
 * @param [in,out]str 输入字符串
 */
static inline int RowNumberOfString(char *src)
{
    int i = 0;
    int row = 0;
    if (src == NULL)
    {
        RETURN_VAL(-1);
    }
    while (src[i] != '\0')
    {
        if (src[i] == '\n')
        {
            if (row != 0
                && src[i - 1] < 0)
            {
                continue;
            }
            row++;
        }
    }
    return row;
}

/**
 * @brief 字节数组解码
 * @param [in,out]dst 输出缓冲区
 * @param [in]dstSize 输出缓冲区大小
 * @param [in]src 源字节数组
 * @param [in]srcSize 源字节数组大小
 * @return 调用状态
 *  -0 成功
 *  --1 失败
 */
static inline int DecodeBytes(unsigned char *dst, int dstSize, const unsigned char *src, int srcSize)
{
    char cl = 0;
    char cr = 0;
    int i = 0;
    if (dst == NULL || src == NULL)
    {
        RETURN_VAL(-1);
    }
    if (srcSize <= 0)
    {
        RETURN_VAL(-1);
    }
    if (dstSize < srcSize / 2)
    {
        RETURN_VAL(-1);
    }
    while (i < srcSize / 2)
    {
        if (src[2 * i] < '0'
            || src[2 * i] > 'F'
            || (src[2 * i] < 'A' && src[i * 2] > '9'))
        {
            RETURN_VAL(-1);
        }
        if (src[2 * i + 1] < '0'
            || src[2 * i + 1] > 'F'
            || (src[2 * i + 1] < 'A' && src[i * 2 + 1] > '9'))
        {
            RETURN_VAL(-1);
        }
        cl = src[2 * i] <= '9' ? (src[2 * i] - '0') : (src[2 * i] - 'A' + 10);
        cr = src[2 * i + 1] <= '9' ? (src[2 * i + 1] - '0') : (src[2 * i + 1] - 'A' + 10);
        dst[i] = DecodeTable[cl][cr];
        i++;
    }
    RETURN_VAL(0);
}

/**
 * @brief 字节数组编码
 * @param [in,out]dst 输出缓冲区
 * @param [in]dstSize 输出缓冲区大小
 * @param [in]src 源字节数组
 * @param [in]srcSize 源字节数组大小
 * @return 调用状态
 *  -0 成功
 *  --1 失败
 */
static inline int EncodeBytes(unsigned char *dst, int dstSize, const unsigned char *src, int srcSize)
{
    int i = 0;
    if (dst == NULL || src == NULL)
    {
        RETURN_VAL(-1);
    }
    if (srcSize <= 0)
    {
        RETURN_VAL(-1);
    }
    if (dstSize < srcSize * 2)
    {
        RETURN_VAL(-1);
    }
    while (i < srcSize)
    {
        dst[2 * i] = EncodeTable[src[i]][0];
        dst[2 * i + 1] = EncodeTable[src[i]][1];
        i++;
    }
}

/**
 * @brief 字符串编码
 * @param [in,out]dst 输出缓冲区
 * @param [in]dstSize 输出缓冲区大小
 * @param [in]src 源字节数组
 * @param [in]srcSize 源字节数组大小
 * @return 调用状态
 *  -0 成功
 *  --1 失败
 */
static inline int EncodeString(char *dst, int dstSize, const char *src)
{
    int i = 0;
    if (dst == NULL || src == NULL)
    {
        RETURN_VAL(-1);
    }
    while (src[i] != '\0')
    {
        if (dstSize < i * 2 + 1)
        {
            RETURN_VAL(-1);
        }
        dst[2 * i] = EncodeTable[src[i]][0];
        dst[2 * i + 1] = EncodeTable[src[i]][1];
        i++;
    }
    dst[2 * i] = '\0';
}

/**
 * @brief 字符串解码
 * @param [in,out]dst 输出缓冲区
 * @param [in]dstSize 输出缓冲区大小
 * @param [in]src 源字节数组
 * @param [in]srcSize 源字节数组大小
 * @return 调用状态
 *  -0 成功
 *  --1 失败
 */
static inline int DecodeString(char *dst, int dstSize, const char *src)
{
    char cl = 0;
    char cr = 0;
    int i = 0;
    if (dst == NULL || src == NULL)
    {
        RETURN_VAL(-1);
    }
    while (src[2 * i] != '\0')
    {
        if (dstSize < i + 1)
        {
            RETURN_VAL(-1);
        }
        if (src[2 * i + 1] == '\0')
        {
            RETURN_VAL(-1);
        }
        if (src[2 * i] < '0'
            || src[2 * i] > 'F'
            || (src[2 * i] < 'A' && src[i * 2] > '9'))
        {
            RETURN_VAL(-1);
        }
        if (src[2 * i + 1] < '0'
            || src[2 * i + 1] > 'F'
            || (src[2 * i + 1] < 'A' && src[i * 2 + 1] > '9'))
        {
            RETURN_VAL(-1);
        }
        if (src[2 * i] <= '9')
        {
            cl = (src[2 * i] - '0');
        } else
        {
            cl = (src[2 * i] - 'A' + 10);
        }
        if (src[2 * i + 1] <= '9')
        {
            cr = (src[2 * i + 1] - '0');
        } else
        {
            cr = (src[2 * i + 1] - 'A' + 10);
        }
        dst[i] = (char) DecodeTable[cl][cr];
        i++;
    }

    dst[i] = '\0';

    RETURN_VAL(0);
}

/**
 * @brief 字符串拷贝
 * @param [in,out]dst 输出字符串
 * @param [in]src 源字符串
 * @param [in]maxSize 输出缓冲区大小
 * @return 状态
 *  -0 成功
 *  --1 失败
 */
static inline int StringCopy(char *dst, const char *src, int maxSize)
{
    int i = 0;
    if (maxSize <= 0 || dst == NULL || src == NULL)
    {
        RETURN_VAL(-1);
    }
    while (src[i] != '\0' && i < maxSize - 1)
    {
        dst[i] = src[i];
        i++;
    }
    dst[i] = '\0';
    RETURN_VAL(0);
}

/**
 * @brief 字符串前缀判断
 * @param [in]src 需要判断的字符串
 * @param [in]prefix 前缀字符串
 * @return 状态
 *  -0 字符串以指定前缀开始
 *  --1 字符串不以指定前缀开始
 */
static inline int StringStartWith(const char *src, const char *prefix)
{
    int i = 0;
    while (prefix[i] != '\0')
    {
        if (src[i] == '\0')
        {
            RETURN_VAL(-1);
        }
        if (prefix[i] != src[i])
        {
            RETURN_VAL(-1);
        }
        i++;
    }
    RETURN_VAL(0);
}

/**
 * @brief 将JSON值转换成int
 * @param [in]value JSON值
 * @param [in,out]out int值
 * @return 状态
 *  -0 成功
 *  --1 失败
 */
static inline int JSONValueAsInt(UJObject value, int *out)
{
    if (!UJIsInteger(value))
    {
        RETURN_VAL(-1);
    }
    *out = UJNumericInt(value);
    RETURN_VAL(0);
}

/**
 * @brief 将JSON值转换成int数组
 * @param [in]value JSON值
 * @param [in]num 数组大小
 * @param [in,out]out int数组
 * @return 状态
 *  -0 成功
 *  --1 失败
 */
static inline int JSONValueAsIntArray(const UJObject value, int num, int *out)
{
    void *iter = NULL;
    UJObject v = NULL;
    int i;
    if (!UJIsArray(value))
    {
        RETURN_VAL(-1);
    }
    iter = UJBeginArray(value);
    if (iter == NULL)
    {
        RETURN_VAL(-1);
    }
    i = 0;
    while (UJIterArray(&iter, &v) != 0)
    {
        if (i >= num)
        {
            RETURN_VAL(-1);
        }
        if (JSONValueAsInt(v, out + i) != 0)
        {
            RETURN_VAL(-1);
        }
        i++;
    }
    if (i != num)
    {
        RETURN_VAL(-1);
    }
    RETURN_VAL(0);
}

/**
 * @brief 将JSON值转换成JSON对象数组
 * @param [in]value JSON值
 * @param [in]num 数组大小
 * @param [in,out]out JSON数组
 * @return 状态
 *  -0 成功
 *  --1 失败
 */
static inline int JSONValueAsArray(const UJObject value, int num, void **out)
{
    void *iter = NULL;
    UJObject v = NULL;
    int i = 0;
    if (!UJIsArray(value))
    {
        RETURN_VAL(-1);
    }
    iter = UJBeginArray(value);
    if (iter == NULL)
    {
        RETURN_VAL(-1);
    }
    i = 0;
    while (UJIterArray(&iter, &v) != 0)
    {
        if (i >= num)
        {
            RETURN_VAL(-1);
        }
        *(out + i) = v;
    }
    RETURN_VAL(0);
}

/**
 * @brief 将JSON值转换成double
 * @param [in]value JSON值
 * @param [in,out]out double值
 * @return 状态
 *  -0 成功
 *  --1 失败
 */
static inline int JSONValueAsDouble(const UJObject value, double *out)
{
    if (!UJIsDouble(value) && !UJIsInteger(value))
    {
        RETURN_VAL(-1);
    }
    *out = UJNumericFloat(value);
    RETURN_VAL(0);
}

/**
 * @brief 将JSON值转换成double数组
 * @param [in]value JSON值
 * @param [in]num 数组大小
 * @param [in,out]out double数组
 * @return 状态
 *  -0 成功
 *  --1 失败
 */
static inline int JSONValueAsFloatArray(const UJObject value, int num, double *out)
{
    void *iter = NULL;
    UJObject v = NULL;
    int i = 0;
    if (!UJIsArray(value))
    {
        RETURN_VAL(-1);
    }
    iter = UJBeginArray(value);
    if (iter == NULL)
    {
        RETURN_VAL(-1);
    }
    i = 0;
    while (UJIterArray(&iter, &v) != 0)
    {
        if (i >= num)
        {
            RETURN_VAL(-1);
        }
        if (JSONValueAsDouble(v, out + i) != 0)
        {
            RETURN_VAL(-1);
        }
        i++;
    }
    RETURN_VAL(0);
}

/**
 * @brief 将JSON值转换成long long值
 * @param [in]value JSON值
 * @param [in,out]out long long值
 * @return 状态
 *  -0 成功
 *  --1 失败
 */
static inline int JSONValueAsLong(const UJObject value, long long *out)
{
    if (!UJIsInteger(value))
    {
        RETURN_VAL(-1);
    }
    *out = UJNumericInt(value);
    RETURN_VAL(0);
}

/**
 * @brief 将JSON值转换成字符串
 * @param [in]value JSON值
 * @param [in,out]out 字符串值
 * @return 状态
 *  -0 成功
 *  --1 失败
 */
static inline int JSONValueAsString(const UJObject value, const char **out)
{
    size_t size = 0;
    if (!UJIsString(value))
    {
        RETURN_VAL(-1);
    }
    *out = UJReadString(value, &size);
    RETURN_VAL(0);
}

/**
 * @brief 字符串格式化输出
 * @param [in]buffer 缓冲区
 * @param [in]size 缓冲区大小
 * @param [in]format 格式化字符串
 * @return 实际输出字符串长度，或-1
 */
static inline int AppendFormatText(char *buffer, int size, const char *format, ...)
{
    int length = 0;
    va_list args;
            va_start(args, format);
    length = vsnprintf(buffer, size, format, args);
    if (length < 0 || length >= size)
    {
                va_end(args);
        RETURN_VAL(-1);
    }
            va_end(args);
    return length;
}

/**
 * @brief 字符串转JSON字符串
 * @param [in,out]dst 缓冲区
 * @param [in]dstSize 缓冲区大小
 * @param [in]src 源字符串
 * @return 状态
 *  -0 成功
 *  --1 失败
 */
static inline int CStringToJString(char *dst, int dstSize, const char *src)
{
    int i = 0;
    int j = 0;
    while (src[i] != '\0')
    {
        switch (src[i])
        {
            case '\\':
            case '\"':
                if (j + 2 >= dstSize)
                {
                    RETURN_VAL(-1);
                }
                dst[j++] = '\\';
                dst[j++] = src[i++];
                break;
            default:
                if (j + 1 >= dstSize)
                {
                    RETURN_VAL(-1);
                }
                dst[j++] = src[i++];
                break;
        }
    }
    dst[j] = '\0';
    return j;
}

/**
 * @brief 字符串大小,包含字符串结束符
 * @param [in]str 字符串
 * @return 字符串大小
 */
static inline int SizeOfString(const char *str)
{
    int size = 0;
    while (str[size] != '\0')
    {
        size++;
    }
    return size + 1;
}

/**
 * @brief 去除字符串开头和末尾的空白字符
 * @param [in]str 字符串
 */
static inline void Trim(char *str)
{
    int i = 0;
    int j = 0;
    int k = SizeOfString(str) - 2;
    if (k < 1)
    {
        RETURN;
    }
    for (i = 0; i < k - 1; i++)
    {
        if (str[i] > 32 || str[i] < 0)
        {
            break;
        }
    }
    j = i;
    for (i = k; i > j; i--)
    {
        if (str[i] > 32 || str[i] < 0)
        {
            break;
        }
    }
    k = i;
    for (i = j; i <= k; i++)
    {
        str[i - j] = str[i];
    }
    str[k + 1] = '\0';
}

/**
 * @brief 文件删除
 * @param [in]name 文件路径
 * @return 状态
 *  -0 成功
 *  --1 失败
 */
static inline int FileRemove(const char *name)
{
    return remove(name);
}

/**
 * @brief 文件拷贝
 * @param [in]src 源文件路径
 * @param [in]dst 目标文件路径
 * @return 状态
 *  -0 成功
 *  --1 失败
 */
static inline int FileCopy(const char *src, const char *dst)
{
    FILE *sfp = NULL;
    FILE *dfp = NULL;
    char buf[1024] = {0};
    size_t size = 0;
    if (src == NULL || dst == NULL)
    {
        RETURN_VAL(-1);
    }
    sfp = fopen(src, "rb");
    if (sfp == NULL)
    {
        RETURN_VAL(-1);
    }
    dfp = fopen(dst, "wb+");
    if (dfp == NULL)
    {
        RETURN_VAL(-1);
    }
    while ((size = fread(buf, 1, 1024, sfp)) > 0)
    {
        if (size != fwrite(buf, 1, size, dfp))
        {
            fclose(sfp);
            fclose(dfp);
            RETURN_VAL(-1);
        }
    }
    fclose(sfp);
    fclose(dfp);
    RETURN_VAL(0);
}

#endif

// Copyright 2019-2021 The jdh99 Authors. All rights reserved.
// 工具箱
// Authors: jdh99 <jdh821@163.com>

#include "tzbox.h"

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdarg.h>

// TZBoxConvert64bitToStr 将64位数转换为字符串
// 转换后的格式为:0x1234567812345678.会自动补0
const char* TZBoxConvert64bitToStr(uint64_t num) {
    static char str[32] = {0};
    memset(str, 0, 32);

    uint32_t high = num >> 32;
    uint32_t low = (uint32_t)num;
    TZBoxSprintf(str, "0x%08x%08x", high, low);
    return str;
}

// TZBoxMemcpyReverse 翻转复制.比如src为小端存储.可以转换为大端存储在dst中
void TZBoxMemcpyReverse(uint8_t* dst, uint8_t* src, int size) {
    for (int i = 0; i < size; i++) {
        dst[i] = src[size - 1 - i];
    }
}

// TZBoxChecksum 计算校验和.算法是累加
uint32_t TZBoxChecksum(uint8_t* bytes, int size) {
    uint32_t check = 0;
    for (int i = 0; i < size; i++) {
        check += bytes[i];
    }
    return check;
}

// TZBoxMacArrToStr MAC地址数组转字符串.转换后的格式示例4c:cc:6a:4d:ce:95
bool TZBoxMacArrToStr(uint8_t* mac, char* dst) {
    uint8_t *dp = mac;
    
    if (dst == NULL) {
        return false;
    }
    char str[3];
    for (int i = 0; i < 6; i++) {
        TZBoxSprintf(str, "%02x", *dp++);
        strcat(dst, str);
        if (dp < mac + 6) {
            strcat(dst, ":");
        }
    }

    return true;
}

// TZBoxMacStrToArr MAC地址字符串转数组.字符串格式示例格式示例4c:cc:6a:4d:ce:95
// 转换后的数组长度是6字节
bool TZBoxMacStrToArr(char* mac, uint8_t* dst) {
    char *macp;
    char *parseEnd;
    if (dst == NULL) {
        return false;
    }

    macp = mac;
    while (1) {
        *dst++ = (uint8_t)strtol(macp, &parseEnd, 16);
        if (*parseEnd == '\0') {
            break;
        }

        if (*parseEnd != ':' && *parseEnd != '\0') {
            return false;
        }
        macp = parseEnd + 1;
    }
    
    return true;
}

// TZBoxIPHexToStr 将16进制的IP地址转换为字符串
const char* TZBoxIPHexToStr(uint32_t ip) {
    static char str[16] = {0};
    memset(str, 0, 16);

    TZBoxSprintf(str, "%d.%d.%d.%d", (uint8_t)(ip >> 24), (uint8_t)(ip >> 16), 
        (uint8_t)(ip >> 8), (uint8_t)ip);
    return str;
}

// TZBoxHtons 2字节主机序转换为网络序
uint16_t TZBoxHtons(uint16_t n) {
    return (uint16_t)(((n & 0xff) << 8) | ((n & 0xff00) >> 8));
}

// TZBoxNtohs 2字节网络序转换为主机序
uint16_t TZBoxNtohs(uint16_t n) {
    return TZBoxHtons(n);
}

// TZBoxHtonl 4字节主机序转换为网络序
uint32_t TZBoxHtonl(uint32_t n) {
    return ((n & 0xff) << 24) |
        ((n & 0xff00) << 8) |
        ((n & 0xff0000UL) >> 8) |
        ((n & 0xff000000UL) >> 24);
}

// TZBoxNtohl 4字节网络序转换为主机序
uint32_t TZBoxNtohl(uint32_t n) {
    return TZBoxHtonl(n);
}

// TZBoxHtonll 8字节主机序转换为网络序
uint64_t TZBoxHtonll(uint64_t n) {
    return ((n & 0xff) << 56) |
        ((n & 0xff00) << 40) |
        ((n & 0xff0000) << 24) |
        ((n & 0xff000000) << 8) |
        ((n & 0xff00000000ULL) >> 8) |
        ((n & 0xff0000000000ULL) >> 24) |
        ((n & 0xff000000000000ULL) >> 40) |
        ((n & 0xff00000000000000ULL) >> 56);
}

// TZBoxNtohll 8字节网络序转换为主机序
uint64_t TZBoxNtohll(uint64_t n) {
    return TZBoxHtonll(n);
}

// TZBoxFilterFirstOrder 一阶滤波
// value是当前值.realValue是实时值.ratio是系数,从0开始,系数越大滤波效果越好
float TZBoxFilterFirstOrder(float value, float realValue, float ratio) {
    return (realValue + value * ratio) / (ratio + 1);
}

// TZBoxSprintf sprintf函数的替代函数,用于某些MCU中不调用printfa.o节约空间
// 注意本函数不能打印浮点数
int TZBoxSprintf(char *str, const char *format, ...) {
    va_list args;
    va_start(args, format);

    int count = 0;
    while (*format) {
        if (*format == '%') {
            format++;
            switch (*format) {
                case 'd': {
                    int num = va_arg(args, int);
                    char temp[20];
                    int i = 0;
                    int is_negative = 0;
                    int len = 0;

                    if (num < 0) {
                        is_negative = 1;
                        num = -num;
                    }

                    // 先计算整数转换为字符串后的长度
                    int temp_num = num;
                    do {
                        len++;
                        temp_num /= 10;
                    } while (temp_num);

                    // 考虑负号
                    if (is_negative) {
                        len++;
                    }

                    // 如果长度超过 20 字节，直接截取
                    if (len > 20) {
                        len = 20;
                        if (is_negative) {
                            temp[0] = '-';
                            i = 1;
                        }
                        for (; i < len; i++) {
                            temp[i] = '0';
                        }
                    } else {
                        // 正常转换整数为字符串
                        do {
                            temp[i++] = num % 10 + '0';
                            num /= 10;
                        } while (num);

                        if (is_negative) {
                            temp[i++] = '-';
                        }

                        // 反转字符串
                        int start = 0;
                        int end = i - 1;
                        while (start < end) {
                            char tmp = temp[start];
                            temp[start] = temp[end];
                            temp[end] = tmp;
                            start++;
                            end--;
                        }
                    }

                    // 将临时字符串复制到结果缓冲区
                    for (i = 0; i < len; i++) {
                        str[count++] = temp[i];
                    }
                    break;
                }
                case 's': {
                    char *s = va_arg(args, char *);
                    while (*s) {
                        str[count++] = *s++;
                    }
                    break;
                }
                case 'c': {
                    char c = (char)va_arg(args, int);
                    str[count++] = c;
                    break;
                }
                default:
                    str[count++] = '%';
                    str[count++] = *format;
                    break;
            }
        } else {
            str[count++] = *format;
        }
        format++;
    }
    str[count] = '\0';
    va_end(args);
    return count;
}

// TZBoxIIRFilter IIR一阶滤波
// value是当前值.realValue是实时值.ratio是系数,0-1之间,系数越小滤波效果越好
float TZBoxIIRFilter(float value, float realValue, float ratio) {
    return value + (realValue - value) * ratio;
}

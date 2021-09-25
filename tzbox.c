// Copyright 2019-2021 The jdh99 Authors. All rights reserved.
// 工具箱
// Authors: jdh99 <jdh821@163.com>

#include "tzbox.h"

#include <stdio.h>
#include <string.h>
#include <stdlib.h>

// TZBoxConvert64bitToStr 将64位数转换为字符串
// 转换后的格式为:0x1234567812345678.会自动补0
const char* TZBoxConvert64bitToStr(uint64_t num) {
    static char str[32] = {0};
    memset(str, 0, 32);

    uint32_t high = num >> 32;
    uint32_t low = (uint32_t)num;
    sprintf(str, "0x%08x%08x", high, low);
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
        sprintf(str, "%02x", *dp++);
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

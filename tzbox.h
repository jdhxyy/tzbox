// Copyright 2019-2021 The jdh99 Authors. All rights reserved.
// 工具箱
// Authors: jdh99 <jdh821@163.com>

#ifndef TZBOX_H
#define TZBOX_H

#include <stdint.h>
#include <stdbool.h>

// TZBoxConvert64bitToStr 将64位数转换为字符串
// 转换后的格式为:0x1234567812345678.会自动补0
const char* TZBoxConvert64bitToStr(uint64_t num);

// TZBoxMemcpyReverse 翻转复制.比如src为小端存储.可以转换为大端存储在dst中
void TZBoxMemcpyReverse(uint8_t* dst, uint8_t* src, int size);

// TZBoxChecksum 计算校验和.算法是累加
uint32_t TZBoxChecksum(uint8_t* bytes, int size);

// TZBoxMacArrToStr MAC地址数组转字符串.转换后的格式示例4c:cc:6a:4d:ce:95
bool TZBoxMacArrToStr(uint8_t* mac, char* dst);

// TZBoxMacStrToArr MAC地址字符串转数组.字符串格式示例格式示例4c:cc:6a:4d:ce:95
// 转换后的数组长度是6字节
bool TZBoxMacStrToArr(char* mac, uint8_t* dst);

// TZBoxHtons 2字节主机序转换为网络序
uint16_t TZBoxHtons(uint16_t n);

// TZBoxNtohs 2字节网络序转换为主机序
uint16_t TZBoxNtohs(uint16_t n);

// TZBoxHtonl 4字节主机序转换为网络序
uint32_t TZBoxHtonl(uint32_t n);

// TZBoxNtohl 4字节网络序转换为主机序
uint32_t TZBoxNtohl(uint32_t n);

// TZBoxHtonll 8字节主机序转换为网络序
uint64_t TZBoxHtonll(uint64_t n);

// TZBoxNtohll 8字节网络序转换为主机序
uint64_t TZBoxNtohll(uint64_t n);

#endif

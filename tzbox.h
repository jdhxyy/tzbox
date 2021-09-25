// Copyright 2019-2021 The jdh99 Authors. All rights reserved.
// ������
// Authors: jdh99 <jdh821@163.com>

#ifndef TZBOX_H
#define TZBOX_H

#include <stdint.h>
#include <stdbool.h>

// TZBoxConvert64bitToStr ��64λ��ת��Ϊ�ַ���
// ת����ĸ�ʽΪ:0x1234567812345678.���Զ���0
const char* TZBoxConvert64bitToStr(uint64_t num);

// TZBoxMemcpyReverse ��ת����.����srcΪС�˴洢.����ת��Ϊ��˴洢��dst��
void TZBoxMemcpyReverse(uint8_t* dst, uint8_t* src, int size);

// TZBoxChecksum ����У���.�㷨���ۼ�
uint32_t TZBoxChecksum(uint8_t* bytes, int size);

// TZBoxMacArrToStr MAC��ַ����ת�ַ���.ת����ĸ�ʽʾ��4c:cc:6a:4d:ce:95
bool TZBoxMacArrToStr(uint8_t* mac, char* dst);

// TZBoxMacStrToArr MAC��ַ�ַ���ת����.�ַ�����ʽʾ����ʽʾ��4c:cc:6a:4d:ce:95
// ת��������鳤����6�ֽ�
bool TZBoxMacStrToArr(char* mac, uint8_t* dst);

// TZBoxHtons 2�ֽ�������ת��Ϊ������
uint16_t TZBoxHtons(uint16_t n);

// TZBoxNtohs 2�ֽ�������ת��Ϊ������
uint16_t TZBoxNtohs(uint16_t n);

// TZBoxHtonl 4�ֽ�������ת��Ϊ������
uint32_t TZBoxHtonl(uint32_t n);

// TZBoxNtohl 4�ֽ�������ת��Ϊ������
uint32_t TZBoxNtohl(uint32_t n);

// TZBoxHtonll 8�ֽ�������ת��Ϊ������
uint64_t TZBoxHtonll(uint64_t n);

// TZBoxNtohll 8�ֽ�������ת��Ϊ������
uint64_t TZBoxNtohll(uint64_t n);

#endif

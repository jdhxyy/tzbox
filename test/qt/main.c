#include <stdio.h>
#include <string.h>

#include "tzbox.h"
#include "scunit.h"

static void case1(void);
static void case2(void);
static void case3(void);
static void case4(void);
static void case5(void);

int main() {
    ScunitLoad((ScunitPrintFunc)printf);
    ScunitAddSuite("test_tzbox");
    ScunitAddTest("case1", case1);
    ScunitAddTest("case2", case2);
    ScunitAddTest("case3", case3);
    ScunitAddTest("case4", case4);
    ScunitAddTest("case5", case5);
    return 0;
}

static void case1(void) {
    char str[32] = {0};
    TZBoxConvert64bitToStr(0x1234567878563412, str);
    ScunitAssert(strcmp(str, "0x1234567878563412") == 0, "1");

    TZBoxConvert64bitToStr(0x1234, str);
    ScunitAssert(strcmp(str, "0x0000000000001234") == 0, "2");
}

static void case2(void) {
    uint64_t num1 = 0x1122334455667788;
    uint64_t num2 = 0;
    TZBoxMemcpyReverse((uint8_t*)&num2, (uint8_t*)&num1, 8);
    ScunitAssert(num2 == 0x8877665544332211, "1");

    uint8_t arr1[3] = {1, 2, 3};
    uint8_t arr2[3] = {0};
    TZBoxMemcpyReverse(arr2, arr1, 3);
    ScunitAssert(arr2[0] == 3, "2");
    ScunitAssert(arr2[1] == 2, "2");
    ScunitAssert(arr2[2] == 1, "2");
}

static void case3(void) {
    uint8_t arr[3] = {1, 2, 3};
    uint32_t sum = TZBoxChecksum(arr, 3);
    ScunitAssert(sum == 6, "1");
}

static void case4(void) {
    uint8_t arr1[6] = {0x4c, 0xcc, 0x6a, 0x4d, 0xce, 0x95};
    char str[32] = {0};
    TZBoxMacArrToStr(arr1, str);
    ScunitAssert(strcmp(str, "4c:cc:6a:4d:ce:95") == 0, "1");

    uint8_t arr2[6] = {0};
    TZBoxMacStrToArr(str, arr2);
    ScunitAssert(memcmp(arr1, arr2, 6) == 0, "2");
}

static void case5(void) {
    ScunitAssert(TZBoxHtons(0x1234) == 0x3412, "Htons");
    ScunitAssert(TZBoxNtohs(0x3412) == 0x1234, "Ntohs");
    ScunitAssert(TZBoxHtonl(0x12345678) == 0x78563412, "Htonl");
    ScunitAssert(TZBoxNtohl(0x78563412) == 0x12345678, "Ntohl");
    ScunitAssert(TZBoxHtonll(0x1122334455667788) == 0x8877665544332211, "Htonll");
    ScunitAssert(TZBoxNtohll(0x8877665544332211) == 0x1122334455667788, "Ntohll");
}

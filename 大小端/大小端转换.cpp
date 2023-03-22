#include <iostream>
#include <type_traits>
#include <vector>
#include <string>
using namespace std;
// https://stackoverflow.com/questions/2182002/convert-big-endian-to-little-endian-in-c-without-using-provided-func
// 大端转换成小端
unsigned int InertToSmall(unsigned int num) {
    unsigned int res = num;
    unsigned char* ptr = (unsigned char*) &res;

    // ptr[0] = num;
    // ptr[1] = num >> 8;
    // ptr[2] = num >> 16;
    // ptr[3] = num >> 24;
    swap(ptr[0], ptr[3]);
    swap(ptr[1], ptr[2]);
    return res;
}

unsigned short InverToSmall(unsigned short num) {
    unsigned short res = num;
    unsigned char* ptr = (unsigned char*) &res;

    // ptr[0] = num;
    // ptr[1] = num >> 8;
    swap(ptr[0], ptr[1]);
    return res;
}
int main() {
    unsigned int big = 0x12345678;
    unsigned int small = InertToSmall(big) ;
    printf("0x%x\n", small);

    // usig
    unsigned short bigshort = 0x0001;
    unsigned short smallshort = InverToSmall(bigshort);
    printf("0x%x\n", smallshort);
    return 0;
}
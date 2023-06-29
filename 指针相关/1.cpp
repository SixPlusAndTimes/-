#include <cstdio>
#include <cstdlib>
// 函数指针的定义
char* func(int a) {
    char* something =(char*) malloc(8);
    for (int i = 0; i < 7; i++) {
        *(something + i) = 'a';
    }
    *(something + 8) = '\0';
    printf("%s\n", something);
    return something;
}
int main() {
    // 定义一个函数指针，它接收int变量，返回char指针
    char* (*p)(int)  = func;

    char* a = p(1);
    printf("%s\n", a);
}
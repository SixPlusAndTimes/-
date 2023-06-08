#include <cstddef>
#include <cstdlib>
#include <string.h>
#include <iostream>
void* my_memmmove(char* dest, char* src, size_t n) {
    char* ret = dest;

    if (dest <= src || dest >= src + n) { // 不发生重叠的情况, 从前往后拷贝
        while (n--) {
            *(dest++) = *(src++);
        }
    }else { // 发生重叠的情况，从后面往前面拷贝
        char* from = src + n - 1; // 注意这里的减一！
        char* to = dest + n - 1;
        while (n--) {
            *(to--) = *(from--); 
        }
    }
    return ret;
}

int main() {
    char buffer[12] = {'\0', '\0', '\0', 'a', 'b', 'c', 'd', '\0','\0','\0', '\0', '\0'};
    char* src = buffer + 3;
    printf("src = %s\n", src);

    char* dest = buffer + 5;
    my_memmmove(dest, src, 5);  
    printf("dest = %s\n", dest);
    printf("src = %s\n", src);
}
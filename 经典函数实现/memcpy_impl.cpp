#include <cstddef>
#include <cstdlib>
#include <string.h>
#include <iostream>
void* my_memcpy(char* dest, char* src, size_t n) {
    char* ret = dest;

    while (n--) {
        *(dest++) = *(src++);
    }
    return ret;
}

int main() {
    char buffer[10] = {'\0', '\0', '\0', 'a', 'b', 'c', 'd', '\0'};
    char* src = buffer + 3;
    printf("src = %s\n", src);

    char* dest = buffer + 5;
    my_memcpy(dest, src, 5); // 发生重叠, dest 在 src的后面，把结束符都覆盖掉了
    printf("overlap = %s\n", dest);
    printf("src = %s\n", src);
}
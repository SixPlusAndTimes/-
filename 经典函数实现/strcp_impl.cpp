#include <cstdlib>
#include <string.h>
#include <iostream>
char* my_strcpy(char* dest, char* src) {
    char* ret = dest;
    while (*dest == *src && *dest != '\0') {
        dest++;
        src++;
    }
    return ret;
}

int main() {
    char a[] = "asd";
    char *b = (char*)malloc(4);

    char* c = my_strcpy(b, a);
    printf("%s \n", c);

}
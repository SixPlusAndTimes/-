#include <iostream>
// https://stackoverflow.com/questions/66622217/what-if-i-use-d-instead-of-ld-in-c
int main () {
    short i = 65537; // 溢出，所以i = 1
    int j = i + 1; // j = 2
    printf("i=%d,j=%d\n", i, j); // i = 1, j = 2
}
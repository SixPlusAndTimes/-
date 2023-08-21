#include <stdio.h>
#define Invert16B(x)  (x & 0xff00 >> 8) | \
                       (x & 0x00ff << 8)
#define  Invert32B(x) (x & 0xff000000 >> 24) | \
                        (x & 0x00ff0000 >> 8) | \
                        (x & 0x0000ff00 << 8) | \
                        (x & 0x000000ff << 24)

int main() {
    short a = 0x1122;
    printf("a = %x, Invert16B(a) = %x\n", a, Invert16B(a));
    int b = 0x11223344;
    printf("b = %x, Invert32B(b) = %x\n", b, Invert32B(b));
}
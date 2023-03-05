#include <functional>
#include <iostream>
#include <unordered_map>
int main() {
    for (int i = 0; i < 100; i++) {
        printf("hash(%d) = %zu\n", i, std::hash<int>()(i));
    }
}
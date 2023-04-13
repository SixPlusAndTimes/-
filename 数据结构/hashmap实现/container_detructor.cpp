#include <iostream>
#include <vector>
class A {
    public:
    ~A() {
        std::cout << "A destructor\n";
    }
};

int main() {
    std::vector<A*> d;
    
    for (int i = 0; i < 10; i++) {
        d.push_back(new A());
    }

    for (int i = 0; i < 10; i++) {
        delete d[i];
        // d[i] = nullptr;
    }


    std::cout << 9 % (-4) << " " << (-9) % (-4);
}


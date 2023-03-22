#include <iostream>
using namespace std;
int main() {
    unsigned short a = 0x0001;
    unsigned char* aptr = (unsigned char*)&a;    
    if (aptr[0] == 0x01) {
        cout << "小端\n"; 
    }else {
        cout <<  "大端\n";
    }
    return 0;
}
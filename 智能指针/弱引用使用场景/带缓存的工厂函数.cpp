#include <cstdio>
#include <iostream>
#include <memory>
#include <vector>
#include <string>
#include <unordered_map>
using namespace std;
// class Object{

// };

// class ObjectA : public Object{

// };

// class ObjectB : public Object {

// };
// const static int Type_A = 0;
// const static int Type_B = 0;

// std::shared_ptr<Object> getObject(int type) {
//     static unordered_map<int, std::weak_ptr<Object>> cache;

//     std::shared_ptr<Object> ret = cache[type].lock();

//     if (!ret) {
//         if (type == Type_A) {
//             ret.reset(new ObjectA);
//         }else {
//             ret.reset(new  ObjectB);
//         }
//     }
//     cache[type] = ret;
//     return ret;
// }

class Widdet {
public:
    int ID = -1;
    Widdet(int id):ID(id) {
        std::cout << "construct Widdet id = " << id << std::endl;
    }
};

std::shared_ptr<Widdet>
getWidget(int id) {
    static unordered_map<int, std::weak_ptr<Widdet>> cache;

    std::shared_ptr<Widdet> ret = cache[id].lock();

    if (!ret) {
        ret.reset(new Widdet(id));
    }
    cache[id] = ret;
    return ret;
}
int main() {
    auto w1 = getWidget(0);
    auto w2 = getWidget(0);

    auto w3 = getWidget(1);
    
    auto w4 = getWidget(2);
    auto w5 = getWidget(2);
    return 0;
}
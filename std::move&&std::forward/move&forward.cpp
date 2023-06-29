#include <cstdio>
#include <type_traits>
#include <stdlib.h>
/* 使用模板推导和模板偏特化来取出引用特性 */ 
template <typename T>
struct RemoveRefrence {
    using Type = T;
};

template <typename T>
struct RemoveRefrence<T&> {
    using Type = T;
};

template <typename T>
struct RemoveRefrence<T&&> {
    using Type = T;
};

/*move 以及 forward 的实现*/
template <typename T>
typename std::remove_reference<T>::type&& move (T&& param) {
    return static_cast<typename std::remove_reference<T>::type&&>(param);
}

// // 使用标准库的removeref
// template<typename T>
// T&& forward(typename std::remove_reference<T>::type& param){
//     return static_cast<T&&>(param);
// }

// 使用自定义的removeref 
template<typename T>
T&& forward(typename RemoveRefrence<T>::Type& param){
    return static_cast<T&&>(param);
}



/* 试验 */
void foo(int& x) {
    printf("foo (int& x) called\n");
}
void foo(int&& x) {
    printf("foo (int&& x) called\n");
}
template<typename T>
void callFoo(T&& arg) {
    foo(forward<T>(arg));
};

int main() {
    int a = 1;
    callFoo(a);
    callFoo(1);
}
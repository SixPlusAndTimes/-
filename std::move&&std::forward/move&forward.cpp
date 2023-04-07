#include <type_traits>
#include <stdlib.h>
template <class T>
typename std::remove_reference<T>::type&& move (T&& param) {
    return static_cast<typename std::remove_reference<T>::type&&>(param);
}

template<typename T>
T&& forward(typename std::remove_reference<T>::type& param){
    return static_cast<T&&>(param);
}


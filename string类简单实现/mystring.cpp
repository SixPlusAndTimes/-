#include "mystring.h"

std::ostream& operator<<(std::ostream& io, mystring& str) {
    io << str.c_str();
    return  io;
}
void mystring::push_back(const char ch) {
    if (size_ >= capacity_) {
        std::cout << "expand capacity_\n";
        char* temp = str_;
        str_ = new char[capacity_ * 2];
        capacity_ = capacity_ * 2;
        strcpy(str_, temp);
        delete[] temp; 
    } 
    str_[size_] = ch;
    str_[++size_] = '\0';
}
char& mystring::operator[](int index) const{ // 这里的const加不加？
    if (index < 0 || index > size_) {
        throw std::out_of_range("数组越界, index > string size\n");
    }
    return str_[index];
}

/*迭代器相关*/
mystring::iterator mystring::begin(){
    return str_;
}
mystring::const_iterator mystring::cbegin(){
    return str_;
};
mystring::iterator mystring::end(){
    return str_ + size_;
}
mystring::const_iterator mystring::cend(){
    return str_ + size_;
}
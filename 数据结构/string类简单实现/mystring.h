#include <algorithm>
#include <cstddef>
#include <cstdlib>
#include <istream>
#include <stdexcept>
#include <string.h>
#include <iostream>
class mystring {
private:
    char* str_;
    int size_; // size_不将str_的结束符计入
    int capacity_; // capacity_ 一开始于size_ 相等，append操作扩容的话就 * 2；
public:
     /*----构造、析构、拷贝函数-----*/
    // 构造函数
    mystring(const char* cstr = "") { // 注意形参的const，如果没有，那么当用户传递一个const char* 会报错
        if (cstr == nullptr) { // cstr如果为null的情况判断
            str_ = new char[1];
            str_[0] = '\0';
            size_ = 0;
        } else {
            size_ = strlen(cstr);
            str_ = new char[size_ + 1];
            strcpy(str_, cstr);
        }
        capacity_ = size_;
    }
    ~mystring() {
        delete [] str_;
    }
    // 拷贝构造函数
    mystring(const mystring& mstr):size_(mstr.size()),capacity_(mstr.getCapacity()) {
        std::cout << "apply mystring copy construct\n";
        str_ = new char[size_ + 1]; // 这一步是必要的，因为要通过拷贝构造函数产生对象，那么就说明这个对象本来是不存在的！这是和赋值函数不一样的一个点
        strcpy(str_, mstr.c_str());
    }
    // 拷贝赋值函数
    mystring& operator=(const mystring& mstr) {
        if (this == &mstr) { // 注意判重，否则导致野指针产生
            return *this;
        }
        delete[] this->str_; // 不要忘记delete本来的数组，否则内存泄漏
        this->str_ = new char[mstr.size() + 1];
        this->size_ = mstr.size();
        this->capacity_ = mstr.getCapacity();
        strcpy(this->str_, mstr.c_str());
        
        return *this;
    }

    /*----移动语义----*/
    // 移动构造
    mystring(mystring&& other) {
        std::cout << "move constructor applied\n";
        str_ = other.str_;
        size_ = other.size_;
        capacity_ = other.capacity_;

        other.str_ = nullptr; // 把被移动的对象置零
        other.size_ = 0;
        other.capacity_ = 0;
    }
    // 移动赋值
    mystring& operator=(mystring&& other) {
        std::cout << "move assigned applied\n";
        if (this == &other) {
            return *this;
        }
        delete [] str_;
        str_ = other.str_;
        size_ = other.size_;
        capacity_ = other.capacity_;

        other.str_ = nullptr; // 把被移动的对象置零
        other.size_ = 0;
        other.capacity_ = 0;
    }

    /*----成员函数----*/
    int getCapacity() const {
        return capacity_;
    }
    int size() const{
        return size_;
    }

    char* c_str() const{
        return str_;
    }
    bool empty() const{
        return size_ == 0; // size_没有把结束符号计入
    }

    void push_back(const char);
    void pop_back() ;
    char& back() const;
    mystring& append(const mystring&);
    mystring& append(const char*);
    /*----操作符重载----*/
    char& operator[](int index) const; // 这里的const加不加？
    mystring& operator+=(const mystring& other);
    mystring operator+(const mystring& other) const;
    // << 重载必须用全局函数而不是成员函数,
    // 如果使用成员函数重载，那么第一个参数是this。那么用户使用要变成这样  mystring << std::cout; 非常别扭
    friend std::ostream& operator<<(std::ostream& io, mystring& str); 

    /*----迭代器相关----*/
public :
    typedef char* iterator;
    typedef const char* const_iterator; // const_iterator可以改变指向，但是不能改变它的值

    iterator begin();
    const_iterator cbegin();
    iterator end();
    const_iterator cend();
};



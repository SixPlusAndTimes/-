#include "mystring.h"
#include <iostream>
#include <ostream>
#include <algorithm>
//g++ mystring.cpp mystring_test.cpp -o mystring_test
int main() {
    /*基本功能测试*/
    const char* str1Char = "asdoij";
    mystring str1(str1Char);

    mystring& str2 = str1;
    std::cout << "str1 :" << str1 << "  size of str1 = " << str1.size() << std::endl;
    std::cout << "str2 :" << str2 << "  size of str2 = " << str2.size() << std::endl;
    str1[0] = 'x';
    std::cout << "str1 :" <<str1;

    mystring str3;
    std::cout << "str3 :" << str3 << "  size of str3 = " << str3.size() << std::endl;   

    char* nullChar = nullptr;
    mystring str4(nullChar);
    std::cout << "str4 :" << str4 << "  size of str4 = " << str4.size() << std::endl;   

    std::cout << "push back a character in str4 :\n"; 
    str4.push_back('a');
    std::cout << "str4 :" << str4 << "  size of str4 = " << str4.size() << std::endl;   

    mystring str5 = str1;
    std::cout << "str5 :" << str5 << "  size of str5 = " << str5.size() << std::endl; 

    /* 测试 iterator*/
    // iterator
    mystring::iterator it = str5.begin();
    *it = 'a';
    *(++it) = 'b';
    std::cout << "modified str5.begin() :" << str5 << "  size of str5 = " << str5.size() << std::endl; 
    // const_iterator
    mystring::const_iterator const_it = str5.cbegin();
    // *const_it = 'b';  不能修改

    std::sort(str5.begin(),str5.end());
    std::cout << "after sorting str5 :" << str5 << "  size of str5 = " << str5.size() << std::endl; 

    /* 测试 移动语义*/
    mystring str6(std::move(str5));
    std::cout << "after move construct str5 to str6:" << "  size of str5 = " << str5.size() << std::endl; 
    std::cout << "str6 :" << str6 << "  size of str6 = " << str6.size() << std::endl; 

    mystring str7("sda");
    str7 = std::move(str6);
    std::cout << "after move assigned  str6 to str7:"<< "  size of str6 = " << str6.size() << std::endl;
    std::cout << "str7 :" << str7 << "  size of str7 = " << str7.size() << std::endl; 
}
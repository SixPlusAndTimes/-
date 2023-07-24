// 定义控制台应用程序的入口点。 //
#include <algorithm>
#include <cstddef>
#include <cstdlib>
#include <cstring>
#include <iostream>
#include <bits/stdc++.h>
class string {
    public:
        string(const char* src = NULL) {
            if (src == NULL) {
                m_data = nullptr;
                m_length = 0;
            }else {
                m_length = strlen(src);
                m_data = (char*)malloc(m_length + 1);
                memcpy(m_data, src, m_length + 1);
            }
        }
        ~string() {
            if (m_data) {
                delete [] m_data;
                m_data = nullptr;
            }
            m_length = 0;
        }
        int size() const {
            return m_length; 
        }
        const char *c_str() const {
            return m_data; 
        }
        string(const string &src) {
    
            m_length = src.m_length;
            m_data = (char*) malloc(m_length);
            memcpy(m_data, src.m_data, m_length + 1);
         
        }
        string operator+(const string &src) const {
            string ret; 
            ret.m_length = src.m_length + this->m_length;
            ret.m_data = (char*)malloc(ret.m_length + 1);
            memcpy(ret.m_data, this->m_data, this->m_length);
            memcpy(ret.m_data + this->m_length, src.m_data, src.m_length + 1);
            return ret; 
        }
        string& operator+=(const string &src) {
            char* new_str = (char*)malloc(m_length + src.m_length + 1);
            memcpy(new_str, this->m_data, this->m_length);
            memcpy(new_str + this->m_length, src.m_data, src.m_length + 1);
            this->m_length = this->m_length + src.m_length;
            if (m_data) {
                delete [] m_data;
            }
            m_data = new_str;
            return *this; 
        }
        bool operator==(const string &str) const {
            return strcmp(this->m_data, str.m_data) == 0;
        }
        void Reverse() {
            std::reverse(m_data, m_data + m_length);
        }
        void Sort() {
            std::sort(m_data, m_data + m_length);
        }
    private:
        char *m_data;
        int m_length; // 不记录空格
};
int main() {
    //构造函数
    string str1 = "abcde"; string str2("12345");
    //拷贝构造函数
    string str3 = str1;
    std::cout << (str3 == str1) << std::endl;
    //拷贝构造函数
    string str4(str2);
    std::cout << (str2 == str4) << std::endl;
    //+ 运算符
    string str5 = str1 + str2;
    std::cout << (str5 == "abcde12345") << std::endl;
    std::cout << (str5.size() == str1.size() + str2.size()) << std::endl;
    //+= 运算符
    str5 += str1;
    std::cout << (str5 == "abcde12345abcde") << std::endl;
    //反转
    string str6 = "12345678";
    str6.Reverse();
    std::cout << (str6 == "87654321") << std::endl;
    //排序
    string str7 = "202008131617";
    str7.Sort();
    std::cout << (str7 == "000111223678") << std::endl; return 0;
} 
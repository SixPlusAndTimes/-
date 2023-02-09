#include <atomic>
#include <iostream>
#include <ostream>

// 测试用的类
class Node {
public:
    int val_;
    Node* next_;
    Node(int val, Node* next) : val_(val), next_(next){}
    Node& operator=(const Node& other){
        val_ = other.val_;
        next_ = other.next_;
        return *this;
    }
};

// 模拟控制块类
class Counter {
    public:
        std::atomic<unsigned int> ref_count_;

        Counter():ref_count_(0){}
        Counter(unsigned int init_count):ref_count_(init_count){ }
};

// Shared_Ptr模板类
template<typename  T>
class Shared_Ptr{
    private:
        Counter* count_;
        T* resource_;
    public:
        // 构造函数
        Shared_Ptr():count_(new Counter(0)),resource_(nullptr) { }
        Shared_Ptr(T* raw_ptr):count_(new Counter(1)),resource_(raw_ptr) { }
        // 析构函数
        ~Shared_Ptr() {
            // printf("deconstructor\n");
            if (count_) { // 注意这里应该判断count_是否为nullptr，可能已经被移走了
                count_->ref_count_--;
                if (count_->ref_count_== 0) {
                    if (resource_) { // resource_也是同样的道理
                        delete resource_;
                    }
                    delete count_;
                }
            }

        }
        // 复制构造函数
        Shared_Ptr(const Shared_Ptr& other) {
            resource_ = other.resource_;
            count_ = other.count_;
            count_->ref_count_++;
        }
        // 赋值构造函数
        Shared_Ptr& operator=(const Shared_Ptr& other) {
            if (&other != this) {
                delete resource_;
                delete count_;

                resource_ = other.resource_;
                count_ = other.count_;
                count_->ref_count_++;
            }
            return *this;
        }

        // 移动构造函数
        // 注意将被移动对象的资源置空
        Shared_Ptr(Shared_Ptr&& other):resource_(other.resource_), count_(other.count_) {

            other.resource_ = nullptr;
            other.count_ = nullptr;
        }
        // 移动赋值函数
        Shared_Ptr& operator=(Shared_Ptr&& other) {
            // 注意将被移动对象的资源置空
            if (this  != &other) {
                delete resource_;
                resource_ = other.resource_;
                other.resource_ = nullptr;

                delete count_;
                count_ = other.count_;
                other.count_ = nullptr;
            }
            return *this;
        } 
        // debug
        unsigned int showRefCount() const{
            if (!count_) return 0;
            return count_->ref_count_;
        }
};


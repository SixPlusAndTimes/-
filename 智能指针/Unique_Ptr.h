#include <cstddef>
#include <iostream>
#include <memory>
class Node {
public:
    int val_;
    Node* next_;
    Node(int val, Node* next) : val_(val), next_(next){}
    Node& operator=(const Node& other){
        val_ = other.val_;
        next_ = other.next_;
    }
};

template<typename T> 
class Unique_Ptr {
private:
    // 原始指针
    T* resource_;

public:
    // unique_ptr是只移的，因此删除赋值函数
    Unique_Ptr(const Unique_Ptr&) = delete;
    Unique_Ptr& operator=(const Unique_Ptr&) = delete;
    // 构造函数
    explicit Unique_Ptr(T* raw_ptr): resource_(raw_ptr) { } // explicit防止隐式转换
    // 移动函数
    Unique_Ptr(Unique_Ptr&& other):resource_(other.resource_) {
        other.resource_ = nullptr;
    }
    Unique_Ptr& operator=(Unique_Ptr&& other) {
        if (&other != this) {
            if (resource_) {
                delete resource_;
            }
            resource_ = other.resource_;
            other.resource_ = nullptr;
        }
        return *this;
    }
    // 析构函数
    ~Unique_Ptr() {
        if (resource_) {
            delete resource_;
            resource_ = nullptr;
        }
    }
    T& operator*() const{
        if (resource_) {
            return resource_;
        }else {
            return nullptr;
        }
    }

    T* operator->() const{
        if (resource_) {
            return resource_;
        }else {
            return nullptr;
        }
    }
    // 用于 if (Unique_Ptr) {..} 的场景
    operator bool() {
        if (resource_) {
            return true;
        }else {
            return false;
        }
    }
};

// int main() {
//     Node* node1 = new Node(1, nullptr);
//     Node* node2 = new Node(2, node1);

//     Unique_Ptr<Node> u_node1(new Node(1, node2));
//     Unique_Ptr<Node> u_node2(std::move(u_node1));
//     std::cout << "u_node2 val = " << u_node2->val_ << "  u_node2 next val: " << u_node2->next_->val_ << std::endl;
// }
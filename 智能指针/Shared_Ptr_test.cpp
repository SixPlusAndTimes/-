#include "Shared_Ptr.h"
#include <memory>
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

Shared_Ptr<Node> getSharedPtr() {
    return Shared_Ptr<Node>(new Node(1,nullptr));
}

void passByValue(Shared_Ptr<Node> node) {
    std::cout << "5. ref count of node in function = " << node.showRefCount() << std::endl;
}
int main() {
    // std::shared_ptr<Node> a(new Node(1,nullptr));
    // 测试
    Node* node1 = new Node(1, nullptr);
    Node* node2 = new Node(2, node1);

    Shared_Ptr<Node> s_node1(new Node(1, node2));
    // Shared_Ptr<typename T><Node> u_node2(std::move(u_node1));
    std::cout << "1. ref count of node1 = " << s_node1.showRefCount() << std::endl;
    std::cout << std::endl;

    Shared_Ptr<Node> s_node2(s_node1);
    Shared_Ptr<Node> s_node3 ;
    s_node3 = s_node2;
    std::cout << "2. ref count of node1 = " << s_node1.showRefCount() << std::endl;
    std::cout << "2. ref count of node2 = " << s_node2.showRefCount() << std::endl;
    std::cout << "2. ref count of node3 = " << s_node3.showRefCount() << std::endl;
    std::cout << std::endl;

    Shared_Ptr<Node> s_node4(std::move(s_node3));
    std::cout << "3. ref count of node1 = " << s_node1.showRefCount() << std::endl;
    std::cout << "3. ref count of node2 = " << s_node2.showRefCount() << std::endl;
    std::cout << "3. ref count of node3 = " << s_node3.showRefCount() << std::endl;
    std::cout << "3. ref count of node4 = " << s_node4.showRefCount() << std::endl;
    std::cout << std::endl;

    s_node4 = nullptr;
    std::cout<< "after s_node4 = nullptr\n";
    std::cout << "3. ref count of node1 = " << s_node1.showRefCount() << std::endl;
    std::cout << "3. ref count of node2 = " << s_node2.showRefCount() << std::endl;
    std::cout << "3. ref count of node4 = " << s_node4.showRefCount() << std::endl;
    std::cout << std::endl;

    Shared_Ptr<Node> s_node5 = getSharedPtr();
    std::cout << "4. ref count of node5 = " << s_node5.showRefCount() << std::endl;
    std::cout << std::endl;

    passByValue(s_node5);
    std::cout << "5. ref count of node in function = " << s_node5.showRefCount() << std::endl;

}
#include <cstdio>
#include <functional>
#include <iostream>
#include <iterator>
#include <ostream>
#include <vector>
#include <string>
#include <unordered_map>
using namespace std;
// 感觉还是不够简单，前面的代码都不可能在短时间内写出来
// 这个版本不考虑泛型， 且 Node显示地存储key 和 value

class Node {
public:
    int key;
    int value;
    Node* next;
    Node* prev;
    Node(int key, int value): key(key), value(value), next(nullptr), prev(nullptr) {

    }
    Node() {}
};

class MyHashTable {
public:
    MyHashTable():bucket_size(3) , ht_(bucket_size){

    }
    Node* getNode(Node* head, int key) {
        while (head) {
            if (head->key == key) {
                return head;
            }else {
                head = head->next;
            }
        }
        return head;
    }
    void put(int key, int val) {
        int bucket_num = hasher(key) % ht_.size();
        if (ht_[bucket_num] == nullptr) { // 这个位置还没有链表存在
            Node* newnode  = new Node(key,val);
            ht_[bucket_num] = newnode;
        }else {
            Node* chain_head = ht_[bucket_num];
            Node* origin_node = getNode(chain_head, key);
            if (origin_node) { // 如果链表中有相同的key的node
                origin_node->value = val;
            }else { // 如果没有则新插入一个node在这个链中
                Node* newnode = new Node(key, val);
                newnode->next = chain_head;
                chain_head->prev = newnode;
                ht_[bucket_num] = newnode;
            }
        }
    }
    int get(int key) {
        int bucket_num = hasher(key) % ht_.size();
        if (ht_[bucket_num] == nullptr) {
            return -1;
        }

        Node* node = getNode(ht_[bucket_num], key);
        if (!node) return -1;
        return node->value;
    }

    bool contains(int key) {

    }
private:
    int bucket_size ;
    std::hash<int> hasher = std::hash<int>();
    vector<Node*> ht_;
};
int main() {
    MyHashTable myht;
    myht.put(1, 2);
    
    myht.put(2, 3);
    cout << myht.get(1) << endl;
    cout << myht.get(2) << endl;
    cout << myht.get(3) << endl;
    cout << myht.get(3) << endl;
    myht.put(1,4);
    cout << myht.get(1) << endl;
    return 0;
}
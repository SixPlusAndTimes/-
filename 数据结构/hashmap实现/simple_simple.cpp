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
    Node(int k, int v) :  key(k), value(v) ,next(nullptr) {
    }
};

class MyHashMap {
private:
    vector<Node*> ht_;
    Node* findNodeInList(Node* head, int key) {
        Node* res = nullptr;
        while (head) {
            if (head->key == key){
                res = head;
                break;
            }
            head = head->next;
        }
        return res;
    }
    void removeFromList(Node* list_head, int key) {
        Node* pre = list_head;
        Node* cur = list_head->next;
        while (pre && cur) {
            if (cur->key == key) {
                pre->next = cur->next;
                delete cur;
                return;
            }else {
                pre = cur;
                cur = cur->next;
            }
        }
    }
public:
    MyHashMap(): ht_(101, nullptr) { // 固定的vec长度
    }

    void put(int key, int value) {
        int bk_num = key % ht_.size();
        Node* list_head = ht_[bk_num];
        if (!list_head) { // 这个bucket还是空的，那么直接放在这里
            ht_[bk_num] = new Node(key,value);
        }else {
            Node* finded_node = findNodeInList(list_head, key);
            if (finded_node) {
                finded_node->value = value;
            }else {
                finded_node = new Node(key, value);
                Node* temp = list_head->next;
                list_head->next = finded_node;

                finded_node->next = temp;
            }
        }


    }
    
    int get(int key) {
        int bk_num = key % ht_.size();
        Node* list_head = ht_[bk_num];
        if (list_head) {
        }
        Node* finded_node = findNodeInList(list_head, key);
        if (finded_node) {
            return finded_node->value;
        }else {
            return -1;
        }
    }
    
    void remove(int key) {
        int  bk_num = key % ht_.size();
        Node* list_head = ht_[bk_num];
        if (!list_head) return ;
        if (list_head && list_head->key == key) {
            ht_[bk_num] = list_head->next;
            delete list_head;
        }else {
            removeFromList(list_head, key);
        }
        
    }

};

int main() {
    MyHashMap myht;
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
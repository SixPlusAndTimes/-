#include <algorithm>
#include <functional>
#include <iostream>
#include <cassert>
#include <iterator>
#include <ostream>
#include <ratio>
#include <string>
#include <utility>
#include <vector>
#include <list>
// 太冗长，面试这样写感觉就寄了
template<typename KeyType, typename ValueType>
class list_node {
public:
    list_node():next_(nullptr), node_val_() {

    }
    list_node(KeyType key, ValueType value) : next_(nullptr), node_val_{key,value}{
    }
    using node_val_type = std::pair<KeyType,ValueType> ;
    list_node<KeyType, ValueType>* next_;
    node_val_type node_val_;

    node_val_type* find(KeyType key) {
        std::cout << "list find() :to find key " << key << std::endl;
        list_node<KeyType, ValueType>* cur = this->next_;
        while (cur) {
            if (cur->node_val_.first == key) {
                std::cout << "\tfind one  key  =  " << key << "  value =  " << cur->node_val_.second<< std::endl;
                return &(cur->node_val_);
            }
            cur = cur->next_;
        }
        std::cout << "\tno key in this bucketchain"<< std::endl;
        return nullptr;
    }

    node_val_type* insert(list_node<KeyType, ValueType>* new_node) {
        std::cout << "list insert : node kye = " << new_node->node_val_.first << " node value = " <<  new_node->node_val_.second << std::endl;
        list_node<KeyType, ValueType>* tmp = next_;
        this->next_ = new_node;
       
        new_node->next_ = tmp;
        std::cout << "insert complete\n";
        return &new_node->node_val_;
    }

    bool empty() {
        return next_ == nullptr;
    }
    
};

template<typename KeyType, typename ValueType, typename HashFunc = std::hash<KeyType>>
class simple_hash_table { // 不支持重复的key，若将重复的键插入，则覆盖原来的键
public:
    simple_hash_table():bucketNum_(10), buckets_(std::vector<list_node<KeyType, ValueType>>(bucketNum_)), hasher(){
    }
    ValueType& operator[] (KeyType key) {
        int hash_val = hasher(key) % bucketNum_;
        
        assert(hash_val >= 0 && hash_val < bucketNum_);
        list_node<KeyType, ValueType>& chainHead = buckets_[hash_val];
        std::pair<KeyType,ValueType>* findNode = chainHead.find(key);
        if (findNode) {
            return findNode->second;
        } else {
            return chainHead.insert(new list_node<KeyType, ValueType>(key, ValueType()))->second;
        }
    }

private:
    int bucketNum_;
    std::vector<list_node<KeyType, ValueType>> buckets_; // 注意std::vector<list_node<KeyType, ValueType>*>比较烦，还得一个一个地new
    HashFunc hasher;
};
// template<typename KeyType, typename ValueType, typename HashFunc>
// const int simple_hash_table<KeyType, ValueType,HashFunc>::bucketNum_ = 10;

int main() {
    // std::vector<std::list<std::pair<int, int>>> s(1);
    simple_hash_table<int, std::string> ht;
    for (int i = 0; i < 1000; i++) {
        ht[i] = std::to_string(i);
    }

    for (int i = 0; i < 1000; i++) {
        assert(ht[i] == std::to_string(i));
    }
}
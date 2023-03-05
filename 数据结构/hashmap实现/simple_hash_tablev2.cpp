#include <iostream>
#include <iostream>
#include <functional>
#include <string>
#include <utility>
#include <vector>
#include <string.h>
#include <cassert>
//  参考源码修正一波,参考版本与《stl源码剖析》的一致，都是SGI版本
//  未考虑迭代器的实现
template<typename Value>
class hashtable_node { 
public:
    hashtable_node* next;
    Value value;
    hashtable_node(Value val): value{val},next{nullptr} {
    }
    hashtable_node() {}
};

template<typename KeyType, typename ValueType, typename HashFunc = std::hash<KeyType>>
class simple_hash_table { 
public:
    using node = hashtable_node<std::pair< KeyType, ValueType>>;

    simple_hash_table():total_elenum{0},bucket_num{7},haser{}, buckets(bucket_num){
    }
    ValueType& operator[](const KeyType& key) { // 注意这里const key， 返回ValueType的引用
        int  bucket_index = haser(key) % bucket_num;
        node* chain_head = buckets[bucket_index];

        for (node* cur = chain_head; cur != nullptr; cur = cur->next) {
            if (cur->value.first == key) {
                return cur->value.second;
            }
        }

        node* new_hash_node = new node();
        new_hash_node->value = std::pair<KeyType, ValueType>{key, ValueType{}};
        new_hash_node->next = chain_head;
        buckets[bucket_index] = new_hash_node;
        ++total_elenum;
        return new_hash_node->value.second;
    }

    node* find(const KeyType& key) {
        int  bucket_index = haser(key) % bucket_num;
        node* chain_head = buckets[bucket_index];

        for (node* cur = chain_head; cur != nullptr; cur = cur->next) {
            if (cur->value.first == key) {
                return cur;
            }
        }
        return nullptr;
    }

    int size() {
        return total_elenum;
    }

    int getBucketNums() {
        return buckets.size();
    }


private:
    int total_elenum;
    int bucket_num;
    HashFunc haser;
    std::vector<node*> buckets;
};

int main() {
    // std::vector<std::list<std::pair<int, int>>> s(1);
    simple_hash_table<int, std::string> ht;
    ht[1] = 2;
    for (int i = 0; i < 1000; i++) {
        ht[i] = std::to_string(i);
    }

    for (int i = 0; i < 1000; i++) {
        assert(ht[i] == std::to_string(i));
    }

    std::cout << "hash table now has " << ht.size() << " elements\n";
    std::cout << "hash table buckets size =  " << ht.getBucketNums() << "\n";

    assert(ht.find(1) != nullptr);
    assert(ht.find(1)->value.second == "1");
    assert(ht.find(1001) == nullptr);
    assert(ht.find(1001) == nullptr);
}
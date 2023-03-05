#include <iostream>
#include <iostream>
#include <functional>
#include <string>
#include <utility>
#include <vector>
#include <string.h>
#include <cassert>
// 加入rehash的逻辑，按照SGI的rehash策略
template<typename Value>
class hashtable_node { 
public:
    hashtable_node* next;
    Value value;
    hashtable_node(Value val): value{val},next{nullptr} {
    }
    hashtable_node() {}
};
// hash表底层vector的size的个数应该为素数
static const std::vector<int> bucketNumCandidate{3, 5, 7, 11, 13,17,19,23,29,31};

template<typename KeyType, typename ValueType, typename HashFunc = std::hash<KeyType>>
class simple_hash_table { 
public:
    using node = hashtable_node<std::pair< KeyType, ValueType>>;

    simple_hash_table():bucket_num_ptr(0), total_elenum{0},haser{}, buckets(bucketNumCandidate[bucket_num_ptr]){
    }
    ValueType& operator[](const KeyType& key) { // 注意这里const key， 返回ValueType的引用
        
        // 添加新的
        need_rehash(total_elenum + 1); // 看看要不要rehash
        int  bucket_index = haser(key) % buckets.size();
        node* chain_head = buckets[bucket_index];
        // 原hash表中存在这个key：value对
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
    int getNextBucketNum() {
        if (bucket_num_ptr == bucketNumCandidate.size() - 1) {
            return bucket_num_ptr;
        }
        else return ++bucket_num_ptr;
    }
    void need_rehash(int hint_num) {
       
        int old_n = buckets.size();
        if (hint_num > old_n) {
            printf("\n");
            int next_num = bucketNumCandidate[getNextBucketNum()];
            // if (next_num == buckets.size()) return; // 已达到最大的哈希表vector长度
            // rehash 
            std::cout << "before rehash\n";
            printTable();
            printf("next_num = %d\n",next_num);
            std::vector<node*> tmp(next_num);
            for(int i = 0; i < old_n; i++) {
                node* first = buckets[i];
                while (first) {
                    int new_buck_num = haser(first->value.first) % next_num; // 新的桶号
                    // 注意： 除了要将原桶的元素rehash至新桶内，
                    // node* next_first = first->next;

                    // node* next_node = tmp[new_buck_num];
                    // tmp[new_buck_num] = first;
                    // first->next = next_node;

                    // first = next_first;

                    buckets[i] = first->next;
                    first->next = tmp[new_buck_num];
                    tmp[new_buck_num] = first;
                    first = buckets[i];
                }
            }
            printf("rehash complete\n");
            buckets = std::move(tmp);

            printTable();
        }
    }

    node* find(const KeyType& key) {
        int  bucket_index = haser(key) % buckets.size();
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
    
    // debug
    void printTable() {
        for (int i = 0; i < buckets.size(); i++) {
            node* chainHead = buckets[i];
            std::cout << "buket" << i << " ";
            while (chainHead) {
                printf("[%d|%s]->", chainHead->value.first, chainHead->value.second.c_str());
                chainHead = chainHead->next;
            }
            printf("\n");
        }
    }

private:
    int bucket_num_ptr;
    int total_elenum;
    HashFunc haser;
    std::vector<node*> buckets;
};

int main() {
    simple_hash_table<int, std::string> ht;
    // ht[1] = 2;
    for (int i = 0; i < 100; i++) {
        ht[i] = std::to_string(i);
    }

    printf("final hashtable:\n");
    ht.printTable();
    for (int i = 0; i < 100; i++) {
        if (std::to_string(i) != ht[i]) {
            printf("ht[%d] = %s, not true\n", i, ht[i].c_str());
        }
    }

    // std::cout << "hash table now has " << ht.size() << " elements\n";
    // std::cout << "hash table buckets size =  " << ht.getBucketNums() << "\n";

    // assert(ht.find(1) != nullptr);
    // assert(ht.find(1)->value.second == "1");
    // assert(ht.find(1001) == nullptr);
    // assert(ht.find(1001) == nullptr);

    // simple_hash_table<std::string, std::string> h2;
    // h2["asd"] = "as";
}
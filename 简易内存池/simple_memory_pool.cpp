#include <cstddef>
#include <cstdlib>
#include <list>
#include <vector>
#include <iostream>
using namespace std;
// 建议的内存池分配实现
// vector<arena> arenas有5个元素，每个arena都代表一个规格的内存块的集合。分别为 16、32、64、128、256
struct mem_block{
    mem_block* next;
};

struct arena{
    arena() : bolck_size(0), free_list(nullptr) {}
    int bolck_size;
    mem_block* free_list;
};

static const int DESC_COUNT = 5;
static const int ALLOC_SIZE = 4096;
vector<arena> arenas; // 8、16 、24、 32、 40

void initArenas() {
    printf("init arenas\n");
    arenas = vector<arena>(DESC_COUNT);
    for (int i = 0; i < DESC_COUNT; i++) {
        arenas[i].bolck_size = 8 * (i + 1);
    }
    printf("init done\n");
}
int getAreanVecIdx(int block_size) {
    int desc_idx = 0;
    for (; desc_idx < DESC_COUNT; desc_idx++) {
        if (arenas[desc_idx].bolck_size >= block_size) {
            break;
        }
    }
    return desc_idx;
}
char* allocMemblock(int block_size) {
    printf("allocMemblock block_size = %d\n", block_size);
    int desc_idx = getAreanVecIdx(block_size);
    if (desc_idx >= DESC_COUNT) {
        printf("allocMemblock : desc_idx >= DESC_COUNT\n");
        return nullptr;
    }

    if (arenas[desc_idx].free_list == nullptr) {
        printf("\tarenas[%d] is empty(), alloc some space\n", desc_idx);
        mem_block* new_area = (mem_block*)malloc(ALLOC_SIZE); // 分配新空间
        // printf("\t\t new_area = %p\n", new_area);
        arenas[desc_idx].free_list = new_area; // 新空间地址存放在free_list中
        int block_nums = ALLOC_SIZE / arenas[desc_idx].bolck_size; // 这个新空间能够包含几个内存块

        for (int i = 0; i < block_nums; i++) { // 将链表连起来
            // printf("\t\t i = %d\n", i);
            new_area->next = (mem_block*)((char*)new_area + block_size);
            new_area = new_area->next;
        }
        // printf("\talloc down\n");
    }

    mem_block* result = arenas[desc_idx].free_list;
    arenas[desc_idx].free_list = arenas[desc_idx].free_list->next;
    printf("return addres = %p\n", result);
    return (char*) result;
}

void freeMemBlock(char* ptr, int block_size) {
    printf("freeMemBlock, bolck_size = %d, ptr = %p\n", block_size, ptr);
    int desc_idx = getAreanVecIdx(block_size);
        if (desc_idx >= DESC_COUNT) {
        printf("freeMemBlock : desc_idx >= DESC_COUNT\n");
        return ;
    }
    mem_block* free_block = (mem_block*) ptr;
    free_block->next = arenas[desc_idx].free_list;

    arenas[desc_idx].free_list = free_block;
    printf("free down\n");
}
int main() {
    initArenas();

    char* a = allocMemblock(8);
    int* a_ptr = (int*)(a);
    *(a_ptr) = 1, *(a_ptr + 1) = 2;
    printf("*a_ptr = %d, *(a_ptr + 1) = %d\n", *(a_ptr), *(a_ptr + 1));

    freeMemBlock(a, 8);

    char* b = allocMemblock(11);
    freeMemBlock(b, 11);

    char* c = allocMemblock(17);
    freeMemBlock(c, 17);

    char* d = allocMemblock(35);
    freeMemBlock(d, 35);

    char* e = allocMemblock(30);
    freeMemBlock(e, 30);

    char* f = allocMemblock(40);
    freeMemBlock(f, 40);

    char* g = allocMemblock(50);
    freeMemBlock(g, 50);
}

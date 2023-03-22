#include <functional>
#include <vector>
using namespace std;

class MyQueue {
private:
    vector<int> heap;
public:
    MyQueue():heap(){

    }

    void push(const int& ele) {
        heap.push_back(ele);
        up(heap.size() - 1);
    }

    void pop() {
        swap(heap[0], heap[heap.size()- 1]);
        heap.pop_back();
        swift_down(0, heap.size() - 1);
    }

    int top() {
        return heap[0];
    }

    void up(int child_index) {
        int parent_index = (child_index - 1) / 2;
        while (parent_index >= 0) {
            if (heap[child_index] > heap[parent_index]) {
                swap(heap[parent_index], heap[child_index]);
                child_index = parent_index;
                parent_index = (child_index - 1) /2;
            }else {
                break;
            }
        }
    }

    void swift_down(int start_index, int end_index) {
        int child_index = start_index * 2 + 1;
        while (child_index <= end_index) {
            if (heap[child_index + 1] > heap[child_index]) {
                child_index++;
            }
            if (heap[child_index] > heap[start_index]) {
                swap(heap[child_index], heap[start_index]);
            }
            start_index = child_index;
            child_index = start_index * 2 + 1;
        }
    }
};
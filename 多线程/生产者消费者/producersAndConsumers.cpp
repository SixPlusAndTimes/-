#include <iostream>
#include <string>
#include <vector>
#include <string.h>
#include <mutex>
#include <condition_variable>
#include <queue>
#include <thread>
const int maxBound = 10; // 缓冲区最多有9个, 还有一个是空位，为了区分判断空和满两种状况
int read_ptr = 0;
int write_ptr = 0;
std::vector<char> shared_buf(10); // 环形缓冲区
// int count = 0; // 表示缓冲区有几个有效的字符, 好像不需要这个字段， 读写指针就可以判断满还是没满了
std::mutex mtx;
std::condition_variable buf_is_empty;
std::condition_variable buf_is_full;

void produce(std::string messeage) {
    for (char cur_char : messeage) {
        std::unique_lock<std::mutex> uniqlk(mtx); // 必须使用uniquelock以配合条件变量，这一步相当于已经将mutex锁住了
        while ((write_ptr + 1) % maxBound == read_ptr) {
            buf_is_full.wait(uniqlk);
        }
        shared_buf[write_ptr] = cur_char;
        write_ptr = (write_ptr + 1) % maxBound;
       
        buf_is_empty.notify_all();

        uniqlk.unlock(); // 解锁
    }
}

void consume(int size) {
    for (int i = 0; i < size; i++) {
        std::unique_lock<std::mutex> uniqlk(mtx);
        while (read_ptr == write_ptr) {
            buf_is_empty.wait(uniqlk);
        }
        std::cout << shared_buf[read_ptr];
        read_ptr = (read_ptr + 1) % maxBound;
       
        buf_is_full.notify_all();

        uniqlk.unlock();
    }
}
int main() {
    // std::thread producer(produce,"hello I.m child\n");
    // std::thread consumer(consume);

    // producer.join();
    // consumer.join();
    std::string messege = "this is message\n";
    std::vector<std::thread> producers;
    for (int i = 0; i < 5; i++) {
        producers.push_back(std::thread(produce,messege));
    }

    std::vector<std::thread> consumers;
    for (int i = 0; i < 5; i++) {
        producers.push_back(std::thread(consume,messege.size()));
    }

    for (auto& i : producers) {
        i.join();
    }

    for (auto& i : consumers) {
        i.join();
    }

    
}
#include <chrono>
#include <iostream>
#include <ostream>
#include <thread>
#include <mutex>
#include <condition_variable>
// 目标： 两个线程交替打印0和1
// 编译命令： g++ print_01_std_thread.cpp  -lpthread -g -o print_01_std_thread
std::mutex m_lck;
std::condition_variable cond;
int which = 0; 
void print1() {
    while (1) {
        std::unique_lock<std::mutex> lk(m_lck);
        // lk.lock();这会造成死锁，上面std::unique_lock<std::mutex> lk(m_lck);已经加锁了
        while (which != 1) {
            cond.wait(lk);
        } 
        std::cout << "pid = " <<std::this_thread::get_id() << ":"<< "1" << std::endl;
        which = 0;
       cond.notify_one();
    }

}

void print0() {
    while (1) {
     std::unique_lock<std::mutex> lk(m_lck);

        // lk.lock();这会造成死锁，上面std::unique_lock<std::mutex> lk(m_lck);已经加锁了 
        while (which != 0) {
            cond.wait(lk);
        } 
        std::cout << "pid = " <<std::this_thread::get_id() << ":"<< "0" << std::endl;
        which = 1;
       cond.notify_one();
    }

}
int main() {
    std::thread t1(print0);
    std::thread t2(print1);
    t1.join();
    t2.join();
}
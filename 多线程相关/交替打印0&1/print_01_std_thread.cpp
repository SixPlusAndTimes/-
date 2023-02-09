#include <chrono>
#include <iostream>
#include <ostream>
#include <thread>
#include <mutex>
#include <condition_variable>
// 目标： 两个线程交替打印0和1
// 体会： C++的线程库有没有系统地学，有些操作难懂。之后还是用C和pthread库写一个吧
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
        lk.unlock(); // 这个unlock不加也行，之前使用的unique_lock在函数执行域末尾（函数返回时）执行unlock，unique_lock也会在循环体末尾解锁吗？
       cond.notify_all();
        std::this_thread::sleep_for(std::chrono::seconds(1));
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
        lk.unlock();
       cond.notify_all();
        std::this_thread::sleep_for(std::chrono::seconds(1));
    }

}
int main() {
    std::thread t1(print0);
    std::thread t2(print1);
    t1.join();
    t2.join();
}
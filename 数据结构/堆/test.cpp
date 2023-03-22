#include "MyPriorityQueue.h"
#include <cassert>
#include <iostream>
#include <ratio>
#include <vector>
#include <queue>
int main() {
    MyQueue mque;
    priority_queue<int> qe;
    for (int i = 10; i >= 1; --i) {
        mque.push(i);
        qe.push(i);
    }
    cout << qe.top() << endl;
    cout << mque.top() << endl;
    assert(qe.top() == mque.top());

    qe.push(4);
    mque.push(4);
    assert(qe.top() == mque.top());

    qe.pop();
    mque.pop();
    cout << qe.top() << endl;
    cout << mque.top() << endl;
    assert(qe.top() == mque.top());

    for (int i = 6; i <= 11; i++) {
        qe.push(i);
        mque.push(i);
    }
    cout << qe.top() << endl;
    cout << mque.top() << endl;
    assert(qe.top() == mque.top());
}
#include <stack>
using namespace std;

// 利用栈实现队列
// 一般会想到双栈思路，比较好实现
//
class MyQueue {
public:
    /** Initialize your data structure here. */
    MyQueue() {}
    
    /** Push element x to the back of queue. */
    void push(int x) {
        stk.push(x);
    }
    
    /** Removes the element from in front of queue and returns that element. */
    int pop() {
        if (help.empty()) {
            while (!stk.empty()) {
                help.push(stk.top());
                stk.pop();
            }
        }
        int ret = 0;
        if (!help.empty()) {
            ret = help.top();
            help.pop();
        }
        return ret;
    }
    
    /** Get the front element. */
    int peek() {
        if (help.empty()) {
            while (!stk.empty()) {
                help.push(stk.top());
                stk.pop();
            }
        }
        int ret = 0;
        if (!help.empty()) {
            ret = help.top();
        }
        return ret;  
    }
    
    /** Returns whether the queue is empty. */
    bool empty() {
        return stk.empty() && help.empty();
    }
private:
    stack<int> stk;
    stack<int> help;                                    
};

/**
 * Your MyQueue object will be instantiated and called as such:
 * MyQueue* obj = new MyQueue();
 * obj->push(x);
 * int param_2 = obj->pop();
 * int param_3 = obj->peek();
 * bool param_4 = obj->empty();
 */

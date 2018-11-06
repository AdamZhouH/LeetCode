#include <iostream>
#include <string>
#include <stack>
using namespace std;

class MinStack {
public:
    /** initialize your data structure here. */
    MinStack();
    void push(int x);
    void pop();
    int top();
    int getMin();
private:
	stack<int> stk;
	stack<int> minStk;
};


MinStack::MinStack() { }

void MinStack::push(int x) {
	if (stk.empty()) {
		minStk.push(x);
	} else {
		auto val = minStk.top();
		if (x <= val)
			minStk.push(x);
	}
	stk.push(x);
}

void MinStack::pop() {
	assert(!stk.empty());
	assert(!minStk.empty());
	auto a = stk.top();
	auto b = minStk.top();
	if (a == b) 
		minStk.pop();
	stk.pop();
}

int MinStack::top() {
	assert(!stk.empty());
	return stk.top();
}

int MinStack::getMin() {
	assert(!minStk.empty());
	return minStk.top();
}

/**
 * Your MinStack object will be instantiated and called as such:
 * MinStack obj = new MinStack();
 * obj.push(x);
 * obj.pop();
 * int param_3 = obj.top();
 * int param_4 = obj.getMin();
 */
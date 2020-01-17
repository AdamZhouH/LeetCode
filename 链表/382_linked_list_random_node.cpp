#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <random>
using namespace std;

#define OPTIMITION

struct ListNode {
	int val;
	ListNode *next;
	ListNode(int x) : val(x), next(nullptr) {}
};

#ifndef OPTIMITION
class Solution {
public:
	Solution(ListNode * head);
	int getRandom();
private:
	int length;
	default_random_engine e;
	ListNode *nodeList;
};

Solution::Solution(ListNode *head) : nodeList(head) {
	int len = 0;
	default_random_engine e(time(nullptr));
	this->e = e;
	ListNode *ptr = nodeList;
	while (ptr) {
		len++;
		ptr = ptr->next;
	}
	length = len;
}

// 很暴力的解法
int Solution::getRandom() {
	uniform_int_distribution<unsigned> u(1, length);
	ListNode *ptr = nodeList;
	int count = u(e);
	while (--count) {
		ptr = ptr->next;
	}
	return ptr->val;
}
#else
class Solution {
public:
	Solution(ListNode *head);
	int getRandom();
private:
	ListNode *listHead;
	default_random_engine e;
};

Solution::Solution(ListNode * head) : listHead(head) {
	e = default_random_engine(time(nullptr));
}

// 本题实际上是蓄水池的大小为1的特殊情况
int Solution::getRandom() {
	int ret = listHead->val;
	ListNode *ptr = listHead->next;
	int cnt = 2;
	while (ptr != nullptr) {
		uniform_int_distribution<unsigned> u(1, cnt);
		int randomvar = u(e);
		if (randomvar == 1)
			ret = ptr->val;
		cnt++;
		ptr = ptr->next;
	}
	return ret;
}
#endif

int main(void) {
	ListNode a(10); ListNode b(1); ListNode c(10); ListNode d(20); ListNode e(100);
	a.next = &b; b.next = &c; c.next = &d; d.next = &e;
	Solution solution(&a);
	for (int i = 0; i < 10; i++) {
		cout << solution.getRandom() << endl;
	}
	return 0;
}


#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
#include <stack>
using namespace std;

// 双指针
// 通过示例图可以知道，让一个指针先走到顺数第n个节点
// 让另一个指针则在第一个指针到达第n个节点后，从初始位置和前一个指针同步走
// 直到第一个指针先走到尾部，此时第二个指针指向的就是倒数第n个节点位置

// 由于题目要求返回删除节点的链表的头节点
// 考虑到删除的节点可能是链表中的任意一个，如果删除的是首个节点，那么头节点
// 指针也会发生变化，因此要注意这些情况
// 此外在删除时，需要直到前一个节点的指针，题目要求使用一次扫描实现
// 我们可以在遍历链表时候保存遍历的路径（利用栈），从而可以方便获取上一个节点

struct ListNode {
	int val;
	ListNode *next;
	ListNode(int x) : val(x), next(nullptr) {}
};

class Solution {
public:
	ListNode *removeNthFromEnd(ListNode *head, int n);
};

// 题目保证了n的有效性，因此这里不做检查
// 如果题目没有说明，则需要检查n的有效性，因为链表的总长度可能小于n
ListNode *Solution::removeNthFromEnd(ListNode *head, int n) {
	ListNode *fore = head;
	ListNode *back = head;
	for (int i = 1; i < n; i++) 
		fore = fore->next;
	// fore和back指针同时走，并且把back路径保存
	// 如果保存路径的栈为空，说明删除的是首个节点，则链表的头节点发生变化
	stack<ListNode *> path;
	while (fore->next != nullptr) {
		path.push(back);
		fore = fore->next;
		back = back->next;
	}
	// 删除的节点恰好是原头节点
	if (path.empty()) {
		return head->next;
	}
	ListNode *prev = path.top();
	prev->next = back->next;
	return head;
}

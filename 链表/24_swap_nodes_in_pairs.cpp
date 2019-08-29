#include <iostream>
#include <vector>

using namespace std;

struct ListNode {
	int val;
	ListNode *next;
	ListNode(int x) : 
		val(x),
		next(nullptr) {}
};

class Solution {
	public:
		ListNode *swapPairs(ListNode *head);
		void swapPairs(ListNode *&newHead, ListNode *&tail, ListNode *head);
};

ListNode *Solution::swapPairs(ListNode *head) {
	if (!head)
		return nullptr;
	ListNode *newHead = nullptr;
	ListNode *tail = nullptr;
	swapPairs(newHead, tail, head);
	return newHead;
}

void Solution::swapPairs(ListNode *&newHead, ListNode *&tail, ListNode *head) {
	if (!head)
		return;
	// 判断两点
	// 1.是否是新链表newHead第一个节点
	// 2.剩余链表head是否存在至少两个节点
	
	// 剩余head链表只有一个节点的情况
	if (!head->next) {
		// 还需要判断是否是第一次插入节点到新链表
		if (!newHead) {
			newHead = tail = head;
			return;
		} else {
			tail->next = head;
			tail = head;
			return;
		}
	} else {
	// 剩余head链表至少两个节点的情况
		// 同样判断是否是第一次插入新的链表
		if (!newHead) {
			ListNode *nextHead = head->next->next;
			head->next->next = head;
			newHead = head->next;
			tail = head;
			head->next = nullptr;
			swapPairs(newHead, tail, nextHead);
		} else {
			ListNode *nextHead = head->next->next;
			tail->next = head->next;
			tail = head;
			head->next->next = head;
			head->next = nullptr;
			swapPairs(newHead, tail, nextHead);
		}
	}
}

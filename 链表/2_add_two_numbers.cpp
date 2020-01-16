
// LeetCode 2 两数相加

// 注意事项，实际上是加法器原理吧
// 每次单个数字相加，考虑进位
// 加完之后，也要考虑进位是否还存在 (溢出)
// 其余部分仔细写就行了

#include <iostream>
using namespace std;

class Solution {
public:
    ListNode* addTwoNumbers(ListNode* l1, ListNode* l2);
    inline void dealCarry(int &val, int &carry);
};

void Solution::dealCarry(int &val, int &carry) {
    if (val >= 10) {
		carry = 1;
		val -= 10;
	} else           // 注意，carry要恢复为0
		carry = 0;
}

ListNode *Solution::addTwoNumbers(ListNode *l1, ListNode *l2) {
	// 类似加法器原理，逐个数字相加，注意进位，初始进位为0
	int carry = 0;
	ListNode *head = nullptr, *tail = nullptr;
	while (l1 && l2) {
		int val = l1->val + l2->val + carry;
		dealCarry(val, carry);
		ListNode *newNode = new ListNode(val);
		// 判断是否是新链表第一个结点
		if (head == nullptr) {
			head = newNode;
			tail = newNode;
			l1 = l1->next;
		    l2 = l2->next;
			continue;
		}
		// 把结点链接到链表
		tail->next = newNode;
		tail = newNode;
		// l1 l2往下走
		l1 = l1->next;
		l2 = l2->next;
	}
	// 剩余数字直接复制到新链表
	if (l1 != nullptr) {
		while (l1) {
			int val = carry + l1->val;
			dealCarry(val, carry);
			ListNode *newNode = new ListNode(val);
			// 尾部链接
			tail->next = newNode;
			tail = newNode;
			l1 = l1->next;
		}
	} else {
		while (l2) {
			int val = carry + l2->val;
			dealCarry(val, carry);
			ListNode *newNode = new ListNode(val);
			// 尾部链接
			tail->next = newNode;
			tail = newNode;
			l2 = l2->next;
		}
	} 
	// 注意可能两个链表同时为空，但是carry存在，处理最后的carry
	if (carry > 0) {
		ListNode *newNode = new ListNode(carry);
		tail->next = newNode;
	}

	return head;
}
// 21_merge_two_sorted_lists.cpp
// 链表不带头节点果然很麻烦，可以自己设置一个头结点，然后免去一部分判断
// LeetCode我这题用时达到12ms，加上头结点后可优化运行时间
// 以后有空再重写一遍  

/**
 * Definition for singly-linked list.
 * struct ListNode {
 *     int val;
 *     ListNode *next;
 *     ListNode(int x) : val(x), next(NULL) {}
 * };
 */

#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
using namespace std;

class Solution {
public:
    ListNode* mergeTwoLists(ListNode* l1, ListNode* l2);
};

ListNode *Solution::mergeTwoLists(ListNode *l1, ListNode *l2) {
	// 对于特殊输入，直接判断，然后返回
	if (!l1 && !l2)
		return nullptr;
	if (!l1)
		return l2;
	if (!l2)
		return l1;
	ListNode *newList = nullptr, *tail = nullptr;
	// 处理第一个结点
	if (l1->val <= l2->val) {
		newList = l1;
		tail = l1;
		l1 = l1->next;
	} else {
		newList = l2;
		tail = l2;
		l2 = l2->next;
	}
	// 处理接下来的结点
	while (l1 && l2) {
		if (l1->val < l2->val) {
			tail->next = l1;
			tail = l1;
			l1 = l1->next;
		} else {
			tail->next = l2;
			tail = l2;
			l2 = l2->next;
		}
	}
	// 处理剩余非空链表的结点
	if (l1)
		tail->next = l1;
	else
		tail->next = l2;
	return newList;
}
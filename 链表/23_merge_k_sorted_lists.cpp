#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <climits>
using namespace std;

struct ListNode {
    int val;
    ListNode *next;
    ListNode(int x) : val(x), next(NULL) {}
 };

// 主要是归并排序思想的运用
// 归并过程中涉及很多的细节问题需要考虑清楚，包括边界情况
// 比如所有的链表都是空链表
// merge的终止条件

class Solution {
public:
    ListNode* mergeKLists(vector<ListNode*>& lists);
    bool allNone(vector<ListNode*>& lists);
};

ListNode* Solution::mergeKLists(vector<ListNode*>& lists) {
	if (lists.empty())
		return nullptr;
	// 判断是否所有的链表都为空，并把非空链表存放到新的vector中
	// 如果所有链表都是空链表，直接返回空指针即可
	vector<ListNode *> ptrs;
	for (auto it : lists)
		if (it)
			ptrs.push_back(it);
	if (ptrs.empty())		
		return nullptr;
	// 设置头结点和尾结点指针
	ListNode *head = new ListNode(0);
	ListNode *tail = head;
	// 用于标识每一轮此比较的最小节点的指针
	ListNode *currMin = nullptr;

    while (!allNone(ptrs)) {
		int minVal = INT_MAX, idx= 0;
        currMin = nullptr;
    	for (int i = 0; i < ptrs.size(); i++) {
    		if (ptrs[i] && ptrs[i]->val < minVal) {
    			currMin = ptrs[i];
    			minVal = ptrs[i]->val;
                idx = i;
    		}
		}
        if (currMin) {
            tail->next = currMin;
            tail = currMin;
		    ptrs[idx] = ptrs[idx]->next;
        } else {
            break;
        }
    }

    return head->next;
}

bool Solution::allNone(vector<ListNode *> &lists) {
	for (auto it : lists) {
		if (it)
			return false;
	}
	return true;
}

// 很笨的方法，看到Leetcode大神20ms的方法真是自愧不如了，好好学习
// 一会把代码抄上来

// 给一个使用优先队列的解法
// 代码显得简洁很多，时间复杂度也降低，但是空间复杂度为O(k)
ListNode *Solution::mergeKLists(vector<ListNode *>& lists) {
    ListNode head;
    ListNode *ptr = &head;
    auto cmp = [](ListNode *lhs, ListNode *rhs) { return lhs->val > rhs->val;};
    priority_queue<ListNode *, vector<ListNode *>, decltype(cmp)> q(cmp);
    for (auto node : lists) if (node != nullptr) q.push(node);
    while (!q.empty()) {
        auto p = q.top(); q.pop();
        ptr->next = p;
        ptr = p;
        if (p->next != nullptr) q.push(p->next);
    }
    return head.next;
}
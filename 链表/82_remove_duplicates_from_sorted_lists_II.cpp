#include <vector>
#include <set>
#include <iostream>
using namespace std;

struct ListNode {
    int val;
    ListNode *next;
    ListNode(int x = 0) : val(x), next(NULL) {}
};


class Solution {
public:
    ListNode* deleteDuplicates(ListNode* head);
};

// 审题注意，题目要求的是没有重复出现的元素
// 而不是删除重复的元素
// 这个代码没有删除重复点的内存，需要删除处理一下
// 已处理删除重复节点内存
ListNode *Solution::deleteDuplicates(ListNode *head) {
    if (head == nullptr) return head;
    ListNode dummy;
    ListNode *tail = &dummy, *curr = head;
    while (curr != nullptr) {
        ListNode *p = curr;
        int val = curr->val;
        while (p->next && p->next->val == val)  {
            ListNode *tmp = p;
            p = p->next;
            delete tmp;
        }
        if (p == curr) {
            tail->next = curr; tail = curr;
            curr = curr->next; tail->next = nullptr;
        } else {
            curr = p->next;
            delete p;
        }
    }
    return dummy.next;
}


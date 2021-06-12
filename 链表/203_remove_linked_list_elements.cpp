#include <iostream>
#include <vector>
#include <algorithm>
#include <list>
using namespace std;

struct ListNode {
    int val;
    ListNode *next;

    ListNode() : val(0), next(nullptr) {}
    ListNode(int x) : val(x), next(nullptr) {}
    ListNode(int x, ListNode *next) : val(x), next(next) {}
};

class Solution {
public:
    ListNode *removeElements(ListNode *head, int val);
};

ListNode *Solution::removeElements(ListNode *head, int val) {
    if (head == nullptr) return head;
    ListNode *dummy = new ListNode(-1);
    dummy->next = head;
    ListNode *prev = dummy;
    while (prev->next) {
        if (prev->next->val == val) 
            prev->next = prev->next->next;
        else
            prev = prev->next;
    }
    return dummy->next;
}

#include <vector>
#include <set>
#include <iostream>
using namespace std;

struct ListNode {
    int val;
    ListNode *next;
    ListNode(int x) : val(x), next(NULL) {}
};

class Solution {
public:
    ListNode* deleteDuplicates(ListNode* head);
};

ListNode *Solution::deleteDuplicates(ListNode *head) {
    if (head == nullptr) return head;
    ListNode *prev = head, *curr = head;
    while (curr != nullptr) {
        int val = prev->val;
        while (curr != nullptr && curr->val == val) curr = curr->next;
        if (curr != nullptr) {
            prev->next->val = curr->val;
            prev = prev->next;
        }
    }
    prev->next = nullptr;
    return head;
}


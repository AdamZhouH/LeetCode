/**
 * Definition for singly-linked list.
 * struct ListNode {
 *     int val;
 *     ListNode *next;
 *     ListNode() : val(0), next(nullptr) {}
 *     ListNode(int x) : val(x), next(nullptr) {}
 *     ListNode(int x, ListNode *next) : val(x), next(next) {}
 * };
 */
class Solution {
public:
    ListNode* reverseBetween(ListNode* head, int left, int right) {
        ListNode *dummy = new ListNode(); dummy->next = head;
        ListNode *ptr1 = dummy, *ptr2 = dummy;
        
        while (--left) { ptr1 = ptr1->next; }
        while (right--) { ptr2 = ptr2->next; }
        
        ListNode *tmpHead1 = ptr1->next;
        ListNode *tmpHead2 = ptr2->next;
        ptr1->next = nullptr;
        ptr2->next = nullptr;
        
        ListNode *ptr = tmpead1;
        ListNode *newHead = nullptr;
        ListNode *newTail = nullptr;
        
        while (ptr) {
            if (newHead == nullptr || newTail == nullptr) {
                newHead = ptr;
                newTail = ptr;
                ptr = ptr->next;
                newHead->next = nullptr;
            } else {
                ListNode *tmp = ptr->next;
                ptr->next = newHead;
                newHead = ptr;
                ptr = tmp;
            }
        }
        ptr1->next = newHead;
        newTail->next = tmpHead2;
        return dummy->next;
    }
};H

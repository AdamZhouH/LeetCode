class Solution {
public:
    ListNode* rotateRight(ListNode* head, int k) {
        if (head == nullptr) return head;
        int len = 0;
        ListNode *ptr = head;
        while (ptr) {
            len++;
            ptr = ptr->next;
        }
        k = k % len;
        if (k == 0) return head;
        int cnt = len - k - 1;
        ptr = head;
        while (cnt--) {
            ptr = ptr->next;
        }
        ListNode *newHead = ptr->next;
        ptr->next = nullptr;
        ListNode *tail = newHead;
        while (tail->next) {
            tail = tail->next;
        }
        tail->next = head;
        return newHead;
    }
};
#include <iostream>
#include <vector>
#include <utility>
using namespace std;

struct ListNode {
    int val;
    ListNode *next;
    ListNode(int x) : val(x), next(nullptr) { }
};

class Solution {
public:
    ListNode* reverseKGroup(ListNode* head, int k);
};

// 当k==1实际上没有反转
ListNode* Solution::reverseKGroup(ListNode *head, int k) {
    if (head == nullptr || k == 1) return head;
    auto ptr = head;
    int cnt = 1;
    while (ptr != nullptr && cnt < k) ptr = ptr->next, cnt++;
    if (ptr == nullptr) return head; 
    auto other = reverseKGroup(ptr->next, k);
    // 反转当前的k个节点
    // 这里的ptr->next = nullptr是一个小trick，避免在翻转过程中还需要考虑元素个数
    ListNode *newhead = nullptr; ptr->next = nullptr;
    auto curr = head;
    while (curr != nullptr) {
        auto tmp = curr->next;
        curr->next = newhead;
        newhead = curr;
        curr = tmp;
    }
    head->next = other;
    return newhead;
}

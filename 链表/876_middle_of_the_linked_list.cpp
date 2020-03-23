/**
 * Definition for singly-linked list.
 * struct ListNode {
 *     int val;
 *     ListNode *next;
 *     ListNode(int x) : val(x), next(NULL) {}
 * };
 */
// 这道题目使用双指针
// 题目确定链表有头节点，并且非空，因此省去判空的情况
class Solution {
public:
    ListNode* middleNode(ListNode* head) {
        ListNode *slow = head;
        ListNode *fast = head;
        while (fast && fast->next) {
            slow = slow->next;
            fast = fast->next->next;
        }
        return slow;
    }
};

// 题目比较坑，说好了带head节点，结果意思都不明确。判定是按照没有头节点的情况来的
// 如果真的带头节点，那么必须判断fast和fast->next哪一个为空。
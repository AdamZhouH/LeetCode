class Solution {
public:
    bool isPalindrome(ListNode* head);
};

// O(n)事件复杂度, O(1)空间复杂度的算法很容易想到，但是写的时候要小心
// 两遍遍历，找到长度和中间节点
// 一遍遍历，逆序前半段链表
// 然后同时遍历两个链表即可
// 时间复杂度在常数次遍历，空间复杂度最多需要常数个辅助指针
// 找链表中间节点也可以使用双指针来寻找，但是需要知道链表的节点个数的奇偶性以及中间节点的前一个节点，因此还是遍历两遍直接找比较好
bool Solution::isPalindrome(ListNode *head) {
    if (head == nullptr) return true;
    // 计算长度
    int count = 0;
    ListNode *ptr = head;
    while (ptr) { count++; ptr = ptr->next; }
    if (count == 1) return true;
    
    // 找中间节点，并分割出两个链表，注意记录中间节点的前一个节点
    ListNode *prev = nullptr, *curr = head;
    int len = count / 2;
    while (len--) { prev = curr, curr = curr->next; }
    ListNode *tail = prev, *l2; 
    tail->next = nullptr;  // 这一步是为了后面逆置方便，避免繁琐判断，直接在tail处，就将两个链表断开
    if (count % 2)  l2 = curr->next;
    else l2 = curr;
    
    // 第一部分链表逆置
    ListNode *l1 = nullptr;
    while (head) {
        ListNode *tmp = head->next;
        head->next = l1;
        l1 = head;
        head = tmp;
    }
    
    // 两个链表同时遍历
    while (l1 != nullptr || l2 != nullptr) {
        if (l1 == nullptr || l2 == nullptr) return false;
        if (l1->val != l2->val) return false;
        l1=l1->next, l2 = l2->next;
    }
    return true;
}
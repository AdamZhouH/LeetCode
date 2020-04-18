#include <string>
#include <vector>
#include <stack>
#include <string>
using namespace std;

class Solution {
public:
    ListNode* addTwoNumbers(ListNode* l1, ListNode* l2);
};

// 利用两个栈，保存链表遍历结果，然后利用头插法建立新链表
ListNode *Solution::addTwoNumbers(ListNode *l1, ListNode *l2) {
    if (l1->val == 0) return l2;
    if (l2->val == 0) return l1;
    stack<int> s1, s2;
    while (l1 != nullptr) { s1.push(l1->val); l1 = l1->next; }
    while (l2 != nullptr) { s2.push(l2->val); l2 = l2->next; }
    // 构造返回链表
    int flag = 0;
    ListNode *head = nullptr;
    while (!s1.empty() && !s2.empty()) {
        int a = s1.top(); s1.pop();
        int b = s2.top(); s2.pop();
        ListNode *newHead = new ListNode((a + b + flag) % 10);
        flag = (a + b + flag) / 10;
        newHead->next = head; head = newHead;
    }
    // 剩余数字
    if (s1.empty()) {
        while (!s2.empty()) {
            ListNode *newHead = new ListNode((s2.top() + flag) % 10);
            flag = (s2.top() + flag) / 10; s2.pop();
            newHead->next = head;
            head = newHead;
        }
    } else if (s2.empty()) {
        while (!s1.empty()) {
            ListNode *newHead = new ListNode((s1.top() + flag) % 10);
            flag = (s1.top() + flag) / 10; s1.pop();
            newHead->next = head;
            head = newHead;
        }
    }
    // 处理最后的flag
    if (flag) {
        ListNode *newHead = new ListNode(flag);
        newHead->next = head;
        head = newHead;
    }
    return head;
}

// 这题的死里很简单，就是利用栈，因为这题的链表保存的顺序和实际数字的顺序一致
// 但实际的加法器则是从尾部开始相加的，因此用栈先保存遍历的结果，然后构造新链表
// 其实上面这一段代码可以简化，不用写这么复杂，而且分开判断，还容易出错
// 实际上终止的条件是，当两个栈都为空，并且进位也为0，则表示没有新的节点了
ListNode *addTwoNumbers(ListNode *l1, ListNode *l2) {
    if (l1 == nullptr) return l2;
    if (l2 == nullptr) return l1;
    stack<int> s1, s2;
    while (l1 != nullptr) { s1.push(l1->val); l1 = l1->next; }
    while (l2 != nullptr) { s2.push(l2->val); l2 = l2->next; }
    int carray = 0;
    ListNode *head = nullptr;
    while (!s1.empty() || !s2.empty() || carray != 0) {
        int sum = carray;
        if (!s1.empty()) { sum += s1.top(); s1.pop(); }
        if (!s2.empty()) { sum += s2.top(); s2.pop(); }
        ListNode *node = new ListNode(sum % 10);
        node->next = head; head = node;
        carray = sum / 10;
    }
    return head;
}




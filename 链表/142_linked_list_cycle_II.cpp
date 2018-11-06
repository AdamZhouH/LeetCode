#include <iostream>
#include <algorithm>
#include <vector>
#include <unordered_set>
#include <string>
using namespace std;

// 给定一个链表，返回链表开始入环的第一个节点, 如果链表无环，则返回 null
// 并不允许修改给定的链表

// 暴力思路
// 仍然是双指针，判断链表是否存在环，同时，针对于存在环的情况
// 首先，我们可以找到快慢指针的相遇点
// 从链表头结点到相遇点的路径上，一定包含环的入口节点
// 那么记录从头结点到相遇点的路径
// 然后再从相遇点出发，往前走，每次判断当前一步的节点是否在之前的路径中
// 如果第一个存在的节点就是环的入口点

// 上述算法在Leetcode提交后，运行时间为24ms，显然效率比较低的
// 考虑大神的另一种算法
// 当相遇之后，一个指针从头开始走，另一个指针从相遇点开始走，每次都走一步
// 则它们的下一个相遇点就是链表的环的入口
// 数学证明？需要思考下，代码实现是比较简单的

class Solution {
public:
    ListNode *detectCycle(ListNode *head);
    ListNode *findEntry(ListNode *head, ListNode *meetPoint);
};

ListNode *Solution::detectCycle(ListNode *head) {
    if (!head)
        return nullptr;
    ListNode *slow = head, *fast = head;
    while (head && fast) {
        slow = slow->next;
        fast = fast->next;
        if (fast && fast->next) {
            fast = fast->next;
            // 找到相遇点
            if (fast == slow) {
                return findEntry(head, slow);
            }
        } else {
            return nullptr;
        }
    }
}

ListNode *Solution::findEntry(ListNode *head, ListNode *meetPoint) {
    unordered_set<ListNode *> path;
    path.insert(meetPoint);
    ListNode *ptr = head;
    while (ptr != meetPoint) {
        path.insert(ptr);
        ptr = ptr->next;
    }
    // 从相遇点开始往下走，找到第一个存在于之前路径中的点就是环的入口
    ptr = meetPoint->next;
    while (true) {
        if (path.find(ptr) != path.end()) {
            return ptr;
        } else {
            ptr = ptr->next;
        }
    }
}

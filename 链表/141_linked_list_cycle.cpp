// 判断链表是否存在环
// 双指针（快慢指针思路）
#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

// 快慢指针，判断链表是否存在环（本质上，使用快慢指针其实是抽象为追及问题）
// 可以很容易证明，一个指针走一步，另一个走两步，如果存在环，则快指针一定可以追上慢指针

// 比较基础简单的写法，但是代码不是很优雅
// Leetcode上比较好的写法是，预先添加一个头结点
// 这样效率比较高，之后把这个算法完善即可

struct ListNode {
    int val;
    ListNode *next;
    ListNode(int x) : val(x), next(NULL) {}
};

class Solution {
public:
    bool hasCycle(ListNode *head);
};

bool Solution::hasCycle(ListNode *head) {
    if (!head)
        return false;
    ListNode *slow = head, *fast = head;
    // 慢指针每次一步，快指针每次两步
    while (slow && fast) {
        slow = slow->next;
        fast = fast->next;
        if (fast && fast->next) {
            fast = fast->next;
            if (fast == slow) {
                return true;
            }
        } else {
            return false;
        }
    }
}

#include <vector>
#include <string>
#include <algorithm>
using namespace std;

// 找链表公共节点的非常优雅的代码和算法
// 之前写这题，都是先两次遍历分别拿到链表的长度，计算长度之差
// 然后长链表先走若干步，然后再两个指针同步走，最后找到相交的节点
// 
//
// 这题关键点也在于：如何抹平长度差距
// 给出的算法实现得非常优雅
// 直接让两个指针从开始就一直走，那么短链表指针，肯定能先走到尾部
// 此时长链表指针还没有走到尾部
// 让短指针从长链表头开始，遍历长链表
// 当长链表最开始那个指针走到长链表尾部时候，此时短链表指针也还在长链表上走
// 下一步让长链表指针从短链表头开始遍历短链表
// 此时，长链表指针走完了整个长链表的长度，并且短链表指针此时已经走完了整个短链表长度
// 并且已经在长链表上走了一小段距离，可以知道，这小段距离就是两个链表的长度之差
// 此时，短链表指针在遍历长链表
// 长链表指针在遍历短链表
// 两者相当于交换了下遍历的链表，但是长度差被抹平了
//
// 这种做法避免了手动找到长度差，代码实现上非常优雅
struct ListNode {
    int val;
    ListNode *next;
    ListNode(int x) : val(x), next(nullptr) { }
};

class Solution {
public:
    ListNode *getIntersectionNode(ListNode *headA, ListNode *headB) {
        ListNode *p1 = headA, *p2 = headB;
        while (p1 != p2) {
            p1 = (p1 == nullptr) ? headB : p1->next;
            p2 = (p2 == nullptr) ? headA : p2->next;
        }
        return p1;
    }
};

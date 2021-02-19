#include <vector>
#include <string>
#include <iostream>
#include <unordered_set>
using namespace std;

struct ListNode {
    int val;
    ListNode *next;
    ListNode(int x) : val(x), next(NULL) {}
};

// 感觉是一道easy题?
class Solution {
public:
    int numComponents(ListNode* head, vector<int>& G) {
        if (head == nullptr) return 0;
        ListNode *ptr = head;
        int cnt = 0;
        unordered_set<int> record(G.begin(), G.end());
        // 比较丑陋的写法
        // while (ptr) {
        //     int flag = false;
        //     while (ptr && record.find(ptr->val) != record.end()) {
        //         flag = true;
        //         ptr = ptr->next;
        //     }
        //     if (flag) cnt++;
        //     if (!ptr) break;
        //     else ptr = ptr->next;
        // }
        while (ptr) {
            if (record.find(ptr->val) != record.end()) {
                if (!ptr->next || record.find(ptr->next->val) == record.end()) {
                    cnt++;
                }
            }
            ptr = ptr->next;
        }
        return cnt;
    }
};

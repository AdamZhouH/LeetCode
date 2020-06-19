#include <string>
#include <vector>
#include <iostream>
using namespace std;

class Solution {
public:
    int getDecimalValue(ListNode* head) {
        long long ans = 0;
        while (head) {
            ans = ans * 2 + head->val;
            head = head->next;
        }
        return ans;
    }
};

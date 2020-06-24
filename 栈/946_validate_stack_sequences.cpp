#include <stack>
#include <iostream>
#include <vector>
#include <algorithm>
#include <string>
using namespace std;

class Solution {
public:
    bool validateStackSequences(vector<int>& pushed, vector<int>& popped) {
        // 直接栈模拟即可
        if (pushed.empty()) return true;
        stack<int> stk;
        int i = 0, j = 0;
        for (int j = 0; j < popped.size(); j++) {
            while (stk.empty() || stk.top() != popped[j] && i < pushed.size())
                stk.push(pushed[i++]);
            if (stk.empty() || stk.top() != popped[j]) return false;
            else stk.pop();
        }
        return true;
    }
};

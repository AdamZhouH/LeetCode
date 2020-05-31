#include <stack>
#include <vector>
#include <iostream>
#include <algorithm>
#include <queue>
using namespace std;

class Solution {
public:
    // 除了暴力的做法，很明显的单调递减栈问题，找下一个更大元素，这里求间隔
    // 那么单调栈直接入栈下标即可
    // 当然也可以暴力，不过时间复杂度肯定是O(n^2)了
    vector<int> dailyTemperatures(vector<int>& T) {
        vector<int> ret(T.size(), 0);
        stack<int> stk;
        for (int i = 0; i < T.size(); i++) {
            while (!stk.empty() && T[stk.top()] < T[i]) {
                int idx = stk.top(); stk.pop();
                ret[idx] = i - idx;
            }
            stk.push(i);
        }
        return ret;
    }
};


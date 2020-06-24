#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <stack>
#include <climits>
using namespace std;

// 1.动态规划
// 2.两次扫描
// 3.暴力求解

class Solution {
public:
    int longestValidParentheses(string s) {
        if (s.size() <= 1) return 0;
        vector<int> dp(s.size(), 0);
        int ms = 0;
        for (int i = 1; i < s.size(); i++) {
            if (s[i] == '(') continue;
            if (s[i-1] == '(') dp[i] = (i-2 >= 0 ? dp[i-2] : 0) + 2;
            else if (i-dp[i-1]-1 >= 0 && s[i-dp[i-1]-1] == '(') {
                dp[i] = 2 + dp[i-1] + (i-dp[i-1]-2 >= 0 ? dp[i-dp[i-1]-2]: 0);
            }
            ms = max(ms, dp[i]);
        }
        return ms;
    }
};

#include <iostream>
#include <vector>
#include <string>
using namespace std;

// 动态规划
class Solution {
public:
    bool isMatch(string s, string p) {
        if (p.empty()) return s.empty();
        int m = s.size(), n = p.size();
        vector<vector<int>> dp(m+1, vector<int> (n+1, 0));
        dp[0][0] = 1;
        for (int j = 1; j <= n; j++) {
            if (p[j-1] != '*') dp[0][j] = 0;
            else dp[0][j] = dp[0][j-1];
        }
        for (int i = 1; i <= m; i++) {
            for (int j = 1; j <= n; j++) {
                if (p[j-1] == s[i-1] || p[j-1] == '?') {
                    dp[i][j] = dp[i-1][j-1];
                } else if (p[j-1] != '*') {
                    dp[i][j] = 0;
                } else {
                    //for (int k = 0; k <= i; k++) dp[i][j] = dp[i][j] | dp[k][j-1];
                    dp[i][j] = dp[i][j-1] || dp[i-1][j];
                }
            }
        }
        return dp[m][n];
    }
};

// 还有迭代版本的回溯思路，时间复杂度和空间复杂度都更优

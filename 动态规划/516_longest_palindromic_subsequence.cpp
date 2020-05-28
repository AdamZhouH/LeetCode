#include <iostream>
#include <vector>
#include <algorithm>
#include <string>
using namespace std;

class Solution {
public:
    // 相比于回文串，子序列不会连续
    // 递推公式有些变化
    // dp[i][j]表示[i:j]子串的最长回文子序列长度
    // dp[i][j] = max{dp[i+1][j], dp[i][j-1], dp[i+1][j-1]+2(if s[i]==s[j])}
    int longestPalindromeSubseq(string s) {
        if (s.size() <= 1) return s.size();
        int n = s.size(), maxlen = INT_MIN;
        vector<vector<int>> dp(n, vector<int>(n, 0));
        for (int i = n-1; i >= 0; i--) {
            for (int j = i; j < n; j++) {
                if (i == j) dp[i][j] = 1;
                else if (i == j-1) dp[i][j] = (s[i] == s[j]) ? 2:1;
                else if (s[i] == s[j]) dp[i][j] = max({dp[i+1][j], dp[i][j-1], 2 + dp[i+1][j-1]}); 
                else dp[i][j] = max({dp[i+1][j], dp[i][j-1]});
                maxlen = max(maxlen, dp[i][j]);
            }
        }
        return maxlen;
    }
};
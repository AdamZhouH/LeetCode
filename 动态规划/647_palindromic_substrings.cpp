#include <iostream>
#include <string>
#include <vector>
#include <string>
using namespace std;

// 这题没有啥意义，完全就是最长回文串的思路来做就行，dp优化暴力即可
class Solution {
public:
    int countSubstrings(string s) {
        if (s.size() <= 1) return s.size();
        vector<vector<int>> dp(s.size(), vector<int>(s.size(), 0));
        int ret = 0, n = s.size();
        for (int i = n-1; i >= 0; i--) {
            for (int j = i; j < n; j++) {
                if (i == j) dp[i][j] = 1;
                else if (i == j-1) dp[i][j] = s[i]== s[j];
                else dp[i][j] = dp[i+1][j-1] && s[i]==s[j];
                if (dp[i][j]) ret++;
            }
        }
        return ret;
    }
};
#include <iostream>
#include <vector>
#include <string>
using namespace std;

class Solution {
public:
    int minimumDeleteSum(string s1, string s2) {
        // 类似编辑距离的动态规划思想
        // dp[i][j]表示使s1[0:i]和s2[0:j]相同需要删除的ASCII值的最小和
        if (s1.empty() && s2.empty()) return 0;
        if (s1.empty() || s2.empty()) {
            if (s1.empty()) s1.swap(s2);
            int ans = 0;
            for (auto c: s1) ans += c;
            return ans;
        }
        vector<vector<int>> dp(s1.size()+1, vector(s2.size()+1, 0));
        int sum = 0;
        for (int j = 1; j <= s2.size(); j++) sum += s2[j-1], dp[0][j] = sum;
        sum = 0;
        for (int i = 1; i <= s1.size(); i++) sum += s1[i-1], dp[i][0] = sum;
        // 构造dp数组
        for (int i = 1; i <= s1.size(); i++) {
            for (int j = 1; j <= s2.size(); j++) {
                if (s1[i-1] == s2[j-1]) dp[i][j] = dp[i-1][j-1];
                else dp[i][j] = min(dp[i-1][j]+s1[i-1], dp[i][j-1]+s2[j-1]);
            }
        }
        return dp[s1.size()][s2.size()];
    }
};

#include <vector>
#include <string>
using namespace std;

class Solution {
public:
    int longestCommonSubsequence(string text1, string text2) {
        if (text1.empty() || text2.empty()) return 0;
        vector<vector<int>> dp(text1.size()+1, vector<int> (text2.size()+1, 0));
        for (int i = 1; i <= text1.size(); i++) {
            for (int j = 1; j <= text2.size(); j++) {
                if (text1[i-1] == text2[j-1]) dp[i][j] = dp[i-1][j-1] + 1;
                else dp[i][j] = max({dp[i][j-1], dp[i-1][j], dp[i-1][j-1]});
                // else dp[i][j] = max(dp[i][j-1], dp[i-1][j]); is all ok in fact
            }
        }
        return dp[text1.size()][text2.size()];
    }
};

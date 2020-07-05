#include <vector>
#include <algorithm>
using namespace std;

class Solution {
public:
    // 能够想到dp做法（比较简单）
    int findLength(vector<int>& A, vector<int>& B) {
        int m = A.size(), n = B.size();
        vector<vector<int>> dp(m+1, vector<int>(n+1));
        int ms = 0;
        for (int i = 1; i <= m; i++) {
            for (int j = 1; j <= n; j++) {
                if (A[i-1] == B[j-1]) dp[i][j] = 1 + dp[i-1][j-1];
                ms = max(ms, dp[i][j]);
            }
        }
        return ms;
    }
};

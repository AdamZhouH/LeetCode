#include <iostream>
#include <vector>
#include <string>
using namespace std;

class Solution {
public:
    int numSubmat(vector<vector<int>>& mat) {
        int m = mat.size(), n = mat[0].size();
        vector<vector<int>> dp(m+1, vector<int> (n+1, 0));
        for (int i = 1; i <= m; i++) {
            for (int j = 1; j <= n; j++)
                dp[i][j] = (mat[i-1][j-1] == 0) ? 0 : 1 + dp[i][j-1];
        }
        int cnt = 0;
        for (int i = 1; i <= m; i++) {
            for (int j = 1; j <= n; j++) {
                int minHeight = INT_MAX;
                for (int k = i; k >= 1; k--) {
                    minHeight = min(minHeight, dp[k][j]);
                    cnt += minHeight;
                    if (minHeight == 0) break;
                }
            }
        }
        return cnt;
    }
};

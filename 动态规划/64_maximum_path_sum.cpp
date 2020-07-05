#include <iostream>
#include <string>
#include <vector>
using namespace std;

class Solution {
public:
    int minPathSum(vector<vector<int>>& grid) {
        if (grid.empty() || grid[0].empty()) return 0;
        vector<vector<int>> dp(grid.size()+1, vector<int> (grid[0].size()+1, 0));
        for (int j = 1; j <= grid[0].size(); j++) dp[1][j] = dp[1][j-1]+grid[0][j-1];
        for (int i = 1; i <= grid.size(); i++) dp[i][1] = dp[i-1][1]+grid[i-1][0];
        for (int i = 2; i <= grid.size(); i++) {
            for (int j = 2; j <= grid[0].size(); j++) {
                dp[i][j] = min(dp[i-1][j], dp[i][j-1]) + grid[i-1][j-1];
            }
        }
        return dp[grid.size()][grid[0].size()];
    }
};

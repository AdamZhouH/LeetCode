#include <vector>
using namespace std;

class NumMatrix {
public:
    // 同样，也是类似前缀和的思想，但是和一维有所区别
    // dp[m][n]表示从[0][0]到[m][n]的矩阵的和
    // 题目要求的区域可以看成是一个大区域，减去若干小区域
    NumMatrix(vector<vector<int>>& matrix) {
        if (matrix.empty() || matrix[0].empty()) return;
        int m = matrix.size();
        int n = matrix[0].size();
        
        dp = std::move(vector<vector<int>>(m + 1, vector<int>(n + 1, 0)));
        // 大区域减去左边和上边两个小区域，由于重复减了公共的左上角区域，因此还需要加回来
        // 先利用前缀和思想，统计每个矩形的和
        // 统计每个矩形的和利用动态规划思想，必须先统计每个点所在的行的左半部分和列的上半部分的累加和
        // 其实可以两次遍历，第一次按照行遍历，第二次按照列遍历
        // 完后就是统计到的每个子矩阵的和
        int currSum = 0;
        // ??按照行遍历
        vector<vector<int>> row = dp;
        for (int i = 1; i <= m; i++) {
            for (int j = 1; j <= n; j++) {
                row[i][j] = row[i][j-1] + matrix[i-1][j-1]; 
            }
        }
    
        // 再按照列遍历
        vector<vector<int>> col = dp;
        for (int j = 1; j <= n; j++) {
            for (int i = 1; i <= m; i++) {
                col[i][j] += col[i-1][j] + matrix[i-1][j-1];
            }
        } 
    
        // 统计子矩阵的和
        for (int i = 1; i <= m; i++) {
            for (int j = 1; j <= n; j++) {
                dp[i][j] = dp[i-1][j-1] + row[i][j] + col[i][j] - matrix[i-1][j-1]; 
            }
        }
    }
    
    int sumRegion(int row1, int col1, int row2, int col2) {
        if (dp.empty()) return 0;
        return 
            dp[row2+1][col2+1] - 
            dp[row1][col2+1] - 
            dp[row2+1][col1] + 
            dp[row1][col1];
    }
private:
    vector<vector<int>> dp;
};

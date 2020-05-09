#include <vector>
#include <algorithm>
#include <iostream>
#include <string>
#include <utility>
using namespace std;

class Solution {
public:
    int maximalRectangle(vector<vector<char>>& matrix);
};

// 转化为第84题，求最大矩形面积即可，依次对每一行执行84题的计算最大矩形面积的方法
// 可以用动态规划或者可以用单调栈计算每行的最大矩形面积

// 单调栈的解法后续会补充上来
int Solution::maximalRectangle(vector<vector<char>>& matrix) {
    if (matrix.size() == 0 || matrix[0].size() == 0) return 0;
    int m = matrix.size(), n = matrix[0].size();
    vector<vector<int>> dp(m, vector<int>(n,0));
    for (int i = 0; i < m; i++) {
        for (int j = 0; j < n; j++) {
            if (matrix[i][j] == '1')
                dp[i][j] = (j >= 1 ? dp[i][j-1] + 1 : 1);
        }
    }
    int area = 0;
    for (int i = 0; i < m; i++) {
        for (int j = 0; j < n; j++) {
            if (matrix[i][j] == '0') continue;
            int currlen = dp[i][j];
            for (int k = i; k >= 0 && matrix[k][j] == '1'; k--) {
                currlen = min(currlen, dp[k][j]);
                area = max(area, (i-k+1) * currlen);
            }
        }
    }
    return area;
}
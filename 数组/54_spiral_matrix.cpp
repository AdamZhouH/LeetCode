#include <iostream>
#include <vector>
using namespace std;

class Solution {
public:
    vector<int> spiralOrder(vector<vector<int>>& matrix);
};

// 思路，从外层往里层，层层遍历即可
// 每一层的起始点为(i,j)则上右下左四个方向分别遍历元素
// 上为第i行，第j到第n-j-1列
// 右为第n-j列，第i行到第m-i-1行
// 下为第m-i-1行，第n-j-1列到第j列
// 左为第j列，第m-i-1行到第i行

vector<int> Solution::spiralOrder(vector<vector<int>>& matrix) {
    vector<int> ret;
    if (matrix.empty() || matrix[0].empty()) return ret;
    int m = matrix.size(), n = matrix[0].size();
    int i = 0, j = 0;
    while (i <= m-i-1 && j <= n-j-1) {
        //分别打印上右下左侧的元素
        for (int k = j; k <= n-j-1; k++) ret.push_back(matrix[i][k]);
        for (int k = i+1; k <= m-i-1; k++) ret.push_back(matrix[k][n-j-1]);
        for (int k = n-j-2; k >= j && m-i-1 > i ; k--) ret.push_back(matrix[m-i-1][k]);
        for (int k = m-i-2; k > i && j < n-j-1; k--) ret.push_back(matrix[k][j]);
    }
    return ret;
}

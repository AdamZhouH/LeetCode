#include <iostream>
#include <vector>
#include <algorithm>
#include <string>
#include <map>
#include <list>
#include <utility>
#include <numeric>
#include <memory>
using namespace std;

class Solution {
public:
    int maximalSquare(vector<vector<char>> &matrix);
};

// 动态规划思路
// 当遇到一个1，考虑以它为正方形右下角点的正方形的最大边长
// 假设当前节点为(i,j), dp[i][j]表示以(i,j)为右下角节点的正方形
// 的最大边长，则dp[i][j] = 1 + min{dp[i-1][j-1], dp[i][j-1], dp[i-1][j]}
int Solution::maximalSquare(vector<vector<char>> &matrix) {
    if (matrix.empty() || matrix[0].empty()) return 0;
    int maxSide = 0;
    vector<vector<int>> dp(matrix.size(), vector<int> (matrix[0].size(), 0));
    for (int i = 0; i < matrix.size(); i++) {
        for (int j = 0; j < matrix[0].size(); j++) {
            if (matrix[i][j] == '1') {
                dp[i][j] = 1 + min({
                        i-1>=0&&j-1>=0 ? dp[i-1][j-1]:0,
                        i-1>=0 ? dp[i-1][j]:0,
                        j-1>=0 ? dp[i][j-1]:0
                        });
                maxSide = max(maxSide, dp[i][j]);
            }
        }
    }
    return maxSide * maxSide;
}

// 再来个暴力解法，每当遇到一个1，则求以当前1为左上角节点的最大正方形的边长
// 求正方形的边长的方法如下：
// 类似于BFS遍历，我们从最开始的这个节点作为BFS的源点，层层往外扩散，每一层都必须所有的元素都是1
// 才可以往下一层扩散，一旦遇到一个不是1的节点，说明不能再继续往外层扩散
// 便得到了以最开始的1为左上角节点的最大正方形的边长
// 每一层包括一行和一列
//
int check(int m, int n, int i, int j, vector<vector<char>> &matrix) {
    int len = 1;
    while (i+len < m && j+len < n) {
        bool flag = true;
        for (int p = i; p <= i+len; p++) {
            if (matrix[p][j+len] == '0') {
                flag = false;
                break;
            }
        }
        if (!flag) break;
        for (int p = j; p <= j+len; p++) {
            if (matrix[i+len][p] == '0') {
                flag = false;
                break;
            }
        }
        if (!flag) break;
        else len++;
    }
    return len;
}

int maximalSquare(vector<vector<char>> &matrix) {
    if (matrix.empty() || matrix[0].empty()) return 0;
    int m = matrix.size(), n = matrix[0].size();
    int maxside = 0;
    for (int i = 0; i < m; i++) {
        for (int j = 0; j < n; j++) {
            if (matrix[i][j] == '1')
                maxside = max(maxside, check(m,n,i,j,matrix));
        }
    }
    return maxside * maxside;
}



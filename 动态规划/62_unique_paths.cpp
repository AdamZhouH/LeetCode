// 给定一个矩阵，求解从左上起始点到右下终点的可能路径总数
// 每一步只能往下或者网右边走
// 很显然，考虑动态规划，找到子问题，先找递推公式，然后递归转迭代，确定初始状态
// 考虑倒数第二步，只能是终点上方往下走，或者终点左边往右走
// 对于矩阵中每个点，给定(i, j)表示其位置，给定f(i, j)表示，从起点到(i, j)的路径数
// 则，对于f(i, j)有，f(i, j) = f(i-1, j) + f(i, j - 1)
// 初始状态，第一层的，全部为1 ，第一列的，全部为1(根据定义可以得知)

#include <iostream>
#include <algorithm>
#include <vector>
using namespace std;

class Solution {
public:
    int uniquePaths(int m, int n);
};

int Solution::uniquePaths(int m, int n) {
    vector<vector<int>> dp(m);
    for_each(dp.begin(), dp.end(), [n](vector<int> &vec) {
    	vec.resize(n);
    });
    for (int i = 0; i < m; i++)
    	for (int j = 0; j < n; j++) {
    		if (i == 0 || j == 0)
    			dp[i][j] = 1;
    		else
    			dp[i][j] = dp[i - 1][j] + dp[i][j - 1];
    	}
    return dp[m - 1][n - 1];
}

int main(void) {
	int m, n;
	Solution solution;
	while (cin >> m >> n) {
		cout << solution.uniquePaths(m, n) << endl;
	}
	return 0;
}
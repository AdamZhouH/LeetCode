// 在之前一道题目的基础上，加上了障碍物
// 基本思路还是差不多的，就是考虑更新 dp[i][j] = dp[i][j - 1] + dp[i - 1][j]时候
// 考虑本身是否是障碍物结点，如果是障碍物结点，那么直接置为0
// 还有一点容易疏忽的就是在初始化阶段（仅仅考虑第一行），我们考虑第一行，某一个结点不可达，那么同行的下一个结点必然也是不可达到
// 第一列同理


#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
using namespace std;

class Solution {
public:
    int uniquePathsWithObstacles(vector<vector<int>> &obstacleGrid);
};

int Solution::uniquePathsWithObstacles(vector<vector<int>> &obstacleGrid) {
	int rows = obstacleGrid.size();
	int cols = obstacleGrid[0].size();
	vector<vector<int>> dp(rows);
	for_each(dp.begin(), dp.end(), [cols](vector<int> &vec) {
		vec.resize(cols);
	});
	// 初始化第一行第一列，注意前一个结点不可达对于后续结点的影响
	for (int j = 0; j < cols; j++)
		if (obstacleGrid[0][j] == 1) {
			while (j < cols)
				dp[0][j++] = 0;
		}
		else
			dp[0][j] = 1;
	for (int i = 0; i < rows; i++)
		if (obstacleGrid[i][0] == 1) {
			while (i < rows)
				dp[i++][0] = 0;
		}
		else
			dp[i][0] = 1;
	// 从dp[1][1]开始填充dp数组
	for (int i = 1; i < rows; i++) {
		for (int j = 1; j < cols; j++) {
			if (obstacleGrid[i][j] == 1)
				dp[i][j] = 0;
			else 
				dp[i][j] = dp[i][j - 1] + dp[i - 1][j];
		}
	}
	return dp[rows - 1][cols - 1];
}

int main(void) {
	vector<vector<int>> obstacleGrid = {
//		{0, 0, 0},
//		{0, 1, 0},
//		{0, 0, 0}
		{1, 1}
	};
	Solution solution;
	cout << solution.uniquePathsWithObstacles(obstacleGrid) << endl;
	return 0;
}
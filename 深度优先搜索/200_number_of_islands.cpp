// 深度优先搜索
// 实际上，就是遍历一个图的过程，一个岛屿中的1就是一个图中互相联通的结点，联通方向不能是斜线
// 对于每个子图，遍历，同时把1改成0即可
// 最终得出子图个数就是岛屿的个数

#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

class Solution {
public:
	int numIslands(vector<vector<char>> &grid);
	void dfs(vector<vector<char>> &grid, int i, int j, int m, int n);
};

int Solution::numIslands(vector<vector<char>> &grid) {
	int m = grid.size();
	int n = grid[0].size();
	int count = 0;
	for (int i = 0; i < m; i++) {
		for (int j = 0; j < n; j++) {
			if (grid[i][j] == '1') {
				count++;
				dfs(grid, i, j, m, n);
			}
		}
	}
	return count;
}

void Solution::dfs(vector<vector<char>> &grid, int i, int j, int m, int n) {
	if (i >= m || i < 0 || j >= n || j < 0)
		return;
	if (grid[i][j] == '0')
		return;
	grid[i][j] = '0';
	dfs(grid, i, j - 1, m, n);
	dfs(grid, i, j + 1, m, n);
	dfs(grid, i + 1, j, m, n);
	dfs(grid, i - 1, j, m, n);	
}

int main(void) {
	Solution solution;
	vector<vector<char>> grid = {
		{'1','1','0','0','0'},
		{'1','1','0','0','0'},
		{'0','0','1','0','0'},
		{'0','0','0','1','1'}
	};
    cout << solution.numIslands(grid) << endl;
    return 0;
}
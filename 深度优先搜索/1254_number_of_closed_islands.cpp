#include <vector>
#include <iostream>
#include <algorithm>
#include <string>
using namespace std;

// 求封闭岛屿的个数
// 相比之前一道题目，题中要求了岛屿四周被水包围
// 那么岛屿的边缘肯定不能有任何一部分在整个框架的边缘
// 在遍历岛屿的同时，判断是否有岛屿中的小块在边缘上，如果存在则不符合条件，记录即可
class Solution {
public:
    int closedIsland(vector<vector<int>> &grid);
    void dfs(vector<vector<int>> &grid, int x, int y, bool &isInside);
private:
    vector<int> dx = {-1, 0, 1, 0};
    vector<int> dy = {0, 1, 0 , -1};
};

int Solution::closedIsland(vector<vector<int>> &grid) {
    if (grid.size() == 0 || grid[0].size() == 0) return 0;
    int ret = 0;
    int n = grid.size(), m = grid[0].size();
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            if (grid[i][j] == 0) {
                bool isInside = true;
                dfs(grid, i, j, isInside);
                if (isInside) ret++;
            }
        }
    }
    return ret;
}

void Solution::dfs(vector<vector<int>> &grid, int x, int y, bool &isInside) {
    int n = grid.size(), m = grid[0].size();
    if (x < 0 || x >= n || y < 0 || y >= m || grid[x][y] == 1) return;
    grid[x][y] = 1;
    // 当isInside没有置位时， 判断是否是边界格子，如果已经判断为非inside，就不用再判断标记了
    if (isInside) {
        if (x == (n - 1) || x == 0 || y == (m - 1) || y == 0)
            isInside = false;
    }
    for (int i = 0; i < 4; i++) {
        dfs(grid, x + dx[i], y + dy[i], isInside);
    }
}

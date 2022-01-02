#include <iostream>
#include <vector>
#include <algorithm>
#include <unordered_map>
#include <queue>
#include <utility>
using namespace std;

class Solution {
public:
    vector<vector<int>> colorBorder(vector<vector<int>>& grid, int row, int col, int color);
};

// 很显然，这是一道题目描述非常坑爹的Leetcode题
vector<vector<int>> Solution::colorBorder(vector<vector<int>>& grid, int row, int col, int color) {
    int m = grid.size();
    int n = grid[0].size();
    int originColor = grid[row][col];
    cout << m << "," << n << endl;

    queue<pair<int, int>> nodes;
    vector<vector<int>> record(m, vector<int>(n, 0));
    nodes.push({row, col});
    record[row][col] = 1;

    const vector<vector<int>> directions = {{0, 1}, {0, -1}, {-1, 0}, {1, 0}};
    while (!nodes.empty()) {
        auto node = nodes.front(); nodes.pop();
        bool border = false;
        for (int i = 0; i < directions.size(); i++) {
            int x = directions[i][0] + node.first;
            int y = directions[i][1] + node.second;
            if (x < 0 || x >= m || y < 0 || y >= n) continue;
            if (grid[x][y] != originColor && record[x][y] == 0) border = true;
            else if (record[x][y] == 0) { record[x][y] = 1; nodes.push({x, y}); }
        }
        border = border || (node.first == m - 1 ) || (node.second == n - 1) || (node.first == 0) || (node.second == 0);
        if (border) grid[node.first][node.second] = color;
    }
    return grid;
}


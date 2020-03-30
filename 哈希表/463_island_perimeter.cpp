#include <iostream>
#include <vector>
using namespace std;

// 水题
// 直接遍历即可，每次判断上下左右是否存在路地块，存在则每个方向都减去1的周长
// 或者说判断每块陆地格子周围如果是水格子的个数
class Solution {
public:
    int islandPerimeter(vector<vector<int>>& grid);
};

const int dx[] = {-1,0,1,0};
const int dy[] = {0,1,0,-1};

int Solution::islandPerimeter(vector<vector<int>>& grid) {
    if (grid.size() == 0 || grid[0].size() == 0) return 0;
    int ret = 0;
    int n = grid.size(), m = grid[0].size();
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            if (grid[i][j] == 1) {
                ret += 4;
                for (int k = 0; k < 4; k++) {
                    int x = i + dx[k];
                    int y = j + dy[k];
                    if (x >= 0 && x < n && y >= 0 && y < m && grid[x][y] == 1)
                        ret--;
                }
            }
        }
    }
    return ret;
}
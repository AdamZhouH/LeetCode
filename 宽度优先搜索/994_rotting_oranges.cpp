#include <iostream>
#include <vector>
#include <string>
#include <queue>
#include <algorithm>
using namespace std;

// 腐烂橘子问题，腐烂的橘子周围的正常橘子也会被腐烂，直到所有的可以被腐烂的橘子都被传染
// 相当于多个传染源，感染周围的正常橘子（四个方向，上下左右）
// 添加一个超级节点，实际上就是从这个超姐节点开始感染了第一批，然后第一批继续感染后续
// 因此是一个BFS问题，多个感染源从自身向四周扩散，经过N轮后扩散后，存在将所有正常橘子感染的可能性
// 题中要求几分钟，实际上就是几轮扩散后，不能再感染任何的橘子，此时判断是否还存在新鲜的橘子即可
// 0表示空格，感染源不会穿过空格去感染
// 1表示新鲜橘子，被感染后成为新的感染源
// 2表示腐烂橘子

class Solution {
public:
    int orangesRotting(vector<vector<int>>& grid);
};

const vector<int> dx = {-1, 0, 1, 0};
const vector<int> dy = {0, 1, 0, -1};

int Solution::orangesRotting(vector<vector<int>> &grid) {
    queue<pair<int, int>> q;
    int healthyOrange = 0;
    for (int i = 0; i < grid.size(); i++) {
        for (int j = 0; j < grid[0].size(); j++) {
            if (grid[i][j] == 2) 
                q.push({i,j});
            else if (grid[i][j] == 1)
                healthyOrange++;
        }
    }
    // 注意特殊输入，本身没有任何健康橘子的这种情况的处理
    if (healthyOrange == 0) return 0;
    // 多源BFS遍历，利用一个变量记录轮次数，同时已经感染的健康橘子更新为2，后续不再入队
    int level = 0;
    int n = grid.size(), m = grid[0].size();
    while (!q.empty()) {
        // 当前轮次的节点个数
        int cnt = q.size();
        while (cnt--) {
            auto node = q.front(); q.pop();
            // 若存在健康橘子则感染之
            for (int i = 0; i < 4; i++) {
                int x = node.first + dx[i], y = node.second + dy[i];
                if (x >= n || x < 0 || y >= m || y < 0 || grid[x][y] == 0 || grid[x][y] == 2) continue;
                // 否则感染新橘子，同时新橘子成为下一轮的感染源
                grid[x][y] = 2, healthyOrange--;
                q.push({x,y});
            }
        }
        level++;
    }
    if (healthyOrange != 0)
        return -1;
    // 这里是忽略的一点，当初始条件为全部橘子都是烂橘子时，返回0，表示需要0分钟即可
    // 因为我们的bfs迭代实际上是记录的bfs的层次数，第一层不用记录入level中
    return level - 1;
}

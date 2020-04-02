#include <iostream>
#include <vector>
using namespace std;

class Solution {
public:
    void gameOfLife(vector<vector<int>>& board);
    int getLiveNumber(vector<vector<int>>& board, int x, int y, int m, int n);
};

const int dx[] = {-1,-1,-1,0,0,1,1,1};
const int dy[] = {-1,0,1,-1,1,-1,0,1};

// 暴力遍历
void Solution::gameOfLife(vector<vector<int>> &board) {
    int m = board.size(), n = board[0].size();
    vector<vector<int>> ret = vector<vector<int>> (m, vector<int>(n, 0));
    for (int i = 0; i < m; i++) {
        for (int j = 0; j < n; j++) {
            int liveCell = getLiveNumber(board, i, j, m, n);
            if (board[i][j] == 0) {
                if (liveCell == 3)
                    ret[i][j] = 1;
                else
                    ret[i][j] = 0;
            } else {
                if (liveCell == 2 || liveCell == 3)
                    ret[i][j] = 1;
                else
                    ret[i][j] = 0;
            }
        }
    }
    board.swap(ret);
}

// 获取周围的活细胞个数
int Solution::getLiveNumber(vector<vector<int>> &board, int x, int y, int m, int n) {
    int cnt = 0;
    for (int i = 0; i < 8; i++) {
        int newx = x + dx[i], newy = y + dy[i];
        if (newx < 0 || newx >= m || newy < 0 || newy >= n || board[newx][newy] == 0) continue;
        cnt++;
    }
    return cnt;
}


// 思路二：
// 增加额外状态，3表示从0到1，4表示1到0
// 最后第二次遍历，还原0和1的状态

// 思路三，将int作为一个8bit的位图，最低位存储上一个状态，而次低位存储更新后的状态
// 最后第二次遍历还原即可
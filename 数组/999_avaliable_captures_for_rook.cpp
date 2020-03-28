#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
using namespace std;

class Solution {
public:
    int numRookCaptures(vector<vector<char>>& board);
};

int Solution::numRookCaptures(vector<vector<char>>& board) {
    int i = 0, j = 0, n = board.size();
    bool flag = false;
    for (i = 0; i < n; i++) {
        for (j = 0; j < n; j++) {
            if (board[i][j] == 'R') {
                flag = true;
                break;
            }
        }
        if (flag)
            break;
    }
    // search for pieces in four directions (left right up down)
    int left = 0, right = 0, up = 0, down = 0;
    int idx = j - 1;
    while (idx >= 0) {
        if (board[i][idx] == 'B') break;
        if (board[i][idx] == 'p') {
            left = 1;
            break;
        }
        idx--;
    }
    idx = j + 1;
    while (idx < n) {
        if (board[i][idx] == 'B') break;
        if (board[i][idx] == 'p') {
            right = 1;
            break;
        }
        idx++;
    }
    idx = i - 1;
    while (idx >= 0) {
        if (board[idx][j] == 'B') break;
        if (board[idx][j] == 'p') {
            up = 1;
            break;
        }
        idx--;
    }
    idx = i + 1;
    while (idx < n) {
        if (board[idx][j] == 'B') break;
        if (board[idx][j] == 'p') {
            down = 1;
            break;
        }
        idx++;
    }
    int ret = left + right + up + down;
    
    return ret;
}
int main(int argc, char *argv[]) {
    vector<vector<char>> board;
    string str;
    for (int i = 0; i < 8; i++) {
        cin >> str;
        board.push_back(vector<char> (str.begin(), str.end()));
    }
    Solution slu;
    cout << slu.numRookCaptures(board) << endl;
    return 0;
}

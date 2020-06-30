#include <vector>
#include <string>
#include <unordered_set>
#include <unordered_map>
using namespace std;

class Solution {
public:
    void solveSudoku(vector<vector<char>>& board) {
        vector<unordered_set<char>> rows(9, unordered_set<char>());
        vector<unordered_set<char>> cols(9, unordered_set<char>());
        vector<unordered_set<char>> grids(9, unordered_set<char>());
        vector<vector<char>> ret = board;
        vector<pair<int,int>> dots;  // 记录为'.'处的位置，这些位置需要递归查找可行解
        for (int i = 0; i < 9; i++) {
            for (int j = 0; j < 9; j++) {
                if (board[i][j] == '.'){
                    dots.push_back({i, j});
                    continue;
                }
                rows[i].insert(board[i][j]);
                cols[j].insert(board[i][j]);
                grids[(i/3)*3+j/3].insert(board[i][j]);
            }
        }
        if (dots.empty()) return;
        // 这里其实可以按照一定策略选择某个dots而不是顺序开始，我们应该每次选择当前状态下，候选个数最少的那个dots从而减少回溯的次数
        // 从而很大程度减少算法的时间消耗
        /**********************
        sort(dots.begin(), dots.end(), [&](pair<int,int> lhs, pair<int,int> rhs){
                    unordered_set<char> a = grids[(lhs.first/3)*3+lhs.second/3];
                    unordered_set<char> b = grids[(rhs.first/3)*3+rhs.second/3];
                    for (auto c: rows[lhs.first]) a.insert(c); for (auto c: cols[lhs.second]) a.insert(c);
                    for (auto c: rows[rhs.first]) b.insert(c); for (auto c: cols[rhs.second]) b.insert(c);
                    return a.size() > b.size();
                });
        // 拍了个序，反而更慢了，orz.....
        ***********************/
        dfs(board, rows, cols, grids, ret, dots, 0);
        board.swap(ret);
    }

    // 针对每一个为'.'处的位置进行递归回溯
    void dfs(vector<vector<char>> &board,  vector<unordered_set<char>> &rows, vector<unordered_set<char>> &cols,
             vector<unordered_set<char>> &grids, vector<vector<char>> &ret, vector<pair<int,int>> &dots, int i) {
        if (i >= dots.size()) { ret = board; return; }
        int x = dots[i].first, y = dots[i].second;
        for (char c = '1'; c <= '9'; c++) {
            if (!rows[x].count(c) && !cols[y].count(c) && !grids[(x/3)*3+y/3].count(c)) {
                rows[x].insert(c); cols[y].insert(c); grids[(x/3)*3+y/3].insert(c);
                board[x][y] = c;
                dfs(board, rows, cols, grids, ret, dots, i+1);
                board[x][y] = '.';
                rows[x].erase(c); cols[y].erase(c); grids[(x/3)*3+y/3].erase(c);
            }
        }
    }
};

// 该用bitset后，时间从300ms减少到28ms，666

class Solution2 {
public:
    void solveSudoku(vector<vector<char>>& board) {
        vector<bitset<9>> rows(9);
        vector<bitset<9>> cols(9);
        vector<bitset<9>> grids(9);
        vector<vector<char>> ret = board;
        vector<pair<int,int>> dots;  // 记录为'.'处的位置，这些位置需要递归查找可行解
        for (int i = 0; i < 9; i++) {
            for (int j = 0; j < 9; j++) {
                if (board[i][j] == '.'){
                    dots.push_back({i, j});
                    continue;
                }
                rows[i][board[i][j]-'1'] = true;
                cols[j][board[i][j]-'1'] = true;
                grids[(i/3)*3+j/3][board[i][j]-'1'] = true;
            }
        }
        if (dots.empty()) return;
        dfs(board, rows, cols, grids, ret, dots, 0);
        board.swap(ret);
    }

    // 针对每一个为'.'处的位置进行递归回溯
    void dfs(vector<vector<char>> &board,  vector<bitset<9>> &rows, vector<bitset<9>> &cols,
             vector<bitset<9>> &grids, vector<vector<char>> &ret, vector<pair<int,int>> &dots, int i) {
        if (i >= dots.size()) { ret = board; return; }
        int x = dots[i].first, y = dots[i].second;
        for (int c = 1; c <= 9; c++) {
            if (!rows[x][c-1] && !cols[y][c-1] && !grids[(x/3)*3+y/3][c-1]) {
                rows[x][c-1] = true; cols[y][c-1] = true; grids[(x/3)*3+y/3][c-1] = true;
                board[x][y] = c+'0';
                dfs(board, rows, cols, grids, ret, dots, i+1);
                board[x][y] = '.';
                rows[x][c-1] = false; cols[y][c-1] = false; grids[(x/3)*3+y/3][c-1] = false;
            }
        }
    }
};

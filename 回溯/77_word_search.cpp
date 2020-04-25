#include <iostream>
#include <vector>
#include <algorithm>
#include <queue>
#include <set>
#include <map>
#include <string>
#include <unordered_map>
#include <unordered_set>
using namespace std;

class Solution {
public:
    bool exist(vector<vector<char>>& board, string word);
	bool exist(vector<vector<char>>& board, string& word, int idx, int x, int y);
};

const int dx[] = {-1,0,1,0};
const int dy[] = {0,1,0,-1};

bool Solution::exist(vector<vector<char>>& board, string& word, int idx, int x, int y) {
	if (idx >= word.size()) return true; 
	int m = board.size(), n = board[0].size();
	if (x < 0 || x >= m || y < 0 || y >= n || board[x][y] == '#' || board[x][y] != word[idx]) return false;
	board[x][y] = '#';
	int flag = false;
	for (int i = 0; i < 4; i++) {
		int newx = x + dx[i], newy = y + dy[i];
		flag = exist(board, word, idx+1, newx, newy);
		if (flag) break;
	}
	board[x][y] = word[idx];
	return flag;
}

bool Solution::exist(vector<vector<char>>& board, string word) {
	if (word.empty()) return true;
	int m = board.size(), n = board[0].size();
	for (int i = 0; i < m; i++) {
		for (int j = 0; j < n; j++) {
			if (exist(board, word, 0, i, j)) return true;
		}
	}
	return false;
}


int main(int argc, char *argv[]) {
	vector<vector<char>> board = {{'A','B','C','E'},
								 {'S','F','C','S'},
								 {'A','D','E','E'}};
	Solution slu;
	string word = "ABCCDE";
	cout << slu.exist(board, word) << endl;
	return 0;
}
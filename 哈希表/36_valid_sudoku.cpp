#include <iostream>
#include <unordered_set>
#include <vector>
#include <algorithm>
using namespace std;

#define TEST
class Solution {
public:
	bool isValidSudoku(vector<vector<char>> &board);
};

bool Solution::isValidSudoku(vector<vector<char>> &board) {
	vector<unordered_set<char>> lines(9, unordered_set<char>());
	vector<unordered_set<char>> columns(9, unordered_set<char>());
	vector<vector<unordered_set<char>>> matrixs(3, vector<unordered_set<char>> (3, unordered_set<char> ()));
	for (int i = 0; i < 9; i++) {
		for (int j = 0; j < 9; j++) {
			char c =  board[i][j];
			if (c == '.')
				continue;
			if (lines[i].find(c) == lines[i].end())
				lines[i].insert(c);
			else
				return false;
			if (columns[j].find(c) == columns[j].end())
				columns[j].insert(c);
			else
				return false;
			if (matrixs[i/3][j/3].find(c) == matrixs[i/3][j/3].end())
				matrixs[i/3][j/3].insert(c);
			else
				return false;
		}
	}
#ifdef TEST
	for (int i = 0; i < 9; i++) {
		for (auto c : lines[i])
			cout << c << ' ';
		cout << endl;
	}

#endif
	return true;
}

int main(void) {
	string str;
	Solution solution;
	vector<vector<char>> matrix(9, vector<char>(9, '.'));
	for (int i = 0; i < 9; i++) {
		cin >> str;
		for (int j = 0; j < 9; j++) {
			matrix[i][j] = str[j];
		}
	}
	solution.isValidSudoku(matrix);
	return 0;
}

#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <cassert>
using namespace std;

class Solution {
public:
    string convert(string s, int numRows);
};

string Solution::convert(string s, int numRows) {
	if (s.empty() || numRows == 1)
		return s;
	assert(numRows > 1);
	vector<vector<char>> charVec(numRows, vector<char>());
	vector<int> lineNo;
	for (int i = 0; i < numRows; i++)
		lineNo.push_back(i);
	for (int i = numRows - 2; i > 0; i--)
		lineNo.push_back(i);
	int val = lineNo.size();
	for (int i = 0; i < s.size(); i++) {
		charVec[lineNo[i % val]].push_back(s[i]);
	}
	// 结果字符串
	string ret;
	for (int i = 0; i < charVec.size(); i++) {
		ret = ret + string(charVec[i].begin(), charVec[i].end());
	}
	return ret;
}

int main(int argc, char *argv[]) {
	Solution solu;
	string s;
	int n;
	while (cin >> s >> n) {
		cout << solu.convert(s, n) << endl;
	}
	return 0;
}

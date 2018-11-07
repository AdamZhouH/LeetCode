#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <stack>
#include <climits>
using namespace std;

// 给出括号序列中最长的合法序列的长度

class Solution {
public:
    int longestValidParentheses(string s);
   	bool isValid(const string& s, int i, int j);
};

bool Solution::isValid(const string& s, int i, int j) {
	if (i >= j)
		return false;
	stack<char> stk;
	while (i <= j) {
		if (s[i] == '(') {
			stk.push('(');
		} else if (s[i] == ')') {
			if (stk.empty())
				return false;
			else 
				stk.pop();
		}
		i++;
	}
	return stk.empty() ? true : false; 
}

int Solution::longestValidParentheses(string s) {
	if (s.empty())
		return 0;
	// 暴力方法
	int maxLength = 0;
	for (int i = 0; i < s.size(); i++) {
		for (int j = i; j < s.size(); j++) {
			if (isValid(s, i, j)) {
				maxLength = max(maxLength, j - i + 1);
			}
		}
	}	
	return maxLength;
}

int main(int argc, char *argv[]) {
	string s;
	Solution solu;
	while (cin >> s) {
		cout << solu.longestValidParentheses(s) << endl;
	}
	return 0;
}
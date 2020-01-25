#include <iostream>
#include <vector>
#include <string>
using namespace std;

class Solution {
public:
	string countAndSay(int n);
};
#define RECURSION
#ifndef RECURSION
// 直接遍历
string Solution::countAndSay(int n) {
	if (n == 1) {
		return "1";
	}
	string prev = "1";
	string curr;
	for (int i = 2; i <= n; i++) {
		int cnt = 1;
		char c = prev[0];
		for (int j = 1; j < prev.size(); j++) {
			if (prev[j] == c) {
				cnt++;
			} else {
				curr.push_back('0' + cnt);
				curr.push_back(c);
				c = prev[j];
				cnt = 1;
			}
		}
		// 最后一个“单词”
		curr.push_back('0' + cnt);
		curr.push_back(c);
		prev = curr;
		curr = "";
	}
	return prev;
}
#else
// 递归方法
string Solution::countAndSay(int n) {
	if (n == 1)
		return "1";
	string prev = countAndSay(n - 1);
	string ret;
	int cnt = 1;
	char c = prev[0];
	for (int i = 1; i < prev.size(); i++) {
		if (prev[i] == c) {
			cnt++;
		} else {
			ret.push_back('0' + cnt);
			cnt = 1;
			ret.push_back(c);
			c = prev[i];
		}
	}
	ret.push_back('0' + cnt);
	ret.push_back(c);
	return ret;
}
#endif

int main(int argc, char *argv[]) {
	int n;
	Solution solution;
	while (cin >> n) {
		cout << solution.countAndSay(n) << endl;
	}
	return 0;
}

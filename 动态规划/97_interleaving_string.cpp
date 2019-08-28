#include <iostream>
#include <string>
#include <vector>
#include <algorithm>

// 判断字符串3是否是由字符串1和字符串2拼接而成
// 暴力方法就是递归，第一个字符串的第一个字符作为整个字符的起始，然后下一个字符可以从第一个字符或者第二个字符串中选择
// 当用完全部字符串，判断构造出来的字符串是否和字符串3相同

// 还有一种利用动态规划的方法来做的，暂时没有补充完整

using namespace std;

class Solution {
	public:
		bool isInterleave(int flag, string s1, string s2, string s3);    // 动态规划的重载版本
		bool isInterleave(string s1, string s2, string s3);
		bool isInterleave(const string &s1, int idx1, const string &s2, int idx2, string &var, const string &s3);
};

bool Solution::isInterleave(string s1, string s2, string s3) {
	if ((s1.size() + s2.size()) != s3.size())
		return false;
	if (s1.empty())
		return s2 == s3;
	else if (s2.empty())
		return s1 == s3;
	string var;
	return isInterleave(s1, 0, s2, 0, var, s3);
}

bool Solution::isInterleave(const string &s1, int idx1, const string &s2, int idx2, string &var,const string &s3) {
	// 当全部字符用完，和s3进行比较，是否相同
	if (idx1 >= s1.size() && idx2 >= s2.size()) {
		return var == s3;
	}
	// 否则进行回溯的过程
	bool ret =false;
	// 先以第一个字符串的首个字符为var的首个字符，进行回溯，当全部字符用完，判断和当前字符是否相同
	if (idx1 < s1.size()) {
		var.push_back(s1[idx1]);
		ret |= isInterleave(s1, idx1 + 1, s2, idx2, var, s3);
		var.pop_back();
	}
	if (ret)
		return true;
	// 再以第二个字符串的首个字符为var的首个字符，进行回溯，当全部字符用完，判断和当前字符是否相同
	if (idx2 < s2.size()) {
		var.push_back(s2[idx2]);
		ret |= isInterleave(s1, idx1, s2, idx2 + 1, var, s3);
		var.pop_back();
	}
	return ret;
}

bool Solution::isInterleave(int flag, string s1, strin s2, string s3) {
	
}

// Test
int main(void) {
	string s1, s2, s3;
	Solution solution;
	while (cin >> s1 >> s2 >> s3) {
		cout << ((solution.isInterleave(s1, s2, s3)) ? "Y" : "N") << endl;
	}
	return 0;
}

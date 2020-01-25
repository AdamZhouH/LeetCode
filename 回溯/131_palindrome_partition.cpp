// LeetCode 131 分割回文字符串
// 给定一个字符串，将其分给为不同的回文字串，并返回所有可能的分割方案

// 解题思路
// 解法一：暴力回溯
// 实质上就是模拟人工分割字符串的过程，利用深度优先递归搜索解空间
// 同时，相比于暴力回溯，对于每个分割出来的字符串，立刻判断是否是回文串
// 如果是，则继续，不是则立刻回溯，避免不必要的枚举过程


// 解题思路二，先利用动态规划思想，找到所有可能的回文字符串的组合
// 然后根据

#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
using namespace std;

class Solution {
public:
    vector<vector<string>> partition(string s);
    void doPartitionDfs(string s, vector<string> &, vector<vector<string>> &);
    bool isPalindrome(string s);
};

// 双指针判断给定的字符串是否是一个回文字符串
bool Solution::isPalindrome(string s) {
	if (s.size() == 0)
		return false;
	if (s.size() == 1)
		return true;
	int head = 0;
	int tail = s.size() - 1;
	while (head < tail) {
		if (s[head] != s[tail])
			return false;
		head++, tail--;
	}
	return true;
}

void Solution::doPartitionDfs(string s, vector<string> &currPartition, vector<vector<string>> &allPartition) {
	int length = s.size();
	// 递归基准情况
	if (length == 0) {
		allPartition.push_back(currPartition);
		return;
	}
	// 递归回溯实现
	for (int i = 0; i < length; i++) {
		if (isPalindrome(s.substr(0, i + 1))) {
			currPartition.push_back(s.substr(0, i + 1));
			doPartitionDfs(s.substr(i + 1, length - i - 1), currPartition, allPartition);
			currPartition.pop_back();		
		}
	}
}


vector<vector<string>> Solution::partition(string s) {
	vector<vector<string>> partitionResult;
	vector<string> currPartition;
	doPartitionDfs(s, currPartition, partitionResult);

	for_each(partitionResult.begin(), partitionResult.end(), [] (vector<string> &vec) {
		for_each(vec.begin(), vec.end(), [] (const string &s) {
			cout << s << " ";
		});
		cout << endl;
	});

	return partitionResult;
}

int main(int argc, char *argv[]) {
	Solution solution;
	string s;
	while (cin >> s) {
		solution.partition(s);
		// cout << solution.isPalindrome(s) << endl;
	}
	return 0;
}

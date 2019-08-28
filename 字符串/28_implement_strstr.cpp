#include <iostream>
#include <string>
#include <vector>

// 在haystack中找到needle第一次出现的位置
// 字符串匹配题

using namespace std;

class Solution {
	public:
		int strStr(string haystack, string needle);
};

int Solution::strStr(string haystack, string needle) {
	if (needle.size() > haystack.size())
		return -1;
	int diff = haystack.size() - needle.size();
	for (int i = 0; i <= diff; i++) {
		int j = 0;
		for (; j < needle.size(); j++) {
			if (needle[j] != haystack[i + j])
				break;
		}
		if (j == needle.size())
			return i;
	}
	return -1;
}

int main(void) {
	string s1, s2;
	Solution solution;
	while (cin >> s1 >> s2) {
		cout << solution.strStr(s1, s2) << endl;
	}
	return 0;
}

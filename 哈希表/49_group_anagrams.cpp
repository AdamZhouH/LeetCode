#include <string>
#include <vector>
#include <iostream>
#include <algorithm>
#include <unordered_set>
#include <unordered_map>
#include <list>
using namespace std;

#define OPTIMIZE
// 个人的蠢办法，其实思路大致一致，但是可以简化一下
// 可以直接保存map<string, vector<string>>
// 直接把排序的迭代过程和找映射关系的迭代过程写在一个循环体中
class Solution {
public:
	vector<vector<string>> groupAnagrams(vector<string> &strs);
};
#ifndef OPTIMIZE
// 考虑将strs中的每个词的字母顺序按照排序
vector<vector<string>> Solution::groupAnagrams(vector<string> &strs) {
	vector<vector<string>> ret;
	unordered_map<string, unordered_set<int>> mapRecord;

	vector<string> words = strs;
	// 将words中的每个单词的字符进行排序
	for (auto &word : words)
		sort(word.begin(), word.end());
	// 保存映射关系，将相同字符串的单词的下标集合在一起，并和字符串映射
	for (int i = 0; i < words.size(); i++) {
		if (mapRecord.find(words[i]) != mapRecord.end()) {
			mapRecord[words[i]].insert(i);
		} else {
			mapRecord[words[i]] = unordered_set<int>();
			mapRecord[words[i]].insert(i);
		}
	}
	// 返回值即可
	for (auto it = mapRecord.begin(); it != mapRecord.end(); it++) {
		vector<string> vec;
		for (auto var : it->second)
			vec.push_back(strs[var]);
		ret.push_back(vec);
	}
	return ret;
}
#else
vector<vector<string>> Solution::groupAnagrams(vector<string> &strs) {
	unordered_map<string, vector<string>> mapinfo;
	for (int i = 0; i < strs.size(); i++) {
		string s = strs[i];
		sort(s.begin(), s.end());
		mapinfo[s].push_back(strs[i]);
	}
	vector<vector<string>> ret;
	for (auto &v : mapinfo) {
		ret.push_back(std::move(v.second));
	}
	return ret;
}
#endif

int main(int argc, char *argv[]) {
	vector<string> svec = {"eat", "tea", "tan", "ate", "nat", "bat"};
	Solution solution;
	auto ret = solution.groupAnagrams(svec);
	for (auto &v : ret) {
		for (auto &s : v) {
			cout << s << ' ';
		}
		cout << endl;
	}
	return 0;
}

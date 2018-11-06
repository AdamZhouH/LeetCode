// 17_letter_combinations_of_a_phone_number.cpp
// 这道题目很明显应该使用回溯的思想去枚举出所有可能的字母组合
// 思路比较清晰，关键是代码实现

// 同时注意，C++的基本语法，map中的pair<const Key, Value> Key是const类型，引用一定要加const
// 其次，主题append方法的正确使用，再次，注意越界问题，递归的基准情况是字串只有一个字符，遍历，然后放入结果
// DFS的递归情形则是每次处理一个字符，剩下的递归处理，到了基准情况，则直接push_back

#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <map>
using namespace std;

class Solution {
public:
	vector<string> letterCombinations(string digits); 
	void dfs(string digits, vector<string> &combinations, string &currentCombination);
	static map<char, vector<char>> numberToCharList;
};

map<char, vector<char>> Solution::numberToCharList = {
	{'2', {'a', 'b', 'c'}},
	{'3', {'d', 'e', 'f'}},
	{'4', {'g', 'h', 'i'}},
	{'5', {'j', 'k', 'l'}},
	{'6', {'m', 'n', 'o'}},
	{'7', {'p', 'q', 'r', 's'}},
	{'8', {'t', 'u', 'v'}},
	{'9', {'w', 'x', 'y', 'z'}},
};

void Solution::dfs(string digits, vector<string> &combinations, string &currentCombination) {
	int digitsLength = digits.size();
    vector<char> &vec = numberToCharList[digits[0]];
    if (digitsLength == 1) {
    	for (auto it = vec.begin(); it != vec.end(); it++) {
    		currentCombination.append(1, *it);
    		combinations.push_back(currentCombination);
    		currentCombination.pop_back();
    	}
    } else {
    	for (auto it = vec.begin(); it != vec.end(); it++) {
		currentCombination.append(1, *it);
		dfs(digits.substr(1), combinations, currentCombination);
		currentCombination.pop_back();
		}
	}
}

vector<string> Solution::letterCombinations(string digits) {
	vector<string> combinations;
	string currentCombination;
	if (digits.size() == 0)
		return combinations;
	dfs(digits, combinations, currentCombination);
	return combinations;
}

int main(void) {
	string digits;
	Solution solution;
	vector<string> combinations;

	while (cin >> digits) {
		combinations = solution.letterCombinations(digits);
		for_each(combinations.begin(), combinations.end(), [] (const string &s) {
			cout << s << " ";
		});
		cout << endl;
	}
	
	// 踩坑：这里必须是pair<const char, vector<char>>
	// map里的关键字是不可修改的，因此pair的first成员必须是const类型，否则报错让你崩溃，这属于基础语法知识
/*
//  测试类的静态数据是否正确初始化
	for_each(solution.numberToCharList.begin(), solution.numberToCharList.end(), [] (pair<const char, vector<char>> &i) {
		cout << i.first << " : ";
		for_each(i.second.begin(), i.second.end(), [] (char &c) {
			cout << c << " ";
		});
		cout << endl;
	});
*/	
	return 0;
}

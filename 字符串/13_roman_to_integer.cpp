// 将罗马数字转换为整数
// 罗马数字以I X C V L D M组成的字符串表示，需要遍历字符串
// 将每部分得到的数字相加即可
// 注意几种题目中给出的特殊规则即可
#include <iostream>
#include <string>
#include <vector>
#include <unordered_map>
using namespace std;

class Solution {
public:
	Solution();
	int romanToInt(string s);
private:
	// 罗马字符和对应的数字的映射关系
	unordered_map<char, int> romanNum;
};

Solution::Solution() {
	romanNum['I'] = 1;
	romanNum['V'] = 5;
	romanNum['X'] = 10;
	romanNum['L'] = 50;
	romanNum['C'] = 100;
	romanNum['D'] = 500;
	romanNum['M'] = 1000;
}

// 因为罗马数字中代表小数字的字符在右侧摆放，因此从最后一个字符开始遍历
int Solution::romanToInt(string s) {
	if (s.empty())
		return 0;
	if (s.size() == 1)
		return romanNum[s[0]];
	int ret = 0;
	int index = s.size() - 1;
	while (index >= 0) {
		char c = s[index];
		if (c == 'I') {
			ret += romanNum[c];
			index -= 1;
		} else if (c == 'V'|| c == 'X') {
			ret += romanNum[c];
			if ((index - 1) >= 0 && s[index - 1] == 'I') {
				ret -= romanNum[s[index - 1]];
				index -= 2;
			} else {
				index -= 1;
			}
		} else if (c == 'L' || c == 'C') {
			ret += romanNum[c];
			if ((index - 1) >= 0 && s[index - 1] == 'X') {
				ret -= romanNum[s[index - 1]];
				index -= 2;
			} else {
				index -= 1;
			}
		} else {
			ret += romanNum[c];
			if ((index - 1) >= 0 && s[index - 1] == 'C') {
				ret -= romanNum[s[index - 1]];
				index -= 2;
			} else {
				index -= 1;
			}
		}
	}
	return ret;
}

int main(void) {
	string str;
	Solution solu;
	while (cin >> str) {
		cout << "实际数字: " << solu.romanToInt(str) << endl;
	}
	return 0;
}

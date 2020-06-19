// 字符串转换为整型数
// 根据题目意思，找到第一个非空字符串判断是否是正负符号或者是数字
// 如果不是以上两种情况，或者字符串为空，字符串仅仅包含空白字符，则说明不可以转换数字，返回0
// 否则，从此处开始，尽可能多的把连续的数字字符转换为数字，之后可以包含非数字字符

// 同时注意溢出的情况，仅考虑在32位int型的整数的范围内的数字转换，溢出则输出 INT_MIN或者INT_MAX

#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <climits>
using namespace std;

class Solution {
public:
	int myAtoi(string str);
};

int Solution::myAtoi(string str) {
	if (str.empty())
		return 0;
	ssize_t pos = str.find_first_not_of(' ');
	if (pos == string::npos || !((str[pos] == '+') || (str[pos] == '-') || (isdigit(str[pos]))))
		return 0;
	int sign = 1;
	if (str[pos] == '+' || str[pos] == '-') {
		if (str[pos] == '+')
			sign = 1;
		else
			sign = -1;
		pos++;
	}
	int sum = 0;
	// 求绝对值，同时需要判断溢出，判断溢出要利用INT_MAX / 10  
	while (pos != str.size() && isdigit(str[pos])) {
		if (sum > INT_MAX / 10  || (sum == INT_MAX / 10 && str[pos] - '0' > INT_MAX % 10))
			return (sign > 0 ? INT_MAX : INT_MIN);
		sum = sum * 10 + str[pos] - '0';
		pos++;
	}
	return sum * sign;
}

// 更加清爽一些的写法
class Solution2 {
public:
    int strToInt(string str);
    int help(const string &str, int flag);
};

int Solution2::strToInt(string str) {
    string::size_type pos = str.find_first_not_of(' ');
    if (pos == string::npos || (!isdigit(str[pos])) && str[pos] != '+' && str[pos] != '-') 
        return 0;
    if (str[pos] == '+' || str[pos] == '-')
        return help(str.substr(pos+1), str[pos] == '+' ? 1 : -1);
    return help(str.substr(pos), 1);
}

int Solution2::help(const string &str, int flag) {
    if (str.empty() || !isdigit(str[0])) return 0;
    long long ans = 0;
    for (int i = 0; i < str.size() && isdigit(str[i]); i++) {
        ans = ans * 10 + str[i] - '0';
        if (flag == 1) {
            if (ans > INT_MAX) return INT_MAX;
        } else {
            if (ans * flag < INT_MIN) return INT_MIN;
        }
    }
    return ans * flag;
}

int main(int argc, char **argv) {
	string s;
	Solution solution;
	while (cin >> s)
		cout << s << " : " << solution.myAtoi(s) << endl;
	return 0;
}

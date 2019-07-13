// 给出一个32位有符号整数
// 给出的例子看，首位可能是符号或者不是符号，首先，符号可以不用管
// 其次，考虑末尾位为0或者连续的0，那么转换后，数字的长度减小
// 首先可以考虑数字转换为字符串，然后字符串转回数字
// 然后，还需要考虑字符串反转后的溢出问题（怎么判断溢出？）
// 考虑极端输入，最小负数，最大正数

// 换个思路，可以利用双端队列，push back 进去，pop_front出来

#include <iostream>
#include <list>
#include <vector>
#include <algorithm>
#include <climits>

using namespace std;

class Solution {
public:
    int reverse(int x);
};

int Solution::reverse(int x) {
    long long var = static_cast<long> (x);
    long long result = 0;
    bool flag = false;
    if (x < 0) {
        var = var * -1;
        flag = true;
    }
    // 开始具体分析
    list<char> clst;
    while (var) {
        char temp = (var % 10) + '0';
        if (temp != '0' || !clst.empty())
            clst.push_back(temp);
        var = var / 10;
    }
    while (!clst.empty()) {
        char temp = clst.front();
        result = result * 10 + (temp - '0');
        clst.pop_front();
    }
    result *= flag ? -1 : 1;
    // 判断溢出
    if (result > INT_MAX || result < INT_MIN) 
        return 0;
    return result;
}

int main(int argc, char *argv[]) {
    int number;
    Solution solution;
    while (cin >> number) {
        cout << number << " : " << solution.reverse(number) << endl;
    }
    return 0;
}
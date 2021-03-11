#include <iostream>
#include <vector>
#include <string>
#include <list>
#include <unordered_map>
#include <unordered_set>
#include <map>
#include <set>
#include <stack>
#include <queue>
using namespace std;

// + - （ ） 空格
// 一个基本的计算器的实现
// 这题不会做，还是看的答案才理解的思路（自己只能想到转换为逆波兰表达式，但是逆波兰不会写）
// 核心思路是，因为这个计算机非常简单，只有+-运算符，以及括号
// 因此你想办法先把所有的括号展开
// 那么就变成很简单的利用栈可以实现的计算逻辑
// 所以展开括号之后，每个数字之前的符号的确定就是这道题的关键
// 由于括号内某个数字之前的符号和最终的符号不一定相同的，还必须结合括号的嵌套次数和每个括号之前的符号
// 因此用栈保存当前嵌套层次中的每个字符的符号

class Solution {
public:
    int calculate(string s);
};

// 注意s是一个合法的表达式，因此这里可以省去一些判断
int Solution::calculate(string s) {
    stack<int> stk;
    stk.push(1);
    int sign = 1, ret = 0;
    for (int i = 0; i < s.size();) {
        if (s[i] == '+') {
            sign = stk.top();
            i++;
        } else if (s[i] == '-') {
            sign = -stk.top();
            i++;
        } else if (s[i] == '(') {
            stk.push(sign);
            i++;
        } else if (s[i] == ')') {
            stk.pop();
            i++;
        } else if (s[i] == ' ') {
            i++;
            continue;
        } else {
            int num = 0;
            while (i < s.size() && isdigit(s[i])) {
                num = num * 10 + (s[i] - '0');
                i++;
            }
            ret += num * sign;
        }
    }
    return ret;
}
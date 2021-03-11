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

class Solution {
public:
    // 这道题中没有括号限制，好像好做一些？
    // 但是增加了另外两种运算，存在优先级的区别
    // 并且如果是优先级高，需要计算后存储结果？
    // 先计算乘除，因为可以直接计算，优先级高，然后结果放回栈
    // 最后就变成一个只有中间结果元素的，并且最终的计算都是加法，然后全部元素相加
    int calculate(string s) {
        // 由于没有嵌套括号，因此不用一个stk保存嵌套之后的括号内元素的符号（对比基本运算器I）
        // 只需要用一个栈保存乘除法之后的元素（最后直接返回所有元素的和即可）
        // 直接用vector模拟栈了
        int sign = 1;
        vector<int> stk;
        int i = 0;
        while (i < s.size()) {
            if (s[i] == ' ') {
                i++; 
            } else if (s[i] == '+' || s[i] == '-') {
                sign = s[i] == '+' ? 1: -1;
                i++;
            } else if (isdigit(s[i])) {
                long num = 0;
                while (i < s.size() && isdigit(s[i])) {
                    num = num * 10 + s[i] - '0';
                    i++;
                }
                stk.push_back(sign * num);
            } else {
                // 说明是乘或者除法符号
                char op = s[i];
                i++;
                long num = 0;
                // 这里有坑，因为符号后面可能还存在空格
                while (i < s.size() && s[i] == ' ') i++;
                while (i < s.size() && isdigit(s[i])) {
                    num = num * 10 + s[i] - '0';
                    i++;
                }
                if (op == '*') 
                    num = stk.back() * num;
                else 
                    num = stk.back() / num;
                stk.pop_back();
                stk.push_back(num);
            }
        }
        return accumulate(stk.begin(), stk.end(), 0);
    }
};
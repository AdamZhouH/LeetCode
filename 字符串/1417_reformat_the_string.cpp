#include <iostream>
#include <string>
uisng namespace std;


// 一道周赛签到题
// 思路很简单，直接统计个数，保证两者个数差的绝对值不超过1，否则不能满足要求
// 直接采用归并思路
// 不能连续两个字符或者数字，而应该间隔
class Solution {
public:
    string reformat(string s) {
        string a, b;
        for (auto c : s) {
            if (isdigit(c)) a.push_back(c);
            else b.push_back(c);
        }
        if (abs((int)a.size() - (int)b.size()) > 1)
            return "";
        string ret;
        int i = 0, j = 0;
        if (a.size() < b.size()) a.swap(b);
        while (i < a.size() && j < b.size()) {
            ret.push_back(a[i++]);
            ret.push_back(b[j++]);
        }
        if (i < a.size()) ret.push_back(a[i++]);
        return ret;
    }
};
#include <string>
#include <algorithm>
#include <iostream>
using namespace std;

// 直接用双指针做的
// 当然也可以将字符串先过滤一遍，然后判断回文串也行
class Solution {
public:
    bool isPalindrome(string s) {
        if (s.empty()) return true;
        int i = 0, j = s.size() - 1;
        while (i <= j) {
            if (!isalnum(s[i])) { i++; continue; }
            if (!isalnum(s[j])) { j--; continue; }
            if (tolower(s[i]) == tolower(s[j])) { i++, j--; continue; }
            else return false;
        }
        return true;
    }
};
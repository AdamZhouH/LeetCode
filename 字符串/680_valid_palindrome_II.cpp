#include <iostream>
#include <vector>
#include <string>
using namespace std;

////////////////////////////////////
// 递归思路
class Solution {
public:
    bool validPalindrome(string s) {
        if (s.size() <= 2) return true;
        return validPalindrome(s, 0, s.size() - 1, true);
    }
    bool validPalindrome(const string &s, int i, int j, bool flag) {
        if (i > j) return true;
        if (s[i] == s[j]) return validPalindrome(s, i+1, j-1, flag);
        if (!flag) return false;
        else flag = false;
        return validPalindrome(s,i+1,j,flag) || validPalindrome(s,i,j-1, flag);
    }
};

////////////////////////////////////
// 迭代思路
class Solution2 {
public:
    bool validPalindrome(string s) {
        if (s.size() <= 2) return true;
        int i = 0, j = s.size() - 1;
        while (i <= j) {
            if (s[i] == s[j]) { i++, j--; continue; }
            return isPalindrome(s, i+1, j) || isPalindrome(s,i, j-1);
        }
        return true;
    }
    
    bool isPalindrome(string s, int i, int j) {
        while (i <= j) 
            if (s[i++] != s[j--]) return false;
        return true;
    }
};
#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
#include <unordered_map>
using namespace std;

class Solution {
public:
    int lengthOfLongestSubstring(string s);
};

int Solution::lengthOfLongestSubstring(string s) {
    if (s.size() == 1)
        return 1;
    unordered_map<char, int> table;
    int startPos = 0;  
    int maxLength = 0;
    int currMaxLength = 0;
    int strLength = s.size();
    // 对于暴力破解的优化，时间36ms
    // 其实对于这种简单问题，可以直接建立一个数组，作为简单的哈希表
    // int hashTable[128] = { 0 };
    // 可能时间会更短
    for (int i = 0; i < strLength; i++) {
        table[s[i]]++;
        if (table[s[i]] == 1)
            currMaxLength++;
        else {
            // 找到重复字符在先前不重复的字串中出现的位置，从而截取可以不用重遍历的子串
            // 因为这部分是不会重复的
            table[s[i]] = 1;
            maxLength = max(currMaxLength, maxLength);
            // 注意这里很容易踩坑
            // 因为计算是从新的字串开始和，因此在新的startPos之前的table中记录的信息也要去除
            // 否则，长度就会变短
            while (startPos <= i - 1 && s[startPos] != s[i]) {
                table.erase(s[startPos]);
                startPos++;
            } 
            startPos++;
            currMaxLength = i - startPos + 1;
        }  
    }
    maxLength = max(maxLength, currMaxLength);
    // 下面的代码是暴力破解 用时420ms
/*
    for (int i = 0; i < strLength; i++) {
        for (int j = i; j < strLength; j++) {
            table[s[j]]++;
            if (table[s[j]] == 1)
                currMaxLength++;
            else
                break;
        }
        maxLength = max(maxLength, currMaxLength);
        table.clear();
        currMaxLength = 0;
    }
*/
    return maxLength;
}

int main(void) {
    string s;
    Solution solution;
    while (cin >> s) {
        cout << solution.lengthOfLongestSubstring(s) << endl;
    }
    return 0;
}
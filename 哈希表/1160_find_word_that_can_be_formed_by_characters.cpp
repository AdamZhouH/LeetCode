#include <iostream>
#include <unordered_map>
#include <vector>
#include <string>
using namespace std;

// 需要注意的是，每次拼写中，chars字符集中的字符只能使用一次

// 开始的时候，想了想，首先，对于chars中的字符的计数操作是不可避免的
// 然后思考每次直接使用这个计数结果会导致计数结果改变，那就应该每次对一个单词进行判断
// 时，都复制一下这个计数的结果，感觉开销会有点大
// 看了用时少的算法，其实开销并不是很大，而且可以直接在临时的复制的计数上直接减，遇到一个字符就减去一次计数
// 当一个字符的计数为0时，说明字符就不够用了，可能不可能掌握这个单词
// 为了避免复制导致的开销，这里就没有用unordered_map结构，而是用数组(相当于一个非常简单的哈希表)

#define VERSION2

class Solution {
public:
    int countCharacters(vector<string>& words, string chars);
};
#ifndef VERSION2
int Solution::countCharacters(vector<string>& words, string chars) {
    if (words.empty() || chars.empty())
        return 0;
    unordered_map<char, size_t> charToCnt;
    unordered_map<char, size_t> currWord;
    for (auto c: chars)
        charToCnt[c]++;
    int totalLen = 0;
    for (auto &word : words) {
        bool flag = true;
        for (auto c : word)
            currWord[c]++;
        for (auto &p : currWord) {
            if (p.second > charToCnt[p.first]) {
                flag = false;
                break;
            }
        }
        if (flag)
            totalLen += word.size();
        currWord.clear();
    }
    return totalLen;
}
#else
int Solution::countCharacters(vector<string>& words, string chars) {
    if (words.empty() || chars.empty())
        return 0;
    
    int cnt[26] = {0};
    for (auto c: chars)
        cnt[c - 'a']++;
    
    int totalLen = 0;
    for (auto &word : words) {
        int tempCnt[26];
        memcpy(tempCnt, cnt, sizeof(tempCnt));
        
        bool flag = true;
        for (auto c: word) {
            if (tempCnt[c - 'a'] <= 0) {
                flag = false;
                break;
            } else {
                tempCnt[c - 'a']--;
            }
        }
        
        if (flag)
            totalLen += word.size();
    }
    return totalLen;
}
#endif
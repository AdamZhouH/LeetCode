#include <iostream>
#include <unordered_set>
#include <cmath>
#include <vector>
#include <string>
using namespace std;

const unsigned long MOD = (unsigned long)pow(2, 32);

class Solution {
public:
    // 核心思路是二分查找，因为如果长度为len的重复字串存在，则长度为len-1 len-2的重复字串肯定也是存在的
    // 因此当存在一个长度的字串时，我们搜索比这个长度大1的重复字串是否存在
    // 如此可用二分计算
    // 其次是hash比分，暴力hash，直接用unordered_set<string>也就是存储的字符串，那么一是导致每次获取字符串的时候
    // 需要O(len)时间复杂度，还有空间也比较大开销
    // 因此使用一种hash算法，将字符串应设成一个unsigned long型整数
    // 也就是Rabin-Karp算法，将字符串hash成一个整数存放到unordered_set中
    string longestDupSubstring(string S) {
        if (S.empty()) return 0;
        string ret = "";
        int left = 1, right = S.size();
        while (left <= right) {
            int mid = left + (right - left) / 2;
            string cur = hasSubstr(S, mid);
            if (cur.empty()) right = mid - 1;
            else {
                ret = cur;
                left = mid + 1;
            }
        }
        return ret;
    }

    string hasSubstr(const string &s, int len) {
        unordered_set<unsigned long> record;
        unsigned long hashCode = 0;
        unsigned long a = 1;
        for (int i = 0; i < len; i++) {
            a = (a * 26) % MOD;
            hashCode = (hashCode * 26 + s[i] - 'a') % MOD;
        }
        record.insert(hashCode);
        int i = 1;
        while (len + i - 1 < s.size()) {
            hashCode = (hashCode * 26 - (s[i-1] - 'a') * a % MOD + MOD) % MOD;
            hashCode = (hashCode + s[len+i-1] - 'a') % MOD;

            if (record.count(hashCode))  return s.substr(i, len);
            record.insert(hashCode); i++;

        }
        return "";
    }
};

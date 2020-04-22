#include <vector>
#include <string>
#include <algorithm>
#include <unordered_map>
#include <utility>
using namespace std;


class Solution {
public:
    int getMaxRepetitions(string s1, int n1, string s2, int n2);
    int dfs(const string &s1, const string &s2, int start, int end, int n2);
};

// 暴力思路
// 直接遍历，但是会导致超时，应该进行时间复杂度的优化
int Solution::getMaxRepetitions(string s1, int n1, string s2, int n2) {
    if (s1.size() * n1 < s2.size() * n2) return 0;
    int start = 0, end = s1.size() * n1 - 1;
    return dfs(s1, s2, 0, end, n2);
}

int Solution::dfs(const string &s1, const string &s2, int start, int end, int n2) {
    if (start > end) return 0;
    int i = 0;
    int j = start;
    int s2len = s2.size() * n2;
    for (; i < s2len; i++) {
        while (j <= end && s1[j % s1.size()] != s2[i % s2.size()]) j++;
        if (j > end) break;
        j++;
    }
    if (i >= s2len) return 1+dfs(s1, s2, j, end, n2);
    return 0;
}


// 使用循环节来优化，找到s2在s1中出现的循环节即可
// 剩余的部分则使用遍历的方法
// unordered_map<int, pair<int,int>> record记录
// 第一个int表示当走到当前的s1的末尾时，还需要匹配的是s2中的哪一个字符
// 第二个则表示，此时，已经遍历了多少个s1字符串和s2字符串
int getMaxRepetitions(string s1, int n1, string s2, int n2) {
    if (n1 == 0) return 0;
    unordered_map<int, pair<int,int>> record;
    int s1cnt = 0, s2cnt = 0;
    int next = 0;
    while (s1cnt < n1) {
        s1cnt++;
        for (int j = 0; j < s1.size(); ) {
            while (j < s1.size() && s1[j] != s2[next]) j++;
            if (j >= s1.size()) break;
            if (next == s2.size() - 1) s2cnt++;
            next = (next + 1) % s2.size(), j++;
        }
        if (record.count(next) == 0) {
            record[next] = {s1cnt, s2cnt};
        } else {
            // 代码走到这里说明找到循环节

            // 循环节长度(占几个s1)、每个循环节多少个s2
            int interval = s1cnt - record[next].first, repeat = s2cnt - record[next].second;
            // 出去开始不属于循环节的部分，能够有多少个循环节
            int numOfinterval = (n1 -record[next].first) / interval;
            // 处于开始部分以及若干个循环节部分，剩余的s1的个数，需要我们遍历查找的
            int numOfleft = (n1 - record[next].first) % interval;
            int ans = numOfinterval * repeat;
            int remain = record[next].second;
            // 直接暴力遍历剩余的若干s1，看能够匹配到几个s2
            // 注意的一点是，因为在循环节出现之前，可能已经用若干个s1匹配了若干个s2
            // 剩余的若干个s1在循环节出现之前的遍历结果上继续遍历，才不会遗漏
            for (int j = 0; j < s1.size() * numOfleft; ) {
                while (j < s1.size() * numOfleft && s1[j % s1.size()] != s2[next]) 
                    j++;
                if (j >= s1.size() * numOfleft)
                    break;
                if (next == s2.size() - 1) 
                    remain++;
                next = (next + 1) % s2.size(), j++;
            } 
            return (ans + remain) / n2;
        }
    }
    // 代码走到这里说明没有找到循环节，那么s2cnt记录的是n1个s1匹配到了多少个s2
    return s2cnt / n2;
}

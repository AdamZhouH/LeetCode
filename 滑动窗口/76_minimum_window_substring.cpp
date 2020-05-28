// 滑动窗口，在没有遇到合法位置之前，扩大右边边界，直到一个满足条件的子串
// 然后尝试能否缩小，那就移动左边界，如果可以满足，那同时也更新最短子串的位置
// 一直通过右移动左边界，达到缩小字符串长度的目的，直到移动到一个子串不符合条件的情况，又开始扩大右边界
// 当右边界无法扩大，同时左边界
// 解题的关键在于如何判断当前子字符串是否是合法的子字符串
// 合法子串的条件之，目标串T中的所有字符都在子串中存在
// 一个简单的方法是利用hashmap，存储子串的各个字符的计数统计，判断是否合法时，直接遍历子目标串T，中的每个字符，在子串的map中，计数-1
// 如果此时出现计数<0的情况，则说明这个字符不够用，肯定是不合法的，如果能遍历完，则是合法的，此时更新最短字符串即可

class Solution {
public:
    // 第266个测试用例超时（倒数第3个）
    string minWindow(string s, string t) {
        int left = 0, right = INT_MAX - 1;
        int i = 0, j = 0;
        unordered_map<char, int> record;
        bool valid = false;
        // 如果当前不合法，则扩大右边界，直到合法
        // 然后缩短左边界，直到不合法
        while (j < s.size()) {
            while (j < s.size() && !isValid(record, t)) {
                record[s[j]]++, j;
                if (isValid(record, t)) {
                    break;
                }
                j++;
            }
            
            if (j >= s.size()) break;
            if (isValid(record, t) && j - i + 1 < right - left + 1)
                left = i, right = j;
            record[s[i]]--, i++;
            while (isValid(record, t)) {
                if (j - i + 1 < right - left + 1)
                    left = i, right = j;
                record[s[i]]--, i++; 
            }
            j++;
        }
        if (right == INT_MAX - 1) return "";
        else return s.substr(left, right - left + 1);
    }
    
    // 主要是这个函数超时了，有没有O(1)时间判断是否是满足条件的字符串的方法？
    bool isValid(unordered_map<char, int> record, const string &t) {
        for (int i = 0; i < t.size(); i++) {
            record[t[i]]--;
            if (record[t[i]] < 0)
                return false;
        }
        return true;
    }
};

// 更好的思路
// 总体思路是不变的，仍然利用SlidingWindows
// 但是在判断是否是合法子串（即包含目标串的所有字符时）进行了优化
// 利用一个matchlen来记录匹配了几个t中的字符，当长度和t长度一致说明全部字符匹配完毕
// 注意只要当前字符是t中的字符，就对target中的计数-1，如果-1后>=0说明刚才的字符是需要计数到matchlen中
// 如果<0说明这个字符之前就已经匹配完
// 注意t中字符重复的情况，因此会出现多次匹配
// 当缩小左侧
class Solution {
public:
    string minWindow(string s, string t);
};

string Solution::minWindow(string s, string t) {
    if (s.size() < t.size()) return "";
    unordered_map<char, int> target;
    for (auto c: t) target[c]++;
    int i = 0, j = 0;
    int start = 0, len = INT_MAX;
    int matchlen = 0;
    while (j < s.size()) {
        if (!target.count(s[j])) { j++; continue;}
        if (--target[s[j]] >= 0) matchlen++;
        while (matchlen == t.size()) {
            if (j - i + 1 < len) start = i, len = j - i + 1;
            if (target.count(s[i]) && ++target[s[i]] > 0) matchlen--;
            i++;
        }
        j++;
    }
    return len == INT_MAX ? "" : s.substr(start, len);
}
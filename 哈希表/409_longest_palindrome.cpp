class Solution {
public:
    int longestPalindrome(string s);
};

// 由string中的字符尽可能组成一个回文字符串
// 首先，在string出出现偶数次数的字符肯定可以用在新的回文串中
// 其次，如果还存在一个出现奇数次字符，也能够用在回串中，不过必须放在中间位置，本质上就是分回文串字符总数为奇数或者偶数的情况
// 那么只要先把所有字符串的偶数频率都选择掉，然后如果剩下有存在的字符，随机选择一个即可

int Solution::longestPalindrome(string s) {
    int ret = 0;
    if (s.empty())
        return ret;
    unordered_map<char, size_t> statistics;
    for (auto c : s)
        statistics[c]++;
    bool flag = false;
    for (auto &p : statistics) {
        if (p.second & 0x1) {
            ret += (p.second - 1);
            flag = true;
        } else {
            ret += p.second;
            p.second = 0;
        }
    }
    if (flag)
        return ret + 1;
    return ret;
}
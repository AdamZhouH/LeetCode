#include <vector>
#include <iostream>
#include <string>
#include <algorithm>
using namespace std;

class Solution {
public:
    bool isMatch(string s, string p);
};

// 开始想的直接用递归去写，看评论动态规划也能很好的完成任务，考虑动态规划的话，其实也还好
// dp[i][j]表示str[1:i]和pattern[1:j]能否匹配，为0表示无法匹配，为1表示可以匹配
//
// 分析状态转移方程
//   对于dp[i][j]，如果str[i]与p[j]相同或者p[j]为.，则dp[i][j] = dp[i-1][j-1]，即与s[1:i-1]和p[1:j-1]的匹配情况相同
//   如果为*，则表示这个字符可以用前一个字符来代替(我们尽量去匹配字符串)
//   p当前字符为*，如果p前一个字符为.，显然可以用一次.*组合，如果p前一个字符p[j-1]不与s[i]相同，则不能使用替换
//   综合考虑，若p[j]=='*'
//   1. 不选择替换，使用0次*，dp[i][j] = dp[i][j-2]
//   2. 当p[j-1]为.或者与s[i]相同时，可以使用一次替换，则dp[i][j] = dp[i-1][j]
//   两者求或 (因为我们尽可能去匹配字符串，所以只要有一种情况匹配成功，则匹配成功)
// 初始化主要考虑p去匹配一个空串的情况，和上面类似的分析过程即可得出结论

bool Solution::isMatch(string s, string p) {
    if (p.empty()) return s.empty();
    vector<vector<int>> dp(s.size()+1, vector<int>(p.size()+1, 0)); dp[0][0] = 1;
    // 初始化dp[0][j]表示p[1:j]与空串的匹配情况
    for (int j = 1; j <= p.size(); j++) {
        if (p[j-1] != '*') continue;
        else dp[0][j] = dp[0][j-2];
    }
    for (int i = 1; i <= s.size(); i++) {
        for (int j = 1; j <= p.size(); j++) {
            if (s[i-1] == p[j-1] || p[j-1] == '.') dp[i][j] = dp[i-1][j-1];
            else if (p[j-1] == '*') {
                dp[i][j] = dp[i][j-2];
                if (p[j-2] == '.' || p[j-2] == s[i-1]) dp[i][j] = dp[i][j] || dp[i-1][j];
            }
        }
    }
    return dp[s.size()][p.size()];
}

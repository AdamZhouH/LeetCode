#include <iostream>
#include <string>
#include <vector>
using namespace std;

class Solution {
public:
    int numDecodings(string s);
};

// 递推公式也比较简单，边界条件比较复杂
// dp[i]表示到第i+1个字符处，一共几种解码的方法
// dp[i] = dp[i-1] + dp[i-2] 
// 当前字符为0，只能和前一个字符组合
//          这种情况下，直接考虑前一个字符，如果为1或者2，则说明可以组合，如果为其他的，就没有方案了，整个字符串都无解
// 当前字符不为0时，考虑两种情况
//     1.当前字符可以和前一个字符组合
//          这种情况一般是前一个字符为1，或者为2并且当前字符小于等于6
//     2.当前字符不能和前一个字符组合
//          这种情况是前一个字符为0，或者前一个字符大于2，或者前一个字符等于2但是当前字符大于6

int Solution::numDecodings(string s) {
    if (s.empty() || s[0] == '0') return 0;
    vector<int> dp(2, 1);
    for (int i = 2; i <= s.size(); i++) {
        // 当前字符为0，只能和前1字符组合
        if (s[i-1] == '0') {
            if (s[i-2] == '1' || s[i-2] == '2') dp.push_back(dp[i-2]);
            else dp.push_back(0);
        } else {
        // 当前字符不为0，则可以考虑与前一个字符组合或者不组合
            if (s[i-2] == '0' || s[i-2] > '2') dp.push_back(dp[i-1]);
            if (s[i-2] == '1') dp.push_back(dp[i-1]+dp[i-2]);
            if (s[i-2] == '2') {
                if (s[i-1] <= '6') dp.push_back(dp[i-1]+dp[i-2]);
                else dp.push_back(dp[i-1]);
            }
        }
    }
    return dp[s.size()];
}

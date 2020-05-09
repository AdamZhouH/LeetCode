#include <iostream>
#include <string>
#include <vector>
using namespace std;

class Solution {
public:
    int numDecodings(string s);
};

// 很明显，用递归可以做，但是可以用递归的都可以考虑下动态规划
// 减少时间复杂度
// 递推公式也比较简单
// dp[i]表示到第i+1个字符处，一共几种解码的方法
// dp[i] = dp[i-1] + dp[i-2](这一项表示当前字符和前一个字字符组成一个字母，当然，前提是可以组成，不能超过26)
int Solution::numDecodings(string s) {
    if (s.empty()) return 0;
    vector<int> dp(s.size() + 1, 0);
    dp[0] = 0, dp[1] = 1;
    for (int i = 2; i <= s.size(); i++) {
        if ((s[i-2]-'A'+1)*10 + (s[i-1]-'A'+1) <= 26)
            dp[i] = dp[i-1] + dp[i-2];
        else
            dp[i] = dp[i-1];
    }
    return dp[s.size()];
}

#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
#include <list>
#include <stack>
#include <map>
#include <set>
#include <queue>
#include <unordered_map>
#include <unordered_set>
#include <utility>
#include <memory>
using namespace std;

// 动态规划思路
// dp[i]表示将[0-i]处的字符串分割成回文子串的最小切割次数
// 如果直接按照之前的暴力方式，生成所有分割方案（利用回溯法），也是可以求出最小的切割次数的
// 这种方式下肯定要超时，这里比较容易想到的是一个递推公示
// dp[i] = min{dp[j]+1} 其中j满足[j+1, i]构成的是一个回文字符串
// 因此针对每个i，都通过这种方式找到最小的dp[i]
// 而判断某个子串是否是回文则可以通过动态规划预处理在O(1)时间内判断某个子串是否是回文字符串
// 针对dp[i][j]，如果s[i]==s[j]并且s[i+1,j-1]是回文串，则s[i][j]也是回文串
// 如果i==j，则显然单个字符是回文串
// 如果|i-j|==1，则比较s[i]和s[j]即可
class Solution {
public:
    int minCut(string s);
    void prePalindromeConstruct(vector<vector<int>> &dp, const string &s);
};

void Solution::prePalindromeConstruct(vector<vector<int>> &dp, const string &s) {
    int n = s.size();
    for (int j = 0; j < n; j++) {
        for (int i = 0; i <= j; i++) {
            if (i == j) { 
                dp[i][j] = 1;
            } else if (j-i == 1) {
                dp[i][j] = s[i] == s[j];
            } else {
                dp[i][j] = dp[i+1][j-1] && s[i] == s[j];
            }
        }
    }
}

int Solution::minCut(string s) {
    if (s.size() <= 1) return 0;
    int n = s.size();
    vector<vector<int>> dp(n, vector<int>(n, 0));
    prePalindromeConstruct(dp, s);
    // 第二次利用dp，找最小切割方案
    vector<int> dp2(n, 0);
    for (int i = 1; i < n; i++) {
        if (dp[0][i]) { dp2[i] = 0; continue; }
        dp2[i] = i;
        for (int j = 1; j <= i; j++) {
            if (dp[j][i]) {
                dp2[i] = min(dp2[i], dp2[j-1]+1);
            }
        }
    }
    return dp2[n-1];
}

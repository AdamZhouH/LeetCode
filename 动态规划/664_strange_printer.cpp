#include <iostream>
#include <vector>
#include <string>
using namespace std;


// 这道题的突破口在于用简单的例子来模拟打印字符串过程
// 对于某个字符串s，打印其中某段s[i:j] (i <= j)，考虑第j个字符
// 1 可以是单独打印的，也就是在s[i:j-1]基础上，直接打印一个字符，也即dp[i][j]=dp[i][j-1]+1
// 2 可以是从前面某个和s[j]相同的字符处的位置，直接打印一串到结尾，然后将其中不同的字符通过打印更改掉，从而达到要求
//   假设这个位置为k，s[k] == s[j]，我们只需要得到s[k:j-1]字符串的打印次数就可以得到s[k:j]
//   因为最后j处的字符和k处是相同的，所以不是s[k:j]而是s[k:j-1]，枚举所有合法k
//   也即 dp[i][j] = min{dp[i][k-1] + dp[k][j-1]} 其中s[k] == s[j]
class Solution {
public:
    int strangePrinter(string s) {
        if (s.size() <= 1) return s.size();
        int n = s.size();
        vector<vector<int>> dp(n+1, vector<int>(n+1, 0));
        for (int i = n; i >= 1; i--) {
            for (int j = i; j <= n; j++) {
                dp[i][j] = dp[i][j-1] + 1;
                for (int k = i; k < j; k++) {
                    if (s[k-1] == s[j-1])
                        dp[i][j] = min(dp[i][j], dp[i][k-1] + dp[k][j-1]);
                }
            }
        }
        return dp[1][n];
    }
};

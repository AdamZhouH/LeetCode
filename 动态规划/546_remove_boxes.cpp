#include <iostream>
#include <vector>
#include <string>
using namespace std;

class Solution {
public:
    int removeBoxes(vector<int>& boxes);
};
// 贴一个效率比较低的dp，写了点注释
// 又是一道区间dp的算法题，好难，考虑消除区间[i:j]部分的元素得到的最大收益，当前考虑j处的元素（从后往前分析）
// dp[i][j][k]表示消除[i:j]区间得到的最大收益，其中k表示j之后还存在k个和j相同的字符
//
// 1.单独删除的情况dp[i][j][k] = dp[i][j-1][0] + (k+1)*(k+1) dp[i][j-1][0] 后一项dp的k为0是因为我们仅考虑[i:j-1]之后没有和j-1处字符相同的字符
// 2.如果[i:j-1]之间存在某个位置p和j处字符相同的元素，则可以考虑先把[p+1:j-1]处的字符删除，然后剩下dp[i][p][k+1]
//   也即是dp[i][j][k] = dp[i][p][k+1] + dp[p+1][j-1][0]，在[i:j-1]区间中，枚举所有这样的p，然后求最小值即可
//
// 综上得到递推公式 dp[i][j][k] = min(dp[i][j-1][0]+(k+1)*(k+1), min{dp[i][p][k+1]+dp[p+1][j-1][0]})
// 得到递推公式后开始考虑初始化情况，首先，ij之间必须满足关系i<=j
// 其次，当i==j时，显然只能是单独一种字符直接删除dp[i][i-1][0]+(k+1)*(k+1)，由于当i>j时，dp元素值已经赋为0了
// 因此其实无需要特殊的初始化了，直接迭代也能保证结果正确，注意为了防止k越界，可以考虑将第三层vector开到至少boxes.size()这么大
// 还有注意dp的计算，对于i要从后往前，对于j从前往后，这是因为dp[i][p][k+1]+dp[p+1][j-1][0]中，p+1是>i的，因此显然i要倒着迭代
// 然后考虑j，在计算dp[i][j][k] = dp[i][j-1][0]+(k+1)*(k+1)时，用到了dp[i][j-1][0]显然对于j应该是正着迭代
// 再考虑p的迭代方向，不管p正向还是逆向，显然都没有问题，因为不管p的迭代方向如何dp[i][p][k+1]和dp[p+1][j-1][0]都已经是已知项了
int Solution::removeBoxes(vector<int>& boxes) {
    if (boxes.size() <= 1) return boxes.size();
    int n = boxes.size();
    // 统计boxes中每个元素的右侧有多少个和它相同的元素
    vector<int> cnt(n+1, 0);
    for (int i = 1; i <= n; i++) {
        for (int j = i+1; j <= n; j++)
            if (boxes[i-1] == boxes[j-1]) cnt[i]++;
    }
    vector<vector<vector<int>>> dp(n+1, vector<vector<int>> (n+1, vector<int> (n+1, 0)));
    for (int i = n; i >= 1; i--) {
        for (int j = i; j <= n; j++) {
            for (int k = 0; k <= cnt[j]; k++) {
                dp[i][j][k] = dp[i][j-1][0] + (k + 1) * (k + 1);
                for (int p = i; p < j; p++) {
                    if (boxes[p-1] == boxes[j-1])
                        dp[i][j][k] = max(dp[i][j][k], dp[i][p][k+1] + dp[p+1][j-1][0]);
                }
            }
        }
    }
    return dp[1][n][0];
}

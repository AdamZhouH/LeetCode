#include <vector>
#include <string>
#include <algorithm>
using namespace std;

// 可以想到的是一个动态规划的思路
// dp[n][k]表示前n个工作分配给k个人，能够得到的最大工作时间的最小值
// 则有dp[n][k] = min{
//          max{dp[n-1][k-1], jobs[n]},
//          max{dp[n-2][k-1], jobs[n-1]+jobs[n]},
//          ...
//          max{dp[k-1][k-1], jobs[k]+..jobs[n]}
//          ...
//          max{dp[0][k-1], jobs[n]+jobs[n-1]+...jobs[0}
//     }
//  但是，一想，这种状态转移肯定是不对，因为工作分配不是必须按照顺序来分的
//  实际上按照上面的状态转移方成来看，第k个人分配的工作可以是n个工作中任意选择的若干个
//  而不是之后的连续若干个
//  这里，找状态转移的大体框架是没有错的
//  问题在于状态转移写的不对，状态的表示不对
//  第k个人可以分配到的工作是n个工作中任意选择的一个工作，因此工作状态的分配其实有很多种情况
//  如果按照上面这种方法来写状态转移，那么需要将所有的状态转移写出来，这显然不太明智
//  这里要用到状态压缩方法，换一种思路来表示工作分配的状态
//  n个工作，一个具有n个bit的整数，就可以表示工作分配的一种状态
//  举个例子，010101，则表示第1、3、5的工作已经被分配给其他人了
//  那么，假定整数n表示工作分配的状态，dp[n][k]表示将n个工作分配给k个人的最小化最大化工作时间
//  那么，状态仍然按照前面的状态转移大致思路，我们可以得到状态转移方程
//  dp[n][k] = min{max{dp[n-m][k-1], s[m]},其中m应该是n的一个子集合}
//  解释一下上面的状态转移方程
//  由于状态用整数表示了，因此状态转移很好写，n-m表示的是从原集合n中分配整数m中的一些工作给第k个人之后，剩下的工作
//  m中的工作指的是m中bit位为1的那些bit表示的工作
//  显然，m因该是n的一个子集
//  如此，遍历所有的m，然后计算得到dp[n][k]的值
//  最终得到结果
//  显然，k小于等于工作的个数（题目规定）
//  注意初始条件以及s[m]的求和，s[m]表示m集合中的工作所花费的总时间
//  同样思路，求解s[m]时候，可用的是状态压缩的动态规划
//  s[m] = s[m1]+s[m2]，其中，m1和m2都是比m小的数字，任意一组m1 m2
//  只要满足，m1和m2中的工作加起来等于m中的工作即可
class Solution {
public:
    int minimumTimeRequired(vector<int>& jobs, int k);
};

int Solution::minimumTimeRequired(vector<int> &jobs, int k) {
    int n = jobs.size();
    // 由于一共具有2^n个状态，因此我们对每个状态都求一下和
    // 注意到，实际上，2^n的值其实有n+1位，并且最高位为0
    // 整数0表示不分陪任何工作的状态，而1111...1（n个1，值为2^n-1）表示分配所有工作的情况
    vector<int> totalTime(1<<n, 0);
    for (int i = 1; i < (1 << n); i++) {
        for (int j = 0; j < n; j++) {
            if ((i & (1 << j)) == 0) continue;
            else { 
                totalTime[i] = totalTime[i-(1<<j)] + jobs[j];
                break;
            }
        }
    }
    // 开始动态规划求解问题，根据状态转移方程填充数组
    vector<vector<int>> dp(k, vector<int> (1<<n, -1));
    // 初始化处理，只有1个人的情况
    for (int j = 0; j < (1<<n); j++) {
        dp[0][j] = totalTime[j];
    }
    for (int i = 1; i < k; i++) {
        for (int j = 0; j < (1<<n); j++) {
            // 求解dp[i][j]，枚举每个合法的k
            // 并且k是j的子集
            // 这里用个取巧的办法
            // 我们枚举所有j的子集，表示分配给第k个人的工作
            int minTime = INT_MAX;
            for (int k = j; k; k=(k-1)&j) {
                minTime = min(max(dp[i-1][j-k], totalTime[k]), minTime);
            }
            dp[i][j] = minTime;
        }
    }
    return dp[k-1][(1<<n)-1];
}

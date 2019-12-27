// 典型动态规划思路
// dp[i] = min(dp[i - coins[0]], dp[i - coins[1]], ...) + 1
// 具有最优子结构，上述便是用子问题的解组合出原问题的最优解的递推公式

// 本题可以基于不同的思路，给出不同的解法
// 从回溯到递归到动态规划，到BFS或者DFS(宽度搜索或者深度搜索)


#include <vector>
#include <string>
#include <iostream>
#include <algorithm>
#include <cmath>
using namespace std;


// 暴力法，递归思路
// 由于总金额给定，那么每一类型的硬币最多可以用的数量也是一定的
// 同一枚硬币可以选择不用的数量，分别选则一种，然后递归这种做法，直到选择完毕
class SolutionBacktrace {
public:
    int coinChange(const vector<int> &coins, int amount);
    int coinChange(int amount, const vector<int> &coins, int idx);
};

int SolutionBacktrace::coinChange(const vector<int> &coins, int amount) {
    return coinChange(amount, coins, 0);
}

int SolutionBacktrace::coinChange(int amount, const vector<int> &coins, int idx) {
    // 递归的边界条件
	if (amount == 0)
        return 0;
    if (idx >= coins.size() || amount < 0)
        return -1;
    int maxNumOfCurrCoin = amount / coins[idx];
    // 递归的核心部分
    int minCoins = -1;
    for (int i = 0; i <= maxNumOfCurrCoin; i++) {
        int ret = coinChange(amount - i * coins[idx], coins, idx + 1);
        if (ret >= 0) {
            if (minCoins != -1)
                minCoins = min(minCoins, ret + i);
            else
                minCoins = ret + i;
        }
    }
    return minCoins;
}

// 递归过程中很多子问题重叠计算，导致求解效率很低，因此采用动态规划的方法
// 具体递推公式已经在上面给出
class SolutionDynamics {
public:
    int coinChange(const vector<int> &coins, int amount);
};

int SolutionDynamics::coinChange(const vector<int> &coins, int amount) {
    // 初始化dp数组
    vector<int> dp(amount + 1, -1);
    dp[0] = 0;
    // 自底向上计算dp数组
    for (int i = 1; i <= amount; i++) {
        int numOfCoins = INT_MAX;
        for (int j = 0; j < coins.size(); j++) {
            // 原题中，coins数组中的元素不一定是按照非递减顺序排列，因此不能直接break，还是需要每个都遍历到
            if (i - coins[j] < 0) {
                break;
            } else if (dp[i - coins[j]] != -1) {
                numOfCoins = min(numOfCoins, dp[i - coins[j]] + 1);
            }
        }
        dp[i] = (numOfCoins == INT_MAX ? -1:numOfCoins);
    }
    return dp[amount];
}


int main(int argc, char *argv[]) {
    vector<int> coins = {3,83,404,474};
    int amount;
#ifdef USE_BACKTRACE
    cout << "Using BackTrace Algorithm" << endl;
    SolutionBacktrace solution;
#else
    cout << "Using Dynamics Algorithm" << endl;
    SolutionDynamics solution;
#endif
    while (cin >> amount) {
        cout << solution.coinChange(coins, amount) << endl;
    }
    return 0;
}

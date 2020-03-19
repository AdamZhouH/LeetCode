// 动态规划思想
#include <iostream>
using namespace std;
// 把一个数先拆成两个，再考虑这两个数分别怎么拆，能够得到最大值
// 很显然，递推公式为
// f(n) = max{f(1)*f(n-1), f(2)*f(n-2), .....f(n/2)*f(n-n/2)}, 因此，考虑动态规划的方法

class Solution {
public:
    int integerBreak(int n);
};

int Solution::integerBreak(int n) {
    if(n == 1 || n == 2)
        return 1;
    int *dp = new int[n + 1] {};
    dp[1] = dp[2] = 1;
    
    int i = 3;
    while (i <= n) {
        int currmax = 0;
        // 求f(i)
        for (int j = 1; j <= i / 2; j++) {
//          currmax = max(dp[j] * dp[i - j], currmax);
            currmax = max(currmax, max(j, dp[j]) * max(i - j, dp[i - j]));
        }
        dp[i] = currmax;
        i++;
    }
    int ret = dp[n];
    delete [] dp;
    return ret;
}

int main(void) {
    int val;
    Solution solu;
    while (cin >> val)
        cout << solu.integerBreak(val) << endl;
    return 0;
}
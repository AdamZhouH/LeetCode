class Solution {
public:
    int countPrimes(int n, int a);
    int countPrimes(int n);
};

// 先试一下暴力解法，看能不能过
// 然后采用最近学习到的筛法求素数

int Solution::countPrimes(int n, int a) {
    if (n <= 2)
        return 0;
    if (n == 3)
        return 1;
    int cnt = 1;
    for (int i = 3; i < n; i++) {
        int val = sqrt(i);
        bool isPrime = true;
        // 细节注意，如果蛮力使用判断条件为 j <= i，是错误的，不能加等号=，因为素数也可以被自身整除的，因此这个细节要注意
        for (int j = 2; j <= val; j++) {
            if (i % j == 0) {
                isPrime = false;
                break;
            }
        }
        if (isPrime)
            cnt++;
    }
    return cnt;
}

// 利用筛法求素数，具体的原理，还需要进一步弄清楚
// 数据结构上使用到了hash表结构

int Solution::countPrimes(int n) {
    if (n <= 2)
        return 0;
    if (n == 3)
        return 1;
    // 开始假设所有数字都是素数
    vector<int> dp(n, 1);
    dp[0] = dp[1] = 0;
    // 筛法去除合数
    for (int i = 2; i < dp.size(); i++) {
        if (dp[i]) {
            // 能够被i整除的数字都不是质数，因此筛去
            for (int k = i + i; k < n; k += i)
                dp[k] = 0;
        }
    }
    int cnt = 0;
    for (int i = 0; i < dp.size(); i++) {
        if (dp[i])
            cnt++;
    }
    return cnt;
}
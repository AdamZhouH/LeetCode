class Solution {
public:
    int numberOfArithmeticSlices(vector<int> &A);
};

/**
        // 动态规划的思路，拆分子问题，让dp[i]表示以A[i]为结尾的等差切分的个数，如果dp[i]非0，即以A[i]结尾存在等差切片
        // 那么dp[i]实际上就是以A[i]为结尾等差切片的最大长度
        // 如果A[i+1]可以和A[i]部分构成等差切片，那么显然，dp[i+1] = dp[i] + 1 
        // 如果dp[i]本身为0.说明不存在以A[i]为结尾的等差切片，那么此时考虑A[i+1] A[i] A[i-1]的等差关系，如果存在，则dp[i+1]=1
        // 否则为0
        
        // 综上，其实只要i元素与前两个元素构成等差，那么dp[i]=dp[i]+1，否则为0
*/

/*
int Solution::numberOfArithmeticSlices(vector<int> &A) {
    if (A.size() <3)
        return 0;
    vector<int> dp(A.size(), 0);
    int total = 0;
    for (int i = 2; i < A.size(); i++) {
        if ((A[i] + A[i -2]) == 2 * A[i - 1])
            dp[i] = dp[i-1] + 1;
        total += dp[i];
    }
    return total;
}
*/

// 实际上可以优化空间复杂度，因为dp数组可以不用，只要记录两个值即可
int Solution::numberOfArithmeticSlices(vector<int> &A) {
    if (A.size() < 3)
        return 0;
    int total = 0, dp0 = 0, dp1 = 0;
    for (int i = 2; i < A.size(); i++) {
        if ((A[i - 2] + A[i]) == 2 * A[i - 1])
            dp1 = dp0 + 1;
        else
            dp1 = 0;
        total += dp1;
        dp0 = dp1;
    }
    return total;
} 

#include <iostream>
#include <vector>
#include <unordered_map>
#include <unordered_set>
using namespace std;

class Solution {
public:
    int lenLongestFibSubseq(vector<int>& A);
};

int Solution::lenLongestFibSubseq(vector<int> &A) {
    if (A.size() < 3) return 0;
    unordered_map<int,int> index;
    for (int i = 0; i < A.size(); i++) index[A[i]] = i;
    vector<int> dp(A.size(), 0);
    if (A[2] - A[1] == A[0]) dp[2] = 1;
    int maxLen = dp[2];
    for (int i = 3; i <= dp.size(); i++) {
        int currLen = 0;
        for (int j = i - 1; j >= 1; j--) {
            if (!index.count(A[i] - A[j]) || index[A[i] - A[j]] >= j) continue;
            else currLen = max(currLen, dp[index[A[i] - A[j]]] + 1);
        }
        dp[i] = currLen;
        maxLen = max(maxLen, dp[i]);
    }
    return maxLen;
}

// 补充一个动态规划写法
// 这里的动态规划其实有点奇怪
// dp[i][j]表示最后两个数为A[i]和A[j]的Fobinacci数列长度
// 则状态转移如下
// 如果A[j]-A[i]存在，并且该元素位置在i之前，则dp[i][j] = dp[A[j]-A[i]][i] == 0 ? 3: dp[A[j]-A[i]][i] + 1
// 如果A[j]-A[i]不存在，或者存在但是位置在i之后，则显然没有相应的Fibonacci数列，故dp[i][j] = 0
class Solution2 {
public:
    int lenLongestFibSubseq(vector<int>& A);
};

int Solution2::lenLongestFibSubseq(vector<int> &A) {
    if (A.size() < 3) return 0;
    unordered_map<int,int> index;
    for (int i = 0; i < A.size(); i++) index[A[i]] = i;
    vector<vector<int>> dp(A.size(), vector<int> (A.size(), 0));
    if (A[0] == A[2] - A[1]) dp[1][2] = 3;
    int maxlen = dp[1][2];
    for (int j = 3; j < A.size(); j++) {
        for (int i = j - 1; i >= 1; i--) {
            if (!index.count(A[j] - A[i]) || index[A[j] - A[i]] >= i) continue;
            else dp[i][j] = dp[index[A[j] - A[i]]][i] == 0 ?3 : dp[index[A[j] - A[i]]][i] + 1;
            maxlen = max(maxlen, dp[i][j]);
        }
    }
    return maxlen;
}





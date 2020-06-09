#include <vector>
#include <iostream>
#include <string>
#include <unordered_map>
#include <unordered_set>
#include <set>
using namespace std;

class Solution {
public:
    int longestArithSeqLength(vector<int>& A);
};

// 等差序列的确定需要至少两个值（和求最长Fibonacci子序列的方式类似，当确定了最后两个值，整个等差数列也就确定了）
// 因此是一个二维dp，注意用map加速查找过程即可
// 注意，等差数列中可能存在重复的数据，因此一个值的下标可能有多个，都要记录
int Solution::longestArithSeqLength(vector<int> &A) {
    if (A.size() <= 2) return A.size();
    vector<vector<int>> dp(A.size(), vector<int>(A.size(), 0));
    unordered_map<int, set<int>> idx;
    for (int i = 0; i < A.size(); i++) idx[A[i]].insert(i);
    // 当A数组数据元素的个数超过3个时，显然最短都可以任意选择两个数字作为一组等差数列
    // 因此，只需要求出长度为3及以上的长度的等差数列即可
    int maxlen = 2;
    for (int j = 2; j < A.size(); j++) {
        for (int i = j - 1; i >= 1; i--) {
            if (!idx.count(2*A[i]-A[j]) || *(idx[2*A[i]-A[j]].begin()) >= i) continue;
            for (auto it = idx[2*A[i]-A[j]].rbegin(); it != idx[2*A[i]-A[j]].rend(); it++) {
                if (*it < i) {
                    dp[i][j] = dp[*it][i] == 0 ? 3 : dp[*it][i] + 1;
                    break;
                }
            }
            maxlen = max(maxlen, dp[i][j]);
        }
    }
    return maxlen;
}

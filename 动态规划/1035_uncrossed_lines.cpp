#include <iostream>
#include <string>
#include <vector>
using namespace std;

class Solution {
public:
    int maxUncrossedLines(vector<int>& A, vector<int>& B);
};

// using dynamic programming to solve the problem like longest Common Subsequence
// dp[i][j] means the maximum lines that we can draw when using A[1:i] B[1:j]
int Solution::maxUncrossedLines(vector<int> &A, vector<int> &B) {
    vector<vector<int>> dp(A.size()+1, vector<int> (B.size()+1, 0));
    int maxline = 0;
    for (int i = 1; i <= A.size(); i++) {
        for (int j = 1; j <= B.size(); j++) {
            if (A[i-1] == B[j-1]) dp[i][j] = dp[i-1][j-1] + 1;
            else dp[i][j] = max(dp[i-1][j], dp[i][j-1]);
            maxline = max(maxline, dp[i][j]);
        }
    }
    return maxline;
}

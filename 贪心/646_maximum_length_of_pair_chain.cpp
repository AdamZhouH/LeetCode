class Solution {
public:
    int findLongestChain(vector<vector<int>>& pairs);
};

// Dynamic programming Method
int Solution::findLongestChain(vector<vector<int>> &pairs) {
    if (pairs.size() <= 1) return pairs.size();
    vector<int> dp(pairs.size(), 1);
    sort(pairs.begin(), pairs.end());
    int maxlen = 1;
    for (int i = 1; i < dp.size(); i++) {
        for (int j = 0; j < i; j++) {
            if (pairs[j][1] < pairs[i][0]) dp[i] = max(dp[i], dp[j] + 1);
        }
        maxlen = max(maxlen, dp[i]);
    }
    return maxlen;
}

// Greedy Method
int findLongestChain(vector<vector<int>> &pairs) {
    if (pairs.size() <= 1) return pairs.size();
    sort(pairs.begin(), pairs.end(), [](vector<int>&a, vector<int>&b){return a[1]<b[1];});
    int cnt = 1, prev = 0;
    for (int i = 1; i < pairs.size(); i++) {
        if (pairs[i][0] > pairs[prev][1]) {
            cnt++;
            prev= i;
        }
    }
    return cnt;
}

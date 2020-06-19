#include <vector>
#include <string>
#include <algorithm>
using namespace std;

class Solution {
public:
    int maxEnvelopes(vector<vector<int>>& envelopes);
};

int Solution::maxEnvelopes(vector<vector<int>>& envelopes) {
    if (envelopes.size() <= 1) return envelopes.size();
    sort(envelopes.begin(), envelopes.end()); // vector可以直接排序
    vector<int> dp(envelopes.size(), 1);
    int ms = 1;
    for (int i = 1; i < envelopes.size(); i++) {
        for (int j = 0; j < i; j++) {
            if (envelopes[j][0] < envelopes[i][0] && envelopes[j][1] < envelopes[i][1])
                dp[i] = max(dp[i], dp[j]+1);
        }
        ms = max(ms, dp[i]);
    }
    return ms;
}

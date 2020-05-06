#include <iostream>
#include <vector>
#include <algorithm>
#include <map>
#include <set>
#include <unordered_map>
#include <unordered_set>
#include <deque>
using namespace std;

class Solution {
public:
    int mincostTickets(vector<int>& days, vector<int>& costs);
};

// 某个days[k]后，三种选择方案，1天、7天、30天，然后可以cover到目前的days[i]，选择三者中最小的总cost即可
// 如果用1天cover到，那只能是在当前天数，也就是第days[i]天买一张1天的票
// 如果用7天的coever到，那么往前找一个days[j]，使得days[i]与days[j]的差刚好大于等于7，也就是说在dasys[j]或者之后的某一天，买一张7天的票，可以cover到days[i]
// 如果用30天的cover到，同理可推
int Solution::mincostTickets(vector<int> &days, vector<int> &costs) {
    vector<int> dp(days.size(), 0);
    dp[0] = min({costs[0], costs[1], costs[2]});
    for (int i = 1; i < dp.size(); i++) {
        int j = i, k = i;
        while (j <= i && j >= 0 && days[i] - days[j] < 7) j--;
        while (k <= i && k >= 0 && days[i] - days[k] < 30) k--;
        dp[i] = min({dp[i-1] + costs[0], (j>=0?dp[j]+costs[1]:costs[1]), (k>=0?dp[k]+costs[2]:costs[2])});
    }
    return dp.back();
}

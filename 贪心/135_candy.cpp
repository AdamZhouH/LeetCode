#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <queue>
using namespace std;
#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
using namespace std;

// 算法思路
// 考虑贪心和动态规划，动态规划使用双向
// 先从左侧开始往右扫描，是的左边的关系满足（但是右边关系可能不满足，比如 评分 3 2 1 获取的糖果数目就是 dp[3] 1 1，显然，后面的两个是不满足的）
// 然后从从开始往左侧扫描，使得右边关系满足
// 局部贪心问题
// dp[i]表示第i个孩子至少应该分到的糖果数目

class Solution {
public:
	int candy(vector<int>& ratings);
};

int Solution::candy(vector<int>& ratings) {
    if (ratings.empty())
        return 0;
	vector<int> dp(ratings.size());
    dp[0] = 1;
    for (int i = 1; i < dp.size(); i++) {
        if (ratings[i] > ratings[i - 1])
            dp[i] = dp[i - 1] + 1;
        else
            dp[i] = 1;
    }
    for (int i = dp.size() - 2; i >= 0; i--) {
        if (ratings[i] > ratings[i + 1] && dp[i] <= dp[i + 1])
            dp[i] = dp[i + 1] + 1;
    }
    return accumulate(dp.begin(), dp.end(), 0);
}
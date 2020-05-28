class Solution {
public:
    int maxProfit(vector<int>& prices);
};

/////////////////////////////原始递归
// 原始的递归思路
// 首先，每一天你都有三种选择
// 1.什么都不做
// 2.卖出股票，当然，这一天之前，你必须已经先买入了股票
// 3.买入股票，当然，这一天之前，你必须不持有股票（也就是说之前了股票然后抛出了或者根本没买）
// 考虑某一天，你不持有股票，你可以选择行为1或者行为3
// 考虑某一天，你持有股票，你可以选择行为1或者行为2
// 以上情况说明了，在递归过程中，我们必须知道当前持有或者不持有股票，从而选择下一步的行为，因此需要传入一个flag变量做标记
// 现在考虑dfs的参数和返回值，dfs的参数，显然有prices数组，当前状态，当前是第几天，以及当前的收益
// dfs的返回值应该是以当前的状态为基准，往后作出买卖股票后能够得到的最大收益
// 再考虑基准情况，显然是当前是最后一天了，那么如果有股票必须卖掉，没有股票，那么不能再买股票了
// 因此，dfs版本的思路就很清晰了，设定flag为0表示不持有，flag为1表示持有股票
// 通过dfs也很容易想到从dfs到动态规划的思路(动态规划就是对dfs过程的优化，避免重复计算子问题)
// 这个dfs肯定是超时的，而且在比较小的数据上就会超时，仅提供一种解题的思路和思考过程
int Solution::dfs(vector<int>& prices, int i, int flag, int profit) {
	if (i == prices.size() - 1) {
		if (flag == 1) return profit + prices[i];
		else return profit;
	}
	int ans = 0;
	if (flag == 0) ans = max(ans, dfs(prices, i+1, 1, profit - prices[i]));
	else ans = max(ans, dfs(prices, i+1, 0, profit + prices[i]));
	ans = max(ans, dfs(prices, i+1, flag, profit));
	return ans;
}

int Solution::maxProfit(vector<int>& prices) {
	return dfs(prices, 0, 0, 0);
}

/////////////////////////////动态规划优化
// 动态规划的思路
// dp[i][0] 表示第i天持有股票时的现金收入(可能为负数，因为买股票需要成本)
// dp[i][1] 表示第i天不持有股票时的现金收入
// 则状态转移分析如下：
// dp[i][0] 是第i天持有股票的情况，这个股票可能时前一天就持有，也可能是前一天没有，但是今天刚买入的
// dp[i][1] 是第i天不持有股票的情况，这个情况可能是前一天就没有股票，然后保持到今天，也可能是今天把前一天持有的股票都卖掉了
// 因此能够得到状态转移方程
// dp[i][0] = max(dp[i-1][0], dp[i-1][1]-prices[i])
// dp[i][1] = max(dp[i-1][1], dp[i-1][0]+prices[i])
// 注意初始条件，当i=1时，dp[1][0]=-prices[0],dp[1][1]=0
// 表示第一天如果持有，只能是当天就买入，如果第一天不持有，也就是第一天没有买
int Solution::maxProfit(vector<int>& prices) {
	vector<vector<int>> dp(prices.size()+1, vector<int>(2,0));
	dp[1][0] = -prices[0], dp[1][1] = 0;
	for (int i = 2; i <= prices.size(); i++) {
		dp[i][0] = max(dp[i-1][0], dp[i-1][1] - prices[i-1]);
		dp[i][1] = max(dp[i-1][1], dp[i-1][0] + prices[i-1]);
	}
	return dp[prices.size()][1];
}

/////////////////////////////贪心算法
// 贪心思路，这个不多说
int Solution::maxProfit(vector<int>& prices) {
	int ans = 0;
	for (int i = 1; i < prices.size(); i++) 
		if (prices[i] > prices[i-1]) ans += prices[i]- prices[i-1];
	return ans;
}

/////////////////////////////另一种动态规划思路
// 贴一个另外的比较容易想到的动态规划思路，虽然超时了
// dp[i]表示假如最后一次卖出股票在第i天，能够获得最大收益
// 显然，最后一次买入肯定在第1到第i-1的某个一天，而上一次的卖出则在最后一次买入之前的某个事件
// dp[i] = max{dp[j] + max(prices[i] - minPriceOf(j+1,i-1), 0)} 其中，j从0取到i-2
// 取0表示此前没有卖出过股票，j最大为i-2是因为不能同一天有买入卖出两种操作，因此至少应该在第i-1买入
// max(prices[i] - minPriceOf(j+1,i-1), 0)则是避免负收入的情况，因为如果买入股票导致损失，那不如不买
// 最后，在第199个测试用例超时了 ——！
int Solution::maxProfit(vector<int>& prices) {
    int maxprofit = 0;
    vector<int> dp(prices.size()+1, 0);
    for (int i = 1; i <= prices.size(); i++) {
        int profit = 0;
        for (int j = 0; j < i-1; j++) {
            int minprices = INT_MAX;
            for (int k = j+1; k < i; k++) minprices = min(minprices, prices[k-1]);
            profit = max(profit, dp[j] + max(0, prices[i-1]-minprices));
        }
        dp[i] = profit;
        maxprofit = max(maxprofit, dp[i]);
    }
    return maxprofit;
}
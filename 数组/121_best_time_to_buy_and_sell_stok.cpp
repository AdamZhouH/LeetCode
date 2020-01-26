class Solution {
public:
    int maxProfit(vector<int>& prices) {
        if (prices.size() <= 1)
            return 0;
        int currMin = min(prices[0], prices[1]);
        int maxP = prices[1] - currMin;
        for (int i = 2; i < prices.size(); i++) {
            currMin = min(currMin, prices[i]);
            maxP = max(maxP, prices[i] - currMin);
        }
        return maxP;
    }
};
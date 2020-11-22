#include <vector>
#include <algorithm>
using namespace std;

// 这题在于多出了一个冷冻期的状态，因此在买股票之前，必须保证前一天不持有股票并且没有卖出动作
// 问题的解决方案：考虑当前两种状态，持有股票，不持有股票
// 找到地推方程，然后就好写了
class Solution {
public:
    int maxProfit(vector<int>& prices) {
        if (prices.empty()) return 0;
        vector<int> hold(prices.size()+1, 0);
        vector<int> unhold(prices.size()+1, 0);
        hold[1] = -prices[0];
        for (int i = 2; i <= prices.size(); i++) {
            hold[i] = max(hold[i-1], unhold[i-2]-prices[i-1]);
            unhold[i] = max(hold[i-1]+prices[i-1], unhold[i-1]);
        }
        return max(hold.back(), unhold.back());
    }
};  

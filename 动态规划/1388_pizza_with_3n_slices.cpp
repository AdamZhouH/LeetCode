#include <iostream>
#include <vector>
#include <algorithm>
#include <string>
using namespace std;

class Solution {
public:
	int maxSizeSlices(vector<int>& slices);
};

/**
 * 思路分析
 * 首先草稿纸上尝试选择若干元素，可以发现，实际上是在3n个元素中选择任意n个不相邻的元素
 * 考虑动态规划，考虑子问题，缩减元素个数，比如目前存在0~j个元素，现在新增一个元素j+1
 * 则两种情况新增元素j+1可以选择，也可以不选择，假设设立一个一唯的dp数组，那么dp[j]的意义
 * 应该是选择第j个元素的情况下，具有的最优解，但是这样理解好像还缺了点东西，首先，不知道当前选择的是第几个元素
 * 因此还需要一个信息，表示当前选的是第几个元素，因此dp再加一个维度，dp[i][j]表示，从0~j中选择i+1个元素
 * 并且第i个元素一定选择nums[j]
 * 但是考虑一种情况，dp[i][j]中，j相比i非常小，那么0~j中根本选不出i+1个元素，此时dp[i][j]如果还表示从0~j中选择出i+1个元素
 * 那么显然和实际是不相符的，也非常不好理解dp数组的边界条件，而对于dp数组的实际物理意义的理解也决定着递推关系的确定
 * 因此dp[i][j]应该理解为从0~j个元素中，选择出至多i+1个元素，而且最后一个元素不一定就选择了nums[j]，这种理解更加符合实际
 * 这样就能解释好当j小于i的情况，同时也明确了递推公式
 * 两种情况：nums[j]不选和nums[j]选
 * 则递推关系为
 * dp[i][j] = max( 
 *		dp[i][j-1]   // 第j个元素不选，从0-j-1中选择至多i个元素
 *		dp[i-1][j-2] + nums[j] // 第j个元素选择，那么之下至多i-1个元素则从0-j-2选择，j-2是为了符合题意，保证最后一个元素也不和j相邻
 *					 // 需要注意理解的是，若j<2时，说明j之前最多只有1个元素，那么只能选择j处的元素本身，因为j-2不存在，也就是没有元素
 *					 // 此时dp[i][j] = nums[j]，实际上就是说dp[i-1][j-2]中一个元素都没有选择
 *		)
 * 还需要注意的是，首尾元素不相连，因此，需要两次dp，一次不使用首元素，一次不使用尾元素
 */

int Solution::maxSizeSlices(vector<int>& slices) {
	int n = slices.size() / 3;
	vector<vector<int>> dp1(n, vector<int> (slices.size() - 1, 0));
	vector<vector<int>> dp2(n, vector<int> (slices.size() - 1, 0));
	// 不使用首元素 初始化dp1，实际上是初始化dp1[0][j]的值，dp[0][j]表示从0-j中至多只选择1个元素得到的最大值
	// 若j元素处的值选择，则只选这一个，若j处的不选，显然应该选择0-j-1处的最大值
	// 因此dp1[0][j]实际上就是选择当前的最大元素
	int currMax = 0;
	for (int i = 1; i < slices.size(); i++) {
		currMax = max(currMax, slices[i]);
		dp1[0][i-1] = currMax;
	}
	// 填充dp数组
	for (int i = 1; i < dp1.size(); i++) {
		for (int j = 0; j < dp1[0].size(); j++) {
			dp1[i][j] = (j < 2) ? slices[j+1] : max(dp1[i-1][j-2] + slices[j+1], dp1[i][j-1]);
		}
	}
	// 初始化第二个dp2数组，slices最后一个元素不使用
	currMax = 0;
	for (int i = 0; i < (slices.size() - 1); i++) {
		currMax = max(currMax, slices[i]);
		dp2[0][i] = currMax;
	}
	for (int i = 1; i < dp2.size(); i++) {
		for (int j = 0; j < dp2[0].size(); j++) {
			dp2[i][j] = (j < 2) ? slices[j] : max(dp2[i-1][j-2] + slices[j], dp2[i][j-1]);
		}
	}
	return max(dp1[n-1].back(), dp2[n-1].back());
}
int main(void) {
	// vector<int> slices = {1,2,3,4,5,6};
	// vector<int> slices = {4,1,2,5,8,3,1,9,7};
	vector<int> slices = {3,1,2};
	Solution slu;
	cout << slu.maxSizeSlices(slices) << endl;
	return 0;
}

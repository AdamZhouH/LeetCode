// 152_maximum_product_subarray.cpp
// 最大的连续子序列乘积
// 考虑动态规划或者分治疗思路都可以求解
// 我们先用动态规划的思维去思考，先找到子问题和递归或者递推公式
// a[0:N]的上述问题的解，可能连续子序列的最后一个数为a[0] a[1]...a[n-1]
// 因此，考虑子问题为以位置0开头，k为结尾且包含k的范围内的最大连续序列的乘积，记为max(k)
// 则原来问题等价为 max{max(0), max(1), ....max(n-1)} 一维动态规划
// 主要就是考虑清楚两者异号的时候存在什么情况

// max(k)和a[k+1]均为正数，且max(i, k)*a[k+1] > max(i, k)，那么有 max(i, k+1) = max(i, k) * a[k+1]
// max(k)和a[k+1]一正一负，如果max(i, k)>0，a[k+1] < 0，那么乘积<0，而max(i, k+1)要包含a[k+1]，所以max(k+1) = a[k+1]，反之亦然
// max(k)为正数，a[k+1]为负数，不过max(i, k)之前相连的序列里有负数，那么前面包含负数的这个序列，必然是一个前面序列的最小值，此时max(i, k+1) = min(i, k) * a[k+1]
// 概括起来，包含第k+1个元素为结尾的序列最大乘积应该取自上述三种情况之一：max(k+1) = max(max(k) * a[k+1],  a[k+1], min(k) * a[k+1])。
// 按照同样的道理，我们求得的包含k+1在内结尾的最小乘积序列为：min(i, k+1) = min(min(k) * a[k+1], a[k+1], max(k) * a[k+1])



#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
using namespace std;

class Solution {
public:
	int maxProduct(vector<int>& nums);
};

int Solution::maxProduct(vector<int> &nums) {
	if (nums.size() == 1)
		return nums[0];
	int currMax = nums[0];
	int currMin = nums[0];
	int maxResult = nums[0];

	int length = nums.size();
	// 计算从0 到 i 结尾并且包括 i 的最大连续子序列的乘积
	for (int i = 1; i < length; i++) {
		int var1 = currMax * nums[i], var2 = currMin * nums[i];
		currMax = max(max(var1, var2), nums[i]);
		currMin = min(min(var1, var2), nums[i]);
		maxResult = max(currMax, maxResult);
	}
	return maxResult;
}

int main(void) {
	vector<int> vec;
	int var;
	while (cin >> var) 
		vec.push_back(var);
	Solution solution;
	cout << "Maximum product subarray is " << solution.maxProduct(vec) << endl;
	return 0;
}
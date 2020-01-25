#include <vector>
#include <iostream>
#include <algorithm>
using namespace std;

class Solution {
public:
	vector<vector<int>> permute(vector<int> &nums);
	void help(vector<int> &nums, vector<vector<int>> &ret, vector<int> &curr, int index);
};

// 暴力递归思路
// 加上回溯
// 先选定当前数组中某个值作为第一个值，然后接下去递归排列
// 返回时，需要把之前的值复原，不影响其他排列的递归
vector<vector<int>> Solution::permute(vector<int> &nums) {
	vector<vector<int>> ret;
	vector<int> curr;
	help(nums, ret, curr, 0);
	return ret;
}

void Solution::help(vector<int> &nums, vector<vector<int>> &ret, vector<int> &curr, int index) {
	// base condition
	if (index == nums.size() - 1) {
		curr.push_back(nums[index]);
		ret.push_back(curr);
		curr.pop_back();
		return;
	}
	// recursive condition
	for (int i = index; i <= nums.size() - 1; i++) {
		// 交换index处和i处的值，然后选择index处的值push到curr数组，继续递归
		// 返回后交换回原位置
		int temp = nums[index];
		nums[index] = nums[i];
		nums[i] = temp;
		curr.push_back(nums[index]);
		help(nums, ret, curr, index + 1);
		nums[i] = nums[index];
		nums[index] = temp;
		curr.pop_back();
	}
}


int main(int argc, char *argv[]) {
	vector<int> nums = {1,2,3};
	Solution solu;
	auto ret = solu.permute(nums);
	for (auto &c : ret) {
		for (auto var : c) {
			cout << var << ' ';
		}
		cout << endl;
	}
	return 0;
}

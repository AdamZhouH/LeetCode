// 组合总数
// 给定一个没有重复的数组，和一个目标数
// 找到其中的所有和为目标数的组合，数组中的数字可以无限制的重复获取

// 算法思想，应该使用回溯算法，利用递归完成

#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
using namespace std;

class Solution {
public:
	vector<vector<int>> combinationSum(vector<int> & candidates, int target);
};





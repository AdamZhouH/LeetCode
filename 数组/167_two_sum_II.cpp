#include <iostream>
#include <string>
#include <algorithm>
#include <vector>
using namespace std;

/**
 *  假定给定的数组是按照升序排列
 *  可以假定每个输入存在唯一的答案
 *  要求不使用重复的元素
 */

/**
 *  既然是已经排序，则可以考虑双指针，往中间靠近
 *  同时注意，不能使用重复的元素
 */

class Solution {
public:
    vector<int> twoSum(vector<int>& numbers, int target);
};

vector<int> Solution::twoSum(vector<int> &numbers, int target) {
	vector<int> ret;
	int i = 0, j = numbers.size() - 1;
	while (i < j) {
		int sum = numbers[i] + numbers[j];
		if (sum == target) {
			ret = {i + 1, j + 1};
			break;
		} else if (sum > target) {
			j--;
		} else {
			i++;
		}
	}
	return ret;
}
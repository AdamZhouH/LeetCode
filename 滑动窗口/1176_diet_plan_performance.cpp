#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

class Solution {
public:
	int dietPlanPerformance(vector<int> &calories, int k, int lower, int upper);
};

int Solution::dietPlanPerformance(vector<int> &calories, int k, int lower, int upper) {
	int ret = 0;
	int windowSize = 0;
	for (int i = 0; i < k; i++)
		windowSize += calories[i];
	if (windowSize > upper)
		ret++;
	else if (windowSize < lower)
		ret--;
	// 从第二天开始统计
	for (int i = 1; i < calories.size() && i + k -1 < calories.size(); i++) {
		windowSize -= calories[i - 1];
		windowSize += calories[i + k - 1];
		if (windowSize > upper)
			ret++;
		else if (windowSize < lower)
			ret--;
	}
	return ret;
}


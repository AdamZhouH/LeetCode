#include <iostream>
#include <algorithm>
#include <vector>
using namespace std;

// 也是非常明显的二分思路，这次是找左边界，当mid元素等于target时，也不能立刻返回
// 应该将右边界往左继续走
// The API isBadVersion is defined for you.
// bool isBadVersion(int version);

class Solution {
public:
    int firstBadVersion(int n);
};

int Solution::firstBadVersion(int n) {
	int left = 1, right = n;
	while (left <= right) {
		int mid = left + (right - left) / 2;
		bool ret = isBadVersion(mid);
		if (!ret) left = mid + 1;
		else right = mid - 1;
	}
	return left;
}
#include <queue>
#include <vector>
#include <algorithm>
#include <unordered_set>
using namespace std;

class Solution {
public:
    int kthSmallest(vector<vector<int>>& matrix, int k);
};

// 首先想到的是可以利用大小为k的大根堆来做
// Leetcode可以过，但是时间复杂度比较高
int Solution::kthSmallest(vector<vector<int>>& matrix, int k) {
    priority_queue<int, vector<int>, less<int>> q;
	int m = matrix.size(), n = matrix[0].size();
	for (int i = 0; i < m; i++) {
		for (int j = 0; j < n; j++) {
			if (q.size() < k) q.push(matrix[i][j]);
			else if (q.top() > matrix[i][j]) { q.pop(); q.push(matrix[i][j]); } 
		}
	}
	return q.top();
}

// 效率更高的算法则是使用二分思路，找到第k小的元素
// 首先，最大元素和最小元素我们知道，那么计算mid，判断矩阵中多少元素小于等于mid，若个数小于k，说明第k个元素比mid元素更大
// 若个数大于等于k，说明第k个元素至少不大于当前mid元素，则right往左移动
// 类似于利用二分法查找左边界，并且题目中这个左边界一定可以找到，因此一定最终left指向第k个元素
// (实际上是right的值为第k个元素-1，但是退出循环时，left刚好比right大1，因此直接返回left了)
int kthSmallest(vector<vector<int>>& matrix, int k) {
    int left = matrix[0][0], right = matrix.back().back();
    while (left <= right) {
        int mid = left + (right - left ) / 2;
        int cnt = 0;
        for (auto &vec: matrix)
            cnt += upper_bound(vec.begin(), vec.end(), mid) - vec.begin();
        if (cnt < k) left = mid + 1;
        else right = mid - 1;
    }
    return left;
}
#include <vector>
#include <string>
#include <iostream>
#include <algorithm>
#include <cassert>
using namespace std;

/**
 * 如果直接暴力破解，思路很简单，直接一个个比较，直到第(m+n)/2个元素，但是时间复杂度为O(m+n)
 * 但题目要求的时间复杂度为log(m+n)，同时两个数组是有序的，这也提示了使用二分查找思路
 * 求median元素实际上是求第(m+n)/2大的元素，问题可以拓展为查找两个数组中第k大的元素
 * 考虑这种思路，每次比较nums1和nums2中的第k/2个元素，比较他们的大小
 *      若相等，则这两个元素的值就是整个数组的中间值
 *      若nums1[k/2]>nums2[k/2]，则说明整个数组的topK个元素中(这里的top显然是元素越小越top)，nums2的前k/2个
 *      元素一定在topk元素中，反证可轻易证明这一点，因此这部分元素中肯定没有第topK个元素，并且比第topK个元素小
 *      因此从剩下的B[k/2:]和整个A数组中找第k/2个元素即为所求
 *      若nums1[k/2]<nums2[k/2]，同理，nums1的前k/2个元素一定在整体的topK元素内，因此从剩下的元素中，找到整体的第k/2个元素
 * 还要注意的是当元素个数为偶数时，取中间两个元素的平均数
*/
#define BINARY_SEARCH
#ifdef BINARY_SEARCH
// 二分查找实现算法
class Solution {
public:
	double findMedianSortedArrays(vector<int> &nums1, vector<int> &nums2);
	// 找到在两个数组中第K小的数字
	int findKthInSortedArrays(vector<int> &nums1, int beg1, int m, vector<int> &nums2, int beg2, int n, int k);
};

int Solution::findKthInSortedArrays(vector<int> &nums1, int beg1, int m, vector<int> &nums2, int beg2, int n, int k) {
	// 从两个数组中一共取出k个元素，按照每个数组取出前k/2个元素，这样可以保证log的时间复杂度(因为用的是二分的方法取)
	// 但可能元素较少的数组中不够k/2个元素，因此需要判断一下能否从较小的数组中取出k/2个，不能的话可以直接将全部元素
	// 取出，并且在另一个数组中取出前k-m个即可，这样保证取出的元素个数一共仍是k个
	// 当较少个数元素的数组为空时，直接取出另一个数组的首个元素(一定存在，可以用反证法说明)
	// 同时注意边界情况，当k为1时，意思是取出一个元素，可以直接判断
	if (m > n) {
		return findKthInSortedArrays(nums2, beg2, n, nums1, beg1, m, k);
	}
	if (m == 0) {
		assert(k <= n);
		return nums2[k - 1];
	}
	if (k == 1) {
		return min(nums1[beg1], nums2[beg2]);
	}
	// 分别计算从nums1和nums2中取出多少个元素
	int fetchLenOfA = min(k/2, m);
	int fetchLenOfB = k - fetchLenOfA;
	if (nums1[beg1 + fetchLenOfA - 1] == nums2[beg2 + fetchLenOfB - 1])
		return nums1[beg1 + fetchLenOfA - 1];
	else if (nums1[beg1 + fetchLenOfA - 1] > nums2[beg2 + fetchLenOfB - 1])
		return findKthInSortedArrays(nums1, beg1, m, nums2, beg2 + fetchLenOfB, n - fetchLenOfB, k - fetchLenOfB);
	else
		return findKthInSortedArrays(nums1, beg1 + fetchLenOfA, m - fetchLenOfA, nums2, beg2, n, k - fetchLenOfA);
}

double Solution::findMedianSortedArrays(vector<int> &nums1, vector<int> &nums2) {
	if ((nums1.size() + nums2.size()) & 0x1) {
		return static_cast<double>(findKthInSortedArrays(nums1, 0, nums1.size(), nums2, 0, nums2.size(), (nums1.size() + nums2.size())/2 + 1));
	} else {
		int a = findKthInSortedArrays(nums1, 0, nums1.size(), nums2, 0, nums2.size(), (nums1.size() + nums2.size())/2);
		int b = findKthInSortedArrays(nums1, 0, nums1.size(), nums2, 0, nums2.size(), (nums1.size() + nums2.size())/2 + 1);
		cout << "Two var: " << a << ' ' << b << endl;
		return (a + b) / 2.0;
	}
}
#else
class Solution {
public:
    double findMedianSortedArrays(vector<int>  &nums1, vector<int> &nums2);
};

double Solution::findMedianSortedArrays(vector<int> &nums1, vector<int> &nums2) {
	// 注意总元素的个数为奇数还是偶数，为偶数则取中间两个数的均值
	// 题目中假定了两个vector均非空(即一共至少两个元素)，因此这里不做判断
	// 先取第k/2个元素，如果元素总个数为偶数，则再取第k+1个元素(这里是次序而非下标，下标要-1)
	int i = 0, j = 0;
	int k = (nums1.size() + nums2.size()) / 2;
	// 找到第k个元素
	int var1, var2;
	while (k--) {
		if (i < nums1.size() && j < nums2.size()) {
			if (nums1[i] <= nums2[j])
				var1 = nums1[i++];
			else
				var1 = nums2[j++];
		} else if (i >= nums1.size()) {
			var1 = nums2[j++];
		} else {
			var1 = nums1[i++];
		}
	}
	// 找到第k+1个元素，因为，如果元素总数为奇数，则应该返回第k+1个元素
	// 否则返回两者均值
	if (i >= nums1.size())
		var2 = nums2[j];
	else if (j >= nums2.size())
		var2 = nums1[i];
	else 
		var2 = min(nums1[i], nums2[j]);
	if ((nums1.size() + nums2.size()) % 2)
		return double(var2);
	// cout << "Two vars : " << var1 << ' ' << var2 << endl;
	return (var1 + var2) / 2.0;
}
#endif


// 精简一点的写法
class Solution3 {
public:
	double findMedianSortedArrays(vector<int> &nums1, vector<int> &nums2);
	int findKth(vector<int> &nums1, int beg1, int m, vector<int> &nums2, int beg2, int n, int k);
};

int Solution3::findKth(vector<int> &nums1, int i, int m, vector<int> &nums2, int j, int n, int k) {
	if (m <= 0) return nums2[j+k-1];
    if (n <= 0) return nums1[i+k-1];
    if (k == 1) return min(nums1[i], nums2[j]);
    int a = (m >= k/2) ? k/2 : m;
    int b = (n >= k-a) ? k-a : n;
    if (nums1[i+a-1] > nums2[j+b-1]) return findKth(nums1,i,m,nums2,j+b,n-b,k-b);
    else return findKth(nums1,i+a,m-a,nums2,j,n,k-a);
}

double Solution3::findMedianSortedArrays(vector<int> &nums1, vector<int> &nums2) {
	int len = nums1.size() + nums2.size();
    if (len % 2) return (double)findKth(nums1, 0, nums1.size(), nums2, 0, nums2.size(), len/2+1);
    else return ((double)findKth(nums1, 0, nums1.size(),nums2, 0, nums2.size(),len/2)
               + (double)findKth(nums1, 0, nums1.size(), nums2, 0, nums2.size(), len/2+1)) / 2.0;
}


int main(int argc, char *argv[]) {
	vector<int> nums1 = {1};
	vector<int> nums2 = {1};
	Solution solution;
	cout << "The median is " << solution.findMedianSortedArrays(nums1, nums2) << endl;
	return 0;
}

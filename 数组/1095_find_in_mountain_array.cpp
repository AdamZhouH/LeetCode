#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

class Solution {
public:
    int findInMountainArray(int target, MountainArray &mountainArr);
    int findMaxIndex(MountainArray &mountainArr);
    int searchHalfPart(MountainArray &mountainArr, int left, int right, int target, bool reverse);
};

// 先用二分查找最高点
// 然后最高点左右两侧都是有序数组，可以进一步进行二分查找，不过，是查找最小的下标
// 因此，左侧和右侧都是找第一个等于目标元素的数字

// 最大元素节点左侧第一个元素小，右侧第一个元素也是更小
int Solution::findMaxIndex(MountainArray &mountainArr) {
    int left = 0, right = mountainArr.length() - 1;
    while (left + 2 <= right) {
        int mid = left + (right - left) / 2;
        int a = mountainArr.get(mid-1), b = mountainArr.get(mid), c = mountainArr.get(mid+1);
        if (a < b && b > c)
            return mid;
        else if ( a <= b && b <= c)
            left = mid;
        else if (a >= b && b >= c)
            right = mid;
    }
    return -1; // 题目说明了给出的一定是山脉数组，因此可以这个return -1实际上不会执行到，但是函数需要返回一个int，如果不写return，编译器可能会报错
}

int Solution::searchHalfPart(MountainArray &mountainArr, int left, int right, int target, bool reverse) {
    int end = right;
    while (left <= right) {
        int mid = left + (right - left) / 2;
        int val = mountainArr.get(mid);
        if (!reverse) {
            if (target > val) left = mid + 1;
            else right = mid - 1;
        } else {
            if (target < val) left = mid + 1;
            else right = mid - 1;
        }
    }
    return right == end ? -1 : (mountainArr.get(right + 1) == target ? right + 1 : -1) ;
}


int Solution::findInMountainArray(int target, MountainArray &mountainArr) {
    int idx = findMaxIndex(mountainArr);
    int left = 0, right = mountainArr.length() - 1;
    int val = mountainArr.get(idx);
    if (target == val) return idx;
    int ans = searchHalfPart(mountainArr, left, idx - 1, target, false);
    if (ans != -1) return ans;
    return searchHalfPart(mountainArr, idx + 1, right, target, true);
}

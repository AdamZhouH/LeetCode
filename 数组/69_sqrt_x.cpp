class Solution {
public:
    int mySqrt(int x);
};

// 简单二分
// 注意防止越界，用long
int Solution::mySqrt(int x) {
    if (x == 0) return 0;
    if (x == 1) return 1;
    long left = 1, right = x;
    while (left <= right) {
        long mid = left + (right - left) / 2;
        if (mid * mid == x) return mid;
        if (mid * mid > x) right = mid - 1;
        else left = mid + 1;
    }
    return right;
}

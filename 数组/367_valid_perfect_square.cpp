class Solution {
public:
    bool isPerfectSquare(int num);
};

// 同样是非常简单的二分法
bool Solution::isPerfectSquare(int num) {
    long left = 1, right = num;
    while (left <= right) {
        long mid = left + (right - left) / 2;
        if (mid * mid == num) return true;
        else if (mid * mid > num) right = mid - 1;
        else left = mid + 1;
    }
    return false;
}

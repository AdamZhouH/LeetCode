class Solution {
public:
    bool increasingTriplet(vector<int>& nums);
};

// 更巧妙的做法，直接维护当前的两个最小值，并且是a < b，如果出现更大的，肯定有长度至少为3的子序列
class Solution2 {
public:
    bool increasingTriplet(vector<int>& nums) {
        if (nums.size() <= 2) return false;
        int a = INT_MAX, b = INT_MAX;
        for (auto val: nums) {
            if (val <= a) a = val;
            else if (val <= b) b = val;
            else return true;
        }
        return false;
    }
};

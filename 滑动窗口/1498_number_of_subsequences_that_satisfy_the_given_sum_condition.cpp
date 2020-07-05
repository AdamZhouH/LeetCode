#include <vector>
#include <algorithm>
#include <string>
using namespace std;

class Solution {
public:
    static unsigned long long MOD;
public:
    int numSubseq(vector<int>& nums, int target);
    int power(int a, int c);
};

unsigned long long Solution::MOD = 1e9+7;

int Solution::power(int a, int c) {
    if (c == 0) return 1;
    if (c == 1) return a % MOD;
    long ret = 1, base = a;
    while (c != 0) {
        if (c & 0x1) ret = (ret * base) % MOD;
        base = (base * base) % MOD;
        c = c >> 1;
    }
    return ret;
}

/******************************************************
int Solution::numSubseq(vector<int>& nums, int target) {
    sort(nums.begin(), nums.end());
    int ret = 0;
    for (int i = 0; i < nums.size(); i++) {
        int cnt = 0;
        int j = i;
        // 这里应该用二分优化，直接遍历肯定超时
        for (; j < nums.size(); j++) {
            if (nums[i] + nums[j] <= target) cnt++;
            else break;
        }
        if (cnt == 0) break;
        ret = (ret + power(2, j-i-1)) % MOD;
    }
    return ret;
}
******************************************************/
int Solution::numSubseq(vector<int>& nums, int target) {
    sort(nums.begin(), nums.end());
    int ret = 0;
    for (int i = 0; i < nums.size(); i++) {
        // 这里利用二分优化，针对每个i，找到对应的right
        int left = i, right = nums.size()-1;
        while (left <= right) {
            int mid = left + (right - left) / 2;
            int sum = nums[i]+nums[mid];
            if (sum <= target) left = mid + 1;
            else right = mid - 1;
        }
        if (right < i) break;
        ret = (ret + power(2, right-i)) % MOD; 
    }
    return ret;
}

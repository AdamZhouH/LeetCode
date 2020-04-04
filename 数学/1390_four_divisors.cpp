#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

// 返回数组中恰有四个因数的数字的各个因数之和
// 通过给出的数据大小可以直到，不超过O(n2)的时间复杂度应该可以通过测试用例
// 因此可以暴力解
class Solution {
public:
    int sumFourDivisors(vector<int>& nums);
};

int Solution::sumFourDivisors(vector<int>& nums) {
    int ret = 0;
    for (auto val : nums) {
        int curr = 0;
        int cnt = 0;
        for (int i = 2; i * i <= val; i++) {
            if (val % i == 0) {
                if (val / i == i) {
                    cnt += 2;
                    curr += val / i + i;
                } else {
                    cnt += 1;
                    curr += i;
                }
                if (cnt > 2) break;
            }
        }
        if (cnt == 2) ret += curr + 1 + val;
    }
    return ret;
}


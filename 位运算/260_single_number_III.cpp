#include <vector>
#include <numeric>
using namespace std;

class Solution {
public:
    vector<int> singleNumber(vector<int>& nums) {
        int val = accumulate(nums.begin(), nums.end(), 0, [](int a, int b) { return a ^ b; });
        // assert(val != 0);
        int flag = 0x1;
        while (!(flag & val)) flag <<= 1;
        int a = 0, b = 0;
        for (auto num : nums) {
            if (flag & num) a ^= num;
            else b ^= num;
        }
        return {a, b};
    }
};
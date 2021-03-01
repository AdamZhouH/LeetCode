#include <vector>
#include <iostream>
using namespace std;

// 前缀和思路
class NumArray {
public:
    NumArray(vector<int>& nums) {
        preSum = std::move(vector<int> (nums.size() + 1, 0));
        for (auto i = 0; i < nums.size(); i++)
            preSum[i+1] = preSum[i] + nums[i];                                     
    }
    
    int sumRange(int i, int j) {
        return preSum[j+1] - preSum[i];
    }
private:
    vector<int> preSum;
};

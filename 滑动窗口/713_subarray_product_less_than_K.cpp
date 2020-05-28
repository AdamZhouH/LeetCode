#include <iostream>
#include <vector>
#include <algorithm>
#include <numeric>
using namespace std;

class Solution {
public:
    int numSubarrayProductLessThanK(vector<int>& nums, int k);
};

// 开始时候想着前缀和，发现前缀和并没有什么用，因为前缀和求的是+相关的操作(可以不完全是+)
// 但是这题的条件是连续子数组的乘积，这里使用前缀积并不方便 
int Solution::numSubarrayProductLessThanK(vector<int>& nums, int k) {
	
	return ans;
}
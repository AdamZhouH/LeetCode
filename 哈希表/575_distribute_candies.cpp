#include <unordered_set>
#include <iostream>
#include <vector>
using namespace std;

// 基本的贪心思路，判断糖果的种类数即可
// 种类数不超过糖果总数的一半，那么最多获取所有种类的糖果
// 种类数超过了糖果总数一半，那么也只能获取最多一半的糖果

class Solution {
public:
    int distributeCandies(vector<int>& candies);
};

int Solution::distributeCandies(vector<int>& candies) {
    int total = candies.size();
    unordered_set<int> types;
    for (auto val : candies) {
        types.insert(val);
    } 
    if (types.size() >= total / 2)
        return total / 2;
    else
        return types.size();
}
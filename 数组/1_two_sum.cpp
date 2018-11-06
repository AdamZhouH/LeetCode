
#include <iostream>
#include <vector>
#include <algorithm>
#include <unordered_map>
using namespace std;

class Solution {
public:
    vector<int> twoSum(vector<int>& nums, int target);
};

vector<int> Solution::twoSum(vector<int> &nums, int target) {
    unordered_map<int, int> number;
    for (int i = 0; i < nums.size(); i++) {
        number[nums[i]] = i;
    }
    vector<int> result;
    for (int i = 0; i < nums.size(); i++) {
        int gap = target - nums[i];
        if (number.find(gap) != number.end() && number[gap] != i) {
            result.push_back(i);
            result.push_back(number[gap]); 
            break;  
        }
    }
    return result;
}

int main(void) {
    int target = 6;
    vector<int> vec = {3,2, 4};
    vector<int> result = Solution().twoSum(vec, target);
    for_each(result.begin(), result.end(), [](int var) {
        cout << var << " ";
    });
    return 0;
}
#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

class Solution {
public:
    vector<vector<int>> fourSum(vector<int>& nums, int target);
};

// 直接类似3sum做法，先排序，最里层双指针，然后前三个数字注意去除重复即可
vector<vector<int>> Solution::fourSum(vector<int> &nums, int target) {
    vector<vector<int>> ans;
    if (nums.size() < 4) return ans;
    sort(nums.begin(), nums.end());
    for (int i = 0; i < nums.size() - 3; i++) {
        if (i > 0 && nums[i] == nums[i-1]) continue;
        for (int j = i+1; j < nums.size() -2; j++) {
            if (j > i+1 && nums[j] == nums[j-1]) continue;
            for (int p = j+1, q = nums.size()-1; p < q;) {
                if (p > j+1 && nums[p] == nums[p-1]) {p++;continue;}
                int sum = nums[i] + nums[j] + nums[p] + nums[q];
                if (sum == target) ans.push_back({nums[i],nums[j],nums[p++],nums[q--]});
                else if (sum > target) q--;
                else p++;
            }
        }
    }
    return ans;
}

// 加上剪枝后，效率进一步提升
vector<vector<int>> fourSum(vector<int> &nums, int target) {
    vector<vector<int>> ans;
    if (nums.size() < 4) return ans;
    sort(nums.begin(), nums.end());
    for (int i = 0; i < nums.size() - 3; i++) {
        if (i > 0 && nums[i] == nums[i-1]) continue;
        if (nums[i] > target/4) break; // 剪枝
        for (int j = i+1; j < nums.size() -2; j++) {
            if (j > i+1 && nums[j] == nums[j-1]) continue;
            if (nums[j] > (target-nums[i])/3) break; // 剪枝
            for (int p = j+1, q = nums.size()-1; p < q;) {
                if (p > j+1 && nums[p] == nums[p-1]) {p++;continue;}
                int sum = nums[i] + nums[j] + nums[p] + nums[q];
                if (sum == target) ans.push_back({nums[i],nums[j],nums[p++],nums[q--]});
                else if (sum > target) q--;
                else p++;
            }
        }
    }
    return ans;
}

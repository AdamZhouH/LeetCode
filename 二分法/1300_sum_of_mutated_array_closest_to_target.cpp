#include <iostream>
#include <string>
#include <vector>
using namespace std;

class Solution {
public:
    // 排序+二分思路
    // 每次选择一个数字，利用二分判断其在数组中的位置，计算和，并且更新差值
    // 双重二分
    int findBestValue(vector<int>& arr, int target) {
        sort(arr.begin(), arr.end());
        vector<int> sum(arr.size(), 0);
        for (int i = 0; i < arr.size(); i++) {
            if (i == 0) sum[i] = arr[i];
            else sum[i] = arr[i] + sum[i-1];
        }
        int left = 0, right = arr.back();
        int value = INT_MAX, minabs = INT_MAX;

        while (left <= right) {
            int mid = left + (right - left) / 2;
            int pos = 0;
            int l = 0, r = arr.size() - 1, currsum = 0;
            // 这里其实可以用lower_bound不用自己手动写都行，代码更简洁，其实也是二分
            while (l <= r) {
                int m = l + (r-l)/2;
                if (arr[m] <= mid) l = m + 1;
                else r = m - 1;
            }
            if (l >= arr.size()) currsum = sum.back();
            else if (l == 0) currsum = mid * arr.size();
            else currsum = sum[l-1] + mid * (arr.size()-l);

            if (abs(currsum-target) < minabs) {
                minabs =  abs(currsum-target);
                value = mid;
            } else if (abs(currsum-target) == minabs) {
                value = min(value, mid);
            }
            if (currsum >= target) right = mid - 1;
            else left = mid + 1;

        }
        return value;
    }
};

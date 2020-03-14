#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

/**
 * 这题和之前一道的同名的题的区别是，数组中可能存在重复的元素
 * 因此当nums[left]和num[mid]相等时，无法判断旋转点(最小值点)所在的位置
 * 这种情况下，则让left往前走一步，然后继续下一次判断即可
 * 在33题的情况下，增加代码
 * 
*/

class Solution {
public:
    bool search(vector<int>& nums, int target);
};

bool Solution::search(vector<int> & nums, int target) {
    int left = 0, right = nums.size() - 1;
    int mid;
    while (left <= right) {
        mid = left + (right - left) / 2;
        if (nums[mid] == target)
            return true;
        if (nums[mid] > nums[left]) {
            if (target < nums[mid] && target >= nums[left])
                right = mid - 1;
            else
                left = mid + 1;
        } else if (nums[mid] < nums[left]) {
            if (target > nums[mid] && target <= nums[right])
                left = mid + 1;
            else
                right = mid - 1;
        } else {
            left++;
        }
    }
    return false;
}

int main(int argc, char *argv[]) {
    vector<int> vec = {2,5,6,0,0,1,2};
    for_each(vec.begin(), vec.end(), [](int i) { cout << i << ' ';} );
    cout << endl;
    int target;
    Solution solu;
    while (cin >> target) {
        cout << (solu.search(vec, target) ? "True":"False") << endl;
    }
    return 0;
}
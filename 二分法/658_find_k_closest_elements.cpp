#include <vector>
#include <iostream>
#include <algorithm>
using namespace std;

class Solution {
public:
    vector<int> findClosestElements(vector<int>& arr, int k, int x);
};

// 比较明显的二分+双指针解法
// 当然暴力将绝对值排序也行
vector<int> Solution::findClosestElements(vector<int>& arr, int k, int x) {
	vector<int> ans;
	int left = 0, right = arr.size()-1;
	int pos = 0;
	while (left <= right) {
		int mid = left + (right - left) / 2;
		if (arr[mid] == x) { pos = mid; break; }
		else if (arr[mid] > x) right = mid - 1;
		else left = mid + 1;
	}
	// 如果没有找到，可能存在x完全在数组范围之外的情况
	if (left > arr.size()-1) {
		auto ret = vector<int> (arr.rbegin(), arr.rbegin() + k);
        sort(ret.begin(), ret.end());
        return ret;
	}
	if (right < 0) {
		auto ret = vector<int> (arr.begin(), arr.begin() + k);
        sort(ret.begin(), ret.end());
        return ret;
	}
	// 设定左右指针
    int i, j;
    if (arr[pos] == x) {
	    ans.push_back(arr[pos]); 
        k--;
        i = pos-1, j = pos+1;
    } else {
        i = right, j = left;
    }
	// 遍历k个元素
	while (k--) {
		if (i >= 0 && j < arr.size()) {
			if (abs(arr[i]-x) < abs(arr[j]-x)) ans.push_back(arr[i]), i--;
			else if (abs(arr[i]-x) > abs(arr[j]-x)) ans.push_back(arr[j]), j++;
			else if (arr[i] <= arr[j]) ans.push_back(arr[i]), i--;
			else ans.push_back(arr[j]), j++;
		} else if (i < 0) {
			ans.push_back(arr[j++]);
		} else {
			ans.push_back(arr[i--]);
		}
	}
	sort(ans.begin(), ans.end());
    return ans;
}

// 直接STL暴力排序
vector<int> Solution::findClosestElements(vector<int>& arr, int k, int x) {
    sort(arr.begin(), arr.end(), [&](int a, int b) ->bool { 
        return abs(a-x) == abs(b-x) ? a < b : abs(a-x) < abs(b-x);
        });
    vector<int> ret(arr.begin(), arr.begin()+k);
    sort(ret.begin(), ret.end());
    return ret;
}
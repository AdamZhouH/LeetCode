#include <vector>
#include <iostream>
#include <string>
using namespace std;

// 暴力算法，直接开辟O(n)的复杂空间，然后用双指针归并有序数组即可
class Solution {
public:
    void merge(vector<int>& nums1, int m, vector<int>& nums2, int n) {
        if (nums2.empty()) return;
        vector<int> help;
        int i = 0, j = 0;
        while (i < m && j < n) {
            if (nums1[i] < nums2[j]) {
                help.push_back(nums1[i++]);
            } else {
                help.push_back(nums2[j++]);
            }
        }
        while (i < m) help.push_back(nums1[i++]);
        while (j < n) help.push_back(nums2[j++]);
        nums1.swap(help);
        return;
    }
};

// 考虑空间复杂度为0的算法，前面的算法从前往后，需要开辟空间，但如果从后往前，就可以无需额外空间了
void merge(vector<int>& nums1, int m, vector<int>& nums2, int n) {
    if (nums2.empty()) return;
    int i = m - 1, j = n - 1, k = m + n - 1;
    while (i >= 0 && j >= 0) {
        if (nums1[i] > nums2[j]) {
            nums1[k--] = nums1[i--];
        } else {
            nums1[k--] = nums2[j--];
        }
    }
    while (i >= 0) nums1[k--] = nums1[i--];
    while (j >= 0) nums1[k--] = nums2[j--];
    return;
}
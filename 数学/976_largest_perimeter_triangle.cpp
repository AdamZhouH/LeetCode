#include <iostream>
#include <vector>
#include <cmath>
#include <algorithm>
using namespace std;

// 思路
// 满足三角形三遍的条件：任意两边之和大于第三边，任意两边之差的绝对值小于第三边
// 贪心算法，尽量找最长的三条边，然后判断是否满足三角形边长条件，不满足则下一组
// 考虑先将变长数组排序，然后从最长的三条边开始选择，满足条件则直接返回
// 否则从次最长的三条边，直到找到满足条件的三边或者遍历完全部边但没有找到满足条件的三角形
// 利用数学知识可以分析到，在已经排序边长的情况下，当前选择的三条边如果不满足，则可以以当前
// 次长的边作为下一轮的最长边，这样的贪心思路可以保证算法的正确性
class Solution {
public:
    int largestPerimeter(vector<int>& A);
};

int Solution::largestPerimeter(vector<int> &A) {
    if (A.size() < 3) return 0;
    sort(A.begin(), A.end());
    int idx = A.size() - 3;
    while (idx >= 0) {
        int a = A[idx + 2], b = A[idx + 1], c = A[idx];
        if (b + c > a && a - c < b) return a + b + c;
        else idx--;
    }
    return 0;
}

int main(int argc, char *argv[]) {
    Solution solu;
    vector<int> arr = {3,3,6,2,55,44,21,75};
    cout << solu.largestPerimeter(arr) << endl;
    return 0;
}
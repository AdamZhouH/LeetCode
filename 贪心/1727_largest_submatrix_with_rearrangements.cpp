#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <map>
#include <set>
#include <list>
#include <unordered_map>
#include <unordered_set>
using namespace std;

// 和85.最大矩形的核心思想一样，矩形的面积考虑长和宽
// 由于长和宽（高度）都是不固定的，因此这里不能直接考虑，需要尽可能固定住一边的位置
// 考虑以矩阵的某行为底，该行上的某个高度（连续1的个数）为高度，计算一个矩形的面积
// 遍历以每一行为底的最大矩形面积，得到整个的最大矩形面积
// 
// 预处理数组，其实用的是动态规划的思想，计算matrix[i][j]上方的连续1的个数存储在height[i][j]
// 对每一行按照height[i][j]对行内元素升序排列，从第一个非0的height[i][j]开始计算
// 显然，该行内[i][j]之后的元素的高度至少>height[i][j]，因此在往后遍历时，矩形的长是在增加的，但是高度必须取最小值
// 因此造成矩形的面积不一定一直在增加，遍历该行元素时候取最大值即可
class Solution {
public:
    int largestSubmatrix(vector<vector<int>>& matrix);
};

int Solution::largestSubmatrix(vector<vector<int>> &matrix) {
    int m = matrix.size(), n = matrix[0].size();
    vector<vector<int>> height(m, vector<int>(n, 0));
    for (int j = 0; j < n; j++) height[0][j] = matrix[0][j] == 1;
    for (int i = 1; i < m; i++) {
        for (int j = 0; j < n; j++) { 
            height[i][j] = matrix[i][j] == 1 ? height[i-1][j] + 1: 0; 
        }
    }
    // 遍历每行，找到以每行为矩形底的最大矩形面积，从而获取整体的最大面积
    int maxArea = 0;
    for (int i = 0; i < m; i++) {
        int currMaxArea = 0;
        int maxHeight = INT_MAX;
        sort(height[i].begin(), height[i].end());
        for (int j = n - 1; j >= 0; j--) {
            maxHeight = min(maxHeight, height[i][j]);
            currMaxArea = max(currMaxArea, maxHeight * (n-j));
        }
        maxArea = max(maxArea, currMaxArea);
    }
    return maxArea;
}
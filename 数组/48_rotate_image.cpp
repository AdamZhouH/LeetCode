#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

class Solution {
public:
	void rotate(vector<vector<int>> &matrix);
};

// 通过观察可知，原来矩阵的元素A[i][j]在新的矩阵中为A[j][n-i+1]
// 其中n为矩阵的行数
// 可知，联想到A[j][i]为矩阵的转置
// 而A[j][n - i]只需要把第j行的元素逆序一下即可
// 因此in-place变换分两步：先转置，然后行内元素逆序即可
void Solution::rotate(vector<vector<int>> &matrix) {
	int n = matrix.size();
	for (int i = 0; i < n; i++) {
		for (int j = i; j < n; j++) {
			int temp = matrix[i][j];
			matrix[i][j] = matrix[j][i];
			matrix[j][i] = temp;
		}
	}
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < (n / 2); j++) {
			int temp = matrix[i][j];
			matrix[i][j] = matrix[i][n - j - 1];
			matrix[i][n - j - 1] = temp;
		}
	}
}

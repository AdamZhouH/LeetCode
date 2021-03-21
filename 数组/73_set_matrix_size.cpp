#include <vector>
#include <algorithm>
#include <bitset>
using namespace std;

const int kSize = 201;

class Solution {
public:
    void setZeroes(vector<vector<int>>& matrix) {
        std::bitset<kSize> row;
        std::bitset<kSize> col;
        int m = matrix.size();
        int n = matrix[0].size();
        // 先遍历，找到有0的行和列，并且记录行列到位图
        for (int i = 0; i < m; i++) {
            for (int j = 0; j < n; j++) {
                if (!matrix[i][j]) {
                    row[i] = true; col[j] = true;
                } 
            }
        }
        // 修改矩阵
        for (int i = 0; i < m; i++) {
            for (int j = 0; j < n; j++) {
                if (matrix[i][j] && (row[i] || col[j])) {
                    matrix[i][j] = 0;
                }
            }
        }
    }
};
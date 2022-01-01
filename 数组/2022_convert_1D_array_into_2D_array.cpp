#include <vector>
using namespace std;

// 没啥好说的，热身题，仔细一点
// 注意一维坐标和二维坐标的转换
class Solution {
public:
    vector<vector<int>> construct2DArray(vector<int>& original, int m, int n) {
        if (m * n != original.size()) return {};
        vector<vector<int>> ret(m, vector<int> (n, 0));
        for (int i = 0, j = 0; i < m && j < n;) {
            ret[i][j] = original[i*n + j];
            j++;
            if (j % n == 0) i++, j = 0;
        }
        return ret;
    }
};

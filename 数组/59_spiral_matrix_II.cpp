#include <vector>
#include <string>
#include <algorithm>
using namespace std;

class Solution {
public:
    vector<vector<int>> generateMatrix(int n) {
        // 直接按照螺旋矩阵I的思路，从外到内按照层次处理
        vector<vector<int>> ret(n, vector<int> (n, 0));
        int num = 1;
        int i = 0, j = 0;
        while (i <= n-i-1 && j <= n-j-1) {
            for (int k = j; k <= n-j-1; k++) 
                ret[i][k] = num++;
            for (int k = i+1; k <= n-i-1; k++) 
                ret[k][n-j-1] = num++;
            for (int k = n-j-2; k >= j && n-i-1 > i; k--)
                ret[n-i-1][k] = num++;
            for (int k = n-i-2; k > i && j < n-j-1; k--)
                ret[k][j] = num++;
            i++, j++;
        }
        return ret;
    }
};

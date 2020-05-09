#include <string>
#include <vector>
#include <algorithm>
using namespace std;

class Solution {
public:
    int orderOfLargestPlusSign(int N, vector<vector<int>>& mines);
};

// 暴力或者dp都可以
// 先给出dp做法
// 从两个方向左上->右下以及右下->左上
// 收集每个节点的上下左右四个方向的连续的1的个数（当然必须是本身为1的情况下才可能作为一个轴心点）

int Solution::orderOfLargestPlusSign(int N, vector<vector<int>>& mines) {
    if (N <= 0) return 0;
    if (mines.size() == 0 || mines[0].size() == 0) return N%2?N/2+1:N/2;
    // 填充matrix数组
    vector<vector<int>> matrix(N, vector<int>(N, 1));
    for (int i = 0; i < mines.size(); i++) {
        matrix[mines[i][0]][mines[i][1]] = 0;
    }
    // dp1 dp2 dp3 dp4 分别表示左 上 右 下
    vector<vector<int>> dp1(N, vector<int>(N, 0));
    auto dp2 = dp1, dp3 = dp1, dp4 = dp1;
    // 分别从两个方向遍历，填充dp1和dp2数组
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            if (matrix[i][j] == 1) {
                dp1[i][j] = (j >= 1 && matrix[i][j-1] == 1) ? dp1[i][j-1] + 1 : 0;
                dp2[i][j] = (i >= 1 && matrix[i-1][j] == 1) ? dp2[i-1][j] + 1 : 0;
            }
        }
    }
    int ans = 0;
    for (int i = N - 1; i >= 0; i--) {
        for (int j = N - 1; j >= 0; j--) {
            if (matrix[i][j] == 1) {
                dp3[i][j] = (j < N-1 && matrix[i][j+1] == 1) ? dp3[i][j+1] + 1 : 0;
                dp4[i][j] = (i < N-1 && matrix[i+1][j] == 1) ? dp4[i+1][j] + 1 : 0;
                ans = max(ans, 1 + min({dp1[i][j], dp2[i][j], dp3[i][j], dp4[i][j]}));
            }
        }
    }
   
    return ans;
}

#include <vector>
#include <string>
#include <algorithm>
using namespace std;

// 这题可以用动态规划的思路来写
// A[i]+A[j]+i-j = A[i]+i + A[j]-j
// 固定j，发现求A[i]+i的最大值即可，并且i<j，因此用一个辅助变量记录当前最大A[i]+i即可
class Solution {
public:
    int maxScoreSightseeingPair(vector<int>& A) {
        if (A.size() <= 1) return 0;
        int ans = A[1] + A[0] - 1;
        int currmax = A[0];
        for (int i = 2; i < A.size(); i++) {
            currmax = max(currmax, A[i-1] + i-1);
            ans = max(ans, A[i]-i + currmax);
        }
        return ans;
    }
};

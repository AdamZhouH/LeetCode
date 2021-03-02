#include <vector>
using namespace std;

// 水题啦，放松下
class Solution {
public:
    int findMaxConsecutiveOnes(vector<int>& nums) {
        int cnt = 0, cntMax = 0;
        for (auto i = 0; i < nums.size(); i++) {
            if (nums[i] == 1) {
                cnt++;
            } else {
                cntMax = max(cntMax, cnt);
                cnt = 0;
            }
        }
        return max(cnt, cntMax);
    }
};

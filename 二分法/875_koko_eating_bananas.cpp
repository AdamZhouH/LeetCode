#include <vector>
using namespace std;

class Solution {
public:
    // 稍加思考，典型二分题
    // left为1，right为piles中的最大值，然后找第一个使得总用时恰好超过H的元素
    int minEatingSpeed(vector<int>& piles, int H) {
        int ms = piles[0];
        for (auto val: piles) { if (val > ms) ms = val; }
        int left = 1, right  = ms;
        while (left <= right) {
            int mid = left + (right - left) / 2;
            int cost = 0;
            for (auto val: piles) {
                if (val <= mid) cost += 1;
                else cost += val / mid + (val % mid ? 1 : 0);
            }
            if (cost <= H) right = mid - 1;
            else left = mid + 1;
        }
        return left;
    }
};

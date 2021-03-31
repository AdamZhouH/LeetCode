#include <vector>
#include <iostream>
using namespace std;

class Solution {
public:
    // 明显的二分                                    
    int arrangeCoins(int n) {
        long left = 1, right = n;
        while (left <= right) {
            long mid = left + (right - left) / 2;
            long total = (1 + mid) * mid / 2;
            if (total <= n) left = mid + 1;
            else right = mid - 1;
        }
        return left - 1;
    }
};

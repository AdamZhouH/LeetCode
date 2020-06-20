#include <vector>
#include <algorithm>
#include <string>
using namespace std;

class Solution {
public:
    int hammingWeight(uint32_t n) {
        int ans = 0;
        while (n != 0) {
            ans += 0x1 & n;
            n >>= 1;
        }
        return ans;
    }
};

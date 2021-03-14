#include <vector>
#include <algorithm>
#include <string>
using namespace std;

// 这道题考差了什么？贪心吗？
// 这么简单还是mid？
class Solution {
public:
    int minElements(vector<int>& nums, int limit, int goal) {
        // 早就猜到你要溢出
        long diff = goal;
        for (int i = 0; i < nums.size(); i++) {
            diff -= nums[i];
        }
        diff = diff > 0 ? diff : -diff;
        return diff % limit ? diff / limit + 1 : diff / limit;
    }
};

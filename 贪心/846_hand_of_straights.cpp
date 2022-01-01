#include <vector>
#include <string>
#include <unordered_map>
using namespace std;

class Solution {
public:
    bool isNStraightHand(vector<int>& hand, int groupSize);
};

// 先排序，然后每次选择最小的那个数组
// 这里直接用unordered_map即可，注意给数组排序好
// 已经分到某个k连续数字组的数字其实会移除掉，因为unordered_map已经减1了
//
//
bool Solution::isNStraightHand(vector<int>& hand, int groupSize) {
    if (hand.size() % groupSize) return false;
    unordered_map<int, int> record;
    for (auto val: hand) record[val]++;
    sort(hand.begin(), hand.end());

    for (int i = 0; i < hand.size(); i++) {
        if (record[hand[i]] == 0) continue;
        for (int k = 0; k < groupSize; k++) {
            if (--record[hand[i] + k] < 0) return false;
        }
    }

    return true;
}

#include <vector>
#include <unordered_map>
using namespace std;

class Solution {
public:
    // 贪心+哈希表计数
    // 看起来像是一个找规律题
    // 利用hash表记录相同出现数字的个数
    // 贪心告诉我们尽可能让这些相同数字的都是一种颜色的兔子，但是有时候情况不完全理想
    // 因为极端情况下，如果一种颜色的兔子有m只，那么数组中最多出现m个m-1
    // 现在出现次数若超过m，则其中一定有其他颜色的兔子
    // 同时注意，answer[i] == 0，这种情况说明只有一只，直接累加
    int numRabbits(vector<int>& answers) {
        unordered_map<int, int> cnt;
        int ret = 0;
        for (auto val: answers) 
            if (val) cnt[val]++;
            else ret++;
        for (auto &p: cnt) {
            //if (p.second <= p.first + 1) ret += p.first + 1;
            /*else*/ret += (p.second % (p.first+1) ? (p.second/(p.first+1)) + 1: (p.second/(p.first+1))) * (p.first+1);
        }
        return ret;
    }
};
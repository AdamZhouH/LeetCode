#include <string>
#include <vector>
using namespace std;

// 利用贪心思路和滑动窗口比较好想到，但是实际上最好的做法是涉及到了竞赛相关的知识(树状数组)
// 贪心的思路，很简单，在k次移动范围内（大小为k+1的滑动窗口中）找到最小的值，然后和当前最左边idx处交换
// 这样就能得到一个尽可能小的值，然后再重复上述迭代过程，找到可以和idx+1处的位置交换的最小值
// 注意k的使用次数是由于在交换过程中使用，因此在减少
// 还一个是最开始的剪枝
// 如果k足够大，那么一定可以得到最小值（实际上一个冒泡排序的过程）
class Solution {
public:
    void swap(string &num, int i, int j) { char tmp = num[i]; num[i] = num[j]; num[j] = tmp; }
    
    string minInteger(string num, int k) {
        if (num.size() * num.size() < 2 * k) {
            sort(num.begin(), num.end());
            return num;
        }
        for (int i = 0; i < num.size() && k > 0; i++) {
            int idx = i;
            for (int j = i + 1; j < num.size() && j <= k + i; j++) {
                if (num[j] < num[idx]) idx = j;
            }
            k = k - (idx - i);
            char tmp = num[idx];
            for (int k = idx - 1; k >= i; k--) num[k+1] = num[k];
            num[i] = tmp;
        }
        return num;
    }
};

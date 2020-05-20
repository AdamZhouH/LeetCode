#include <vector>
#include <unordered_map>
#include <unordered_set>
#include <algorithm>
#include <numeric>
using namespace std;

class Solution {
public:
    int singleNumber(vector<int>& nums); 
};

// 最简单的方法就是利用hash计数，从而得到出现一次的数据
// 或者利用set去重，然后得到所有不重复元素的和，再用这个和的3倍数-原数组的和
// 得到目标数的2倍
int singleNumber(vector<int>& nums) {
    unordered_set<int> record(nums.begin(), nums.end());
    long sum1 = accumulate(record.begin(), record.end(), static_cast<long> (0));
    long sum2 = accumulate(nums.begin(), nums.end(), static_cast<long> (0));
    return (3*sum1 - sum2) / 2;
}

// 比较巧妙的方式则是利用位运算，只需要O(1)的空间复杂度和O(n)事件复杂度就可以完成
// 找到单独出现的一个数字
// 首先可以这样考虑，嫁入一个数组中的除了某个元素单独出现一次以外，其他所有元素都出现2次
// 求这个单独的元素，很显然可以用异或的方法找到这个单独的元素
// 但是这个只是表象，更深次的原因在于，异或能够完成状态从0-1-0的自动转换
// 将一个数展开为二进制，那么这个数的某些二进制位为1，某些为0
// 假如这个数出现了k次，那么，这些位肯定也出现了k次
// 现在回到刚才找单独数字的问题，其他数出现了3次，而某个数只出现了一次
// 那么，（假如整数类型32位）统计从0到31位上，所有数字的在某个位上的1出现的次数
// 要么为3k次，要么为3K+1次，如果为后者，说明单独的那个数在这一位上也是1
// 当然可以针对每一位，然后每个数字挨个统计，但是也可以同时统计，但是一个数出现可能有三种状态，即出现1次或者2次或3次
// 显然用一个bit不能表示出3个状态，故用两个bit组合来表示
// 选定00表示出现0次，01表示1次，10表示2次，当出现三次时，按照题目和解题的要求，应该回到00状态
// 然后明确转换的规则，如果下一个数在这一位为1，则00->01 01->10 10->00
// 如果下一个数在这一位为0，则状态不发生变化
// 两个bit分别命名为a,b, 下一个数为x，则画出abx的真值表
// 通过卡诺图可以得到状态转移方程
int Solution::singleNumber(vector<int>& nums) {
    int a = 0, b = 0, tmp = 0;
    for (auto num : nums) {
        tmp = (a & ~b & ~num) | (~a & b & num);
        b = (~a & ~b & num) | (~a & b & ~num);
        a = tmp;
    }
    return b;
}

// 当然也可以按照最原始的思路，统计每一位上的出现1的次数，然后和3取余数，如果余1，则说明single数在这一位上为1
int singleNumber2(vector<int>& nums) {
        int ret = 0, count = 0;
        int flag = 0x1;
        for (int i = 0; i < 32; i++) {
            flag = 1 << i;
            count = 0;
            for (int j = 0; j < nums.size(); j++)
                if (flag & nums[j]) count++;
            ret |= (count % 3) ? flag : 0;
        }
        return ret;
    }
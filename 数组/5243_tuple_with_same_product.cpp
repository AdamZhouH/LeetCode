#include <vector>
#include <unordered_map>
using namespace std;

// 核心思路和2sum 3sum问题是类似的
// 2sum问题中，利用hash表的O(1)查找判断另一个数是否存在
// 3sum问题中，则先O(n^2)确定前两个数字，然后利用hash确定第三个数是否存在
// 4sum同理，先确定前3个，然后hash确定第四个是否存在
// 这里的a b c d四个数要求满足a*b=c*d，也即是2组乘积相同的数
// 可以用map来确定每个可能的积能有多少组pair构成
// 若有n组，则显然按照题意的组合，有n(n-1) * 4种组合（实际上就是n个数字取前两个的全排列，然后*4）
// 由于nums数组中的数字本身就不相同，因此问题也更简化了

class Solution {
public:
    int tupleSameProduct(vector<int>& nums);
};

int Solution::tupleSameProduct(vector<int> &nums) {
    if (nums.size() < 4) return 0;
    unordered_map<int, int> record;
    for (int i = 0; i < nums.size(); i++) {
        for (int j = i + 1; j < nums.size(); j++) {
            record[nums[i] * nums[j]]++;
        }
    }
    int ret = 0;
    for (const auto &p: record) {
        if (p.second > 1) ret += p.second * (p.second - 1) * 4;
    }
    return ret;
}
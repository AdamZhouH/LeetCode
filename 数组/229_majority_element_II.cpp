class Solution {
public:
    vector<int> majorityElement(vector<int>& nums);
};

// 算法要求了空间复杂度为O(1)，因此无法递归，无法哈希表
// 同时还要求时间复杂度为O(n)，意味着不可能排序了
// 还是利用投票法改进一下，求出两个最多被投票的人，同时判断它们的投票数字是否超过了n/3，如果超过则是，否则不是
// 因为如果出现超过n/3的次数的元素，那么至多只有两个

vector<int> Solution::majorityElement(vector<int>& nums) {
    vector<int> ret;
    if (nums.empty())
        return ret;
    // 摩尔投票的变形应用
    // 先选择两个人，如果投给这两个的票，不抵消，否则，都减1（抵消一次）
    int a = nums[0], b = nums[0];
    int counta = 0, countb = 0;
    for (auto num :nums) {
        if (num == a) { counta++; continue; }
        if (num == b) { countb++; continue; }
        if (counta == 0) { a = num; counta++; continue; }
        if (countb == 0) { b = num; countb++; continue; }
        counta--, countb--;
    }
    // 遍历一次，统计a和b出现的次数
    counta = 0, countb = 0;
    for (auto var: nums) {
        if (var == a) 
            counta++;
        else if (var == b)   // 可能存在a==b的情况（因为一开始的投票，初始阶段a=b=nums[0]，对于数组中所有元素相同的情况，投完所有的票，ab还是指向同一个值）
            countb++;
    }
    if (counta > nums.size() / 3) ret.push_back(a);
    if (countb > nums.size() / 3) ret.push_back(b);
    return ret;
}
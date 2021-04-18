class Solution {
public:
    // 这题容易想到的是利用滑动窗口维持一个大小为k的窗口空间
    // 那么窗口内任意两个数的下标距离的绝对值都会不超过k，则其中一个条件就满足了
    // 主要关注第二个条件
    // 每次遍历到下一个元素，首先需要将与之前窗口最左侧即将离开窗口的元素移除，维护好窗口
    // 其次，abs(nums[i]-nums[j])<=t即-t<=nums[i]-nums[j]<=t
    // 即-t+nums[j]<=nums[i]<=t+nums[j]
    // 对于nums[j]，如果能在窗口中找到nums[i]，则说明存在
    // 而如果我们维护窗口内的数字有序，那么可以用二分查找，联想到用平衡二叉搜索树来存储
    // 查找时，利用lower_bound找到第一个满足条件的nums[i],然后判断是否<=nums[j]+t即可
    // 窗口内的元素，比如用set，这样每次查找的时间复杂度为logK
    // 总体时间复杂度为nlogK，空间复杂度为k
    // 考虑到可能溢出，这里用long
    
    bool containsNearbyAlmostDuplicate(vector<int>& nums, int k, int t) {                   set<long> record;
        for (int i = 0; i < nums.size(); i++) {
            auto it = record.lower_bound((long)nums[i]-(long)t);
            if (it != record.end() && (long)*it <= ((long)nums[i] + (long)t))
                return true;
            record.insert((long)nums[i]);
            if (record.size() > k)
                record.erase(nums[i-k]);
        }
        return false;                                                                 
    }
};
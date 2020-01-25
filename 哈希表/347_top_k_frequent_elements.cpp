class Solution {
public:
    vector<int> topKFrequent(vector<int>& nums, int k);
};

// 利用哈希表存储出现的次数
// 然后根据次数进行排序
// 题目已经假定给定的k都是有意义的

vector<int> Solution::topKFrequent(vector<int>& nums, int k) {
    unordered_map<int, int> records;
    for (int i = 0; i < nums.size(); i++) {
        records[nums[i]]++;
    }
    // 进行出现次数排序
    vector<pair<int, int>> vec;
    for (auto it = records.begin(); it != records.end(); it++) {
        vec.push_back(make_pair(it->first, it->second));
    }
    sort(vec.begin(), vec.end(), [] (const pair<int, int> &lhs, 
                                     const pair<int, int> &rhs) {
        return lhs.second > rhs.second;
    });
    vector<int> ret;
    for (int i = 0; i < k; i++) {
        ret.push_back(vec[i].first);
    }
    return ret;
}
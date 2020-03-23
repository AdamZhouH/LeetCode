#include <iostream>
#include <unordered_map>
#include <vector>
#include <algorithm>
using namespace std;

// 基本方法：直接统计每个数的权重，然后排序
// 更加优化的方法，由于只需要第k大的元素
// 考虑使用堆，STL中的优先队列(这里使用大根堆)
// 或者使用快速排序思想，利用partition，在O(n)时间内找到第k大的元素

#define HEAP

class Solution {
public:
    int getKth(int lo, int hi, int k);
private:
    unordered_map<int, int> weights = {{1, 0}};
    int getWeights(int var);
};

int Solution::getWeights(int var) {
    if (weights.count(var)) return weights[var];
    int ret;
    if (var % 2) 
        ret = 1 + getWeights(3 * var + 1);   
    else
        ret = 1 + getWeights(var / 2);
    weights[var] = ret;
    return ret;
}
#ifndef HEAP
int Solution::getKth(int lo, int hi, int k) {
    // <权重,值>
    vector<pair<int,int>> vec;
    while (lo <= hi) {
        vec.push_back({getWeights(lo), lo});
        lo++;
    }
    sort(vec.begin(), vec.end(), [](const pair<int,int> &lhs, const pair<int,int> &rhs) { 
        if (lhs.first == rhs.first)
            return lhs.second < rhs.second;
        return lhs.first < rhs.first;
    });
    return vec[k-1].second;
}
#else
int Solution::getKth(int lo, int hi, int k) {
    vector<pair<int,int>> vec;
    while (lo <= hi) {
        vec.push_back({getWeights(lo), lo});
        lo++;
    }
    auto func = [](const pair<int,int> &a, const pair<int,int> &b) {
        if (a.first == b.first)
            return b.second < a.second;
        return b.first < a.first;
    };
    priority_queue<pair<int,int>, vector<pair<int,int>>, decltype(func)> q(vec.begin(), vec.end(), func);
    int ret;
    while (k--) {
        ret = q.top().second; q.pop();
    }
    return ret;
}
#endif

int main(void) {
    int lo, hi, k;
    Solution slu;
    cin >> lo >> hi >> k;
    cout << slu.getKth(lo, hi, k) << endl;
    return 0;
}


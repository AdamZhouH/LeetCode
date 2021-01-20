#include <iostream>
#include <vector>
#include <string>
#include <unordered_map>
using namespace std;

// 思路
// 需要想到的一点是：假如给定了(0,3) (3,4) 说明0、3、4处的字符可以是这三个字符的任意组合序列
// 0,3,4同属一一个连通集内，容易想到并查集
// 将字符串的所有下标根据给定的pairs分成若干并查集，并查集内的字符直接可以取按照这些字符组成的最小字典序字符串
// 然后将所有并查集组成的不同的子串最终按照原来的相对位置拼接好即可
// 
// ---并查集划分
// ---并查集内字符排序
// ---整体字符串拼接

class Solution {
public:
    string smallestStringWithSwaps(string s, vector<vector<int>>& pairs);
private:
    int Find(vector<int> &ufs, int val);
    void Union(vector<int> &ufs, int lhs, int rhs);
};

string Solution::smallestStringWithSwaps(string s, vector<vector<int>> &pairs) {
    vector<int> ufs(s.size(), 0);
    for (int i = 0; i < ufs.size(); i++) ufs[i] = i;
    for (auto &pair: pairs) Union(ufs, pair[0], pair[1]);
    // 将s中的字符按照并查集分组并组内排序
    // 每个组内需要一个游标，因为拼接最终字符串时，需要根据每个组内的游标当前所指来取字符
    unordered_map<int, string> strMap;
    unordered_map<int, int> index;
    for (int i = 0; i < s.size(); i++)  strMap[Find(ufs, i)].push_back(s[i]); 
    for(auto &pair: strMap) sort(pair.second.begin(), pair.second.end()); 
    // 拼接答案
    string ret;
    for (int i = 0; i < s.size(); i++)  ret.push_back(strMap[Find(ufs, i)][index[Find(ufs, i)]++]);
    return ret;
}

int Solution::Find(vector<int> &ufs, int val) {
    // 带路径压缩，不带路径压缩会超时（也就一行代码，带上吧）
    if (ufs[val] == val) return val;
    return ufs[val] = Find(ufs, ufs[val]);
    // return Find(ufs, ufs[val]);
}

void Solution::Union(vector<int> &ufs, int lhs, int rhs) {
    ufs[Find(ufs, lhs)] = Find(ufs, rhs);
}
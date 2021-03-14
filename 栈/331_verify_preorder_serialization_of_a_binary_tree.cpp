#include <stack>
#include <vector>
#include <string>
#include <iostream>
#include <sstream>
#include <fstream>
#include <algorithm>
using namespace std;

// 判断字符串是否是一个树的前序遍历的序列化结果（已经给定了序列化规则）
// 怎么找思路呢？
// 这道题自己想不出来，还是看了答案了，但是用栈的方式，每次遇到两个#，则将两个#和前一个字符出栈
// 并用一个#代替，这个方法还是没理解清楚
//
//
//
// 但是另一个方法，利用度来分析的思路，还是比较好理解的：素有节点的入度之和等于出度之和
// 这可以从边来考虑，每个边都存在两个树中节点作为端点，并且一个为入端，一个为出端，分别贡献了一个节点的出度和入度
// 因此，针对所有节点来说，入度和等于出度和
// 因此在遍历字符串过程中，统计出度和入度，如果遍历完字符串，两者仍然相等，那么说明这个遍历序列是合法的
// 同时，在遍历的过程中，必须考虑到，假如当前遍历到一个非空节点或者#节点（表示空节点），应该如何更新出度和入度呢？
// 显然，遇到了一个非空节点，则首先，这个节点的入度需+1（注意如果是根节点，不需要，因为没有入度），并且出度+2
// 遇到一个空节点，则入度+1，并且出度不变
// 换个角度看，出度+2，相当于提供了两个挂载点（可以被子节点消耗）
// 入度+1，相当于消耗了一个挂载点
// 在遍历过程中，应当有出度始终不小于入度，否则说明挂载点不够用了
// 综上，可以有一种算法实现
class Solution {
public:
    bool isValidSerialization(string preorder);
};

bool Solution::isValidSerialization(string preorder) {
    // 首先处理一下输入
    istringstream input(preorder);
    string word;
    vector<string> contents;
    while (getline(input, word, ',')) {
        contents.push_back(word);
    }
    int in = 0, out = 0;
    for (int i = 0; i < contents.size(); i++) {
        if (contents[i] != "#") out += 2;
        if (i != 0) in += 1;
        if (i != contents.size() - 1 && in >= out) 
            return false;                                                                 // if (i == 0) {
        //     if (contents[i] != "#")
        //         outDegree += 2;
        // } else {
        //     if (contents[i] != "#")
        //         outDegree += 2;
        //     inDegree += 1;
        // }
        // // 这里为何是i != contents.size() - 1 && inDegree >= outDegree
        // // 因为如果是合法序列，在遍历到最后一个节点时，inDegree和outDegree肯定是相等的
        // // 但是在最后一个节点遍历到之前，都必须有inDegree < outDegree
        // // 因此，如果i!=contents.size()-1&&inDegree>=outDegree则说明一定false
        // if (i != contents.size() - 1 && inDegree >= outDegree) return false;
    }
    return in == out;
}

// 第二个思路是利用递归，模拟先根遍历
// 假如是一个正确的序列，那么按照二叉树先根遍历的方式
// 序列恰好能够遍历完成（也即是遍历的元素个数=序列中节点的个数）
// 因此，在先根遍历的递归过程中，记录遍历到的元素个数

class Solution2 {
public:
    bool isValidSerialization(vector<string> &nodes, int &idx, int &cnt) {
        if (idx >= nodes.size()) return false;
        cnt++;
        if (nodes[idx] == "#") return true;
        idx++;
        auto ret = isValidSerialization(nodes, idx, cnt);
        if (!ret) return false;
        idx++;
        return isValidSerialization(nodes, idx, cnt);
    }
                                        
    bool isValidSerialization(string preorder) {
        istringstream input(preorder);
        string str;
        vector<string> nodes;
        while (getline(input, str, ',')) { nodes.push_back(str); }
        int idx = 0;
        int cnt = 0;
        return isValidSerialization(nodes, idx, cnt) && cnt == nodes.size();
    }                                   
};

#include <iostream>
#include <vector>
#include <string>
#include <queue>
#include <algorithm>
#include <stack>
#include <utility>
#include <unordered_map>
#include <unordered_set>
using namespace std;

// 方法很简单，就是代码实现需要考虑很多细节。
// 基本思路就是找一个有向图中两个节点之间的最短的所有路径。
// 这类最短路径显然用BFS可以做，但是相比前一题只需要求长度，这题需要找到所有路径，难度就大了些。
// 首先，要找路径，那么BFS过程中一定要记录节点的前驱节点，这样才能在遍历到endWord的时候，通过回溯得到完整的一条路径。需要考虑的一点是，某个节点可能存在多个前驱节点，因此，实际的最短路径可能有很多条，在BFS过程中一定不要遗漏。还有一点，在BFS过程中，已经入队的节点不能入队。
// BFS遍历到endWord时，实际上已经记录了所有到endWord的最短路径。然后用一个回溯方法组合所有合法路径即可。
class Solution {
public:
    vector<vector<string>> findLadders(string beginWord, string endWord, vector<string>& wordList);
    void getAllPath(vector<vector<string>> &ans, unordered_map<string, unordered_set<string>> &paths, const string &beginWorld, const string &currWord, vector<string> &currPath);
};

// 路径存在多条，因为每个节点的前驱节点可能不止一个，因此用set来保存某个节点的前驱节点集合
vector<vector<string>> Solution::findLadders(string beginWord, string endWord, vector<string>& wordList) {
    unordered_set<string> words(wordList.begin(), wordList.end());
    vector<vector<string>> ans;
    unordered_map<string, unordered_set<string>> paths;
    unordered_set<string> vis, prevs;
    queue<string> q;
    q.push(beginWord), prevs.insert(beginWord), vis.insert(beginWord);
    // 需要统计当前生成的所有节点以及该层之上的所有节点，前者避免重复入队，后者防止出现环结构
    while (!q.empty()) {
        if (!ans.empty()) break;
        int sz = q.size();
        unordered_set<string> next;
        while (sz--) {
            string node = q.front(); q.pop();
            if (node != endWord) {
                string tmp = node;
                for (int i = 0; i < tmp.size(); i++) {
                    char o = tmp[i];
                    for (char c = 'a'; c <= 'z'; c++) {
                        if (c == o) continue;
                        tmp[i] = c;
                        // prevs表示tmp节点的上层的所有节点，用于避免成环
                        if (!words.count(tmp) || prevs.count(tmp)) continue;
                        paths[tmp].insert(node);
                        next.insert(tmp);
                        // tmp可能之前已经入队，需要避免重复入队
                        if (!vis.count(tmp)) { vis.insert(tmp); q.push(tmp); }
                    }
                    tmp[i] = o;
                }
            } else {
                vector<string> currPath;
                getAllPath(ans, paths, beginWord, node, currPath);
            }
        }
        for (auto &s: next) prevs.insert(s);
    }
    return ans;
}

void Solution::getAllPath(vector<vector<string>> &ans, unordered_map<string, unordered_set<string>> &paths, const string &beginWord, const string &currWord, vector<string> &currPath) {
    if (currWord == beginWord) {
        currPath.push_back(currWord); 
        reverse(currPath.begin(), currPath.end());
        ans.push_back(currPath);
        reverse(currPath.begin(), currPath.end());
        currPath.pop_back();
    } else {
        currPath.push_back(currWord);
        for (auto node: paths[currWord]) {
            getAllPath(ans, paths, beginWord, node, currPath);
        }
        currPath.pop_back();
    }
}

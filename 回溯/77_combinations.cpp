#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

class Solution {
public:
    vector<vector<int>> combine(int n, int k);
	void dfs(vector<vector<int>> &ret, vector<int> &curr, int begin, int n, int k);
};

vector<vector<int>> Solution::combine(int n, int k) {
	vector<vector<int>> ret; vector<int> curr;
	dfs(ret, curr, 1, n, k);
	return ret;
}

void Solution::dfs(vector<vector<int>> &ret, vector<int> &curr, int begin, int n, int k) {
	if (k == 0) { ret.push_back(curr); return; }
    for (int i = begin; i <= n; i++) {
        curr.push_back(i);
        dfs(ret, curr, i+1, n, k-1);
        curr.pop_back();
    }
}
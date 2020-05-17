#include <iostream>
#include <vector>
#include <unordered_set>
#include <unordered_map>
#include <set>
#include <algorithm>
using namespace std;

class Solution {
public:
    vector<int> findOrder(int numCourses, vector<vector<int>>& prerequisites);
};

// 实际上是给出一个拓扑排序，如果不存在拓扑排序，则没有合理的课程安排（图中存在环结构）
// 先用BFS给出一个解法
// 统计节点的入度，每次删除入度为0的节点，并更新其他节点的入度
vector<int> Solution::findOrder(int numCourses, vector<vector<int>>& prerequisites) {
	vector<int> indegree(numCourses, 0);
	unordered_map<int, set<int>> graph;
	vector<int> path;
	for (auto &v : prerequisites) {
		indegree[v[0]]++;
		graph[v[1]].insert(v[0]);
	}
	/***************这部分改用队列做会更方便，代码更清晰一些
	while (true) {
		bool flag = false;
		for (int i = 0; i < numCourses; i++) {
			if (indegree[i] == 0) {
				flag = true;
				path.push_back(i);
				indegree[i]--;
				for (auto node : graph[i]) indegree[node]--;
			}
		}
		if (!flag) break;
	}
	****************/
	queue<int> q;
		for (int i = 0; i < numCourses; i++)
			if (indegree[i] == 0) q.push(i);
		while (!q.empty()) {
			auto node = q.front(); q.pop();
			path.push_back(node);
			indegree[node]--;
			for (auto adj: graph[node]) {
				indegree[adj]--;
				if (indegree[adj] == 0) q.push(adj);
			}
		}
	return path.size() == numCourses ? path : vector<int>();
}
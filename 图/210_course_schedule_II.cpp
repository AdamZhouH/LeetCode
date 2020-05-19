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

// 算法二
// 之前的利用是bfs遍历，并且bfs非常好写（傻瓜模版），现在用dfs遍历来判断一个有向图中是否存在环
// 首先可以想到的是类似于树的dfs遍历，针对图的dfs遍历也一样
// 遍历到某个节点，然后dfs其邻居节点，如果发现其邻居节点已经遍历过，那么则说明出现了环
// 但这个如果直接这样判断，并不准确，只有已经遍历和没有遍历这两种状态，并不能判断一定就存在环
// 针对树，这样dfs是可以的，或者仅仅针对一个联通图的遍历，这也是可以的，但是需要判断环，则两个状态并不够
// 考虑这个图 1—>2 1->3 2->4 3->4，首先这个图是不存在环的
// 从节点1开始深度遍历，依次遍历1 2 4，并将1 2 4标记为已遍历节点，递归回到1时，继续遍历节点3
// 然后发现3的邻居节点中4已经被访问过了，因此认为图中存在环，这是不正确，这种情况出现的原因在于
// 除了已经遍历和未遍历这两种状态，还应该有一种中间状态，在遍历到节点3时候，发现邻居节点4处于已经遍历的状态
// 这种情况应该是合法的，增加一种状态来表明不合法的状态
// 观察有环图1->2 1->3 3->2 2->4 2->3的dfs遍历情况
// 首先会从节点1开始，dfs到节点2， 然后dfs到节点4，然后dfs到节点3，然后dfs到节点2，虽然节点2已经被访问过
// 但是实际上是成环的，这是因为2的邻居节点的dfs还没有完成，(当前节点3是2的邻居节点4的邻居节点)函数递归还没有回溯到dfs节点2的层次
// 因此当前节点2的状态不能被标记为已经访问和未访问，而应在从2开始dfs时，就标记为访问中
// 当遇到访问中邻居的节点时，表示存在环
// 首先一个节点是未访问状态，当访问后，标记为访问中状态，当其邻居节点的dfs已经完成时，回溯到当前节点时，则将节点标记为已经访问
// 每次访问一个节点，然后查看邻居节点，如果是访问中，则说明有环，如果是为访问，则dfs，如果是已经访问，则不做任何处理
// 注意，因为我们还需要获取一个具体的拓扑排序结果
// 因此使用了一个path数组，但是每当遍历到一个节点时，不能先push进去
// 考虑到我们是从一个最开始一个未遍历的节点进行dfs的，那么这个节点dfs的结果只能是从这个节点开始能够遍历的一个联通子图结构
// 这个图的开始的节点可能并不是一个没有先前依赖的节点，并且即使有，也遍历不到，否则就成环了
// 如果直接遍历到就push，而不是回溯的时候push，就会导致拓扑排序的顺序不正确
// 因此，应该在回溯时候push，并且，此时path的节点顺序和拓扑顺序应该是完全相反的，最后reverse一下即可
class Solution2 {
public:
	typedef unordered_map<int, set<int>> Graph;
public:
	vector<int> findOrder(int numCourses, vector<vector<int>>& prerequisites);
	bool dfs(Graph &graph, vector<int> &state, vector<int> &path, int node);
};

bool Solution2::dfs(Graph &graph, vector<int> &state, vector<int> &path, int node) {
	state[node] = 1;
	for (auto adj: graph[node]) {
		if (state[adj] == 1) return false;
		if (state[adj] == 0) {
			auto ret = dfs(graph, state, path, adj);
			if (!ret) return false;
		}
	}
	state[node] = 2;
	path.push_back(node);
	return true;
}

vector<int> Solution2::findOrder(int numCourses, vector<vector<int>>& prerequisites) {
	Graph graph;
	vector<int> state(numCourses, 0);
	vector<int> path;
	for (auto &vec: prerequisites) {
		graph[vec[1]].insert(vec[0]);
	}
	bool flag = true;
	for (int i = 0; i < numCourses; i++) {
		if (!state[i]) {
			flag = dfs(graph, state, path, i);
			if (!flag) break;
		}
	}
	reverse(path.begin(), path.end());
	if (flag) return pathl;
	return {};
}

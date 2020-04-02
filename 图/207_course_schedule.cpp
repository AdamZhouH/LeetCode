class Solution {
public:
    bool canFinish(int numCourses, vector<vector<int>>& prerequisites);
};

// 利用拓扑排序，判断有向中是否存在环
// 保存每个节点的出节点的集合，方便拓扑排序
// 逐层删去入度为0的节点
bool Solution::canFinish(int numCourses, vector<vector<int>> &prerequisites) {
    vector<int> inDegree(numCourses, 0);
    vector<unordered_set<int>> toNode(numCourses);
    for (auto &vec : prerequisites) {
        inDegree[vec[0]]++;
        toNode[vec[1]].insert(vec[0]);
    }
    queue<int> q;
    for (int i = 0; i < inDegree.size(); i++) {
        if (inDegree[i] == 0) {
            q.push(i);
            inDegree[i] = -1;
        }
    }
    while (!q.empty()) {
        int cnt = q.size();
        while (cnt--) {
            int node = q.front(); q.pop();
            for (auto desNode : toNode[node]) {
                if (--inDegree[desNode] == 0) q.push(desNode);
            }
        }
    }
    for (int i = 0; i < inDegree.size(); i++)
        if (inDegree[i] > 0) return false;
    return true;
}

// 也可以利用dfs遍历每个节点，判断是否存在环
// 用一个标记来标记每个节点，为-1，表示已经被其他初始节点的dfs过程判断过，直接return一个true
// 为1表示被由当前的初始节点的dfs已经访问过，出现了环，因此直接return false
// 否则置位1，然后继续dfs所有邻接节点
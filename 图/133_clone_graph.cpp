/**
 * Definition for undirected graph.
 * struct UndirectedGraphNode {
 *     int label;
 *     vector<UndirectedGraphNode *> neighbors;
 *     UndirectedGraphNode(int x) : label(x) {};
 * };
 */

// 通过分析题目意思可知，这就是一道图的遍历题
// 可以广度或者深度优先遍历，每次遍历到一个结点，则复制这个结点到新的图中
// 注意图的BFS和树的BFS的区别，图可能重复遍历到之前已经遍历的节点，因此要判断节点是否已经遍历过
// 需要注意一点，图中允许出现环

// 本题最重要的一点是，保存原来的图的节点和新的图的节点之间的映射关系，每次遍历到一个新的节点
// 然后还要添加新图的链接关系

// 复制节点应当是很好复制的，遍历即可，关键是如何在遍历过程中把结点之间的；链接关系也保存在新图之中
// 这点在自己想的时候，没有想出来利用 map 保存映射关系，其实类似的做法之间应该遇见，还是没有能吃透，以后多看看类似
// 于是，类似的图或者树的复制，或者链表的复制，这种存在链接关系的，都可以考虑这种做法
// 而且，本题目目前给出的是BFS广度优先遍历的思路
// 也可以使用宽度优先遍历的思路，不自己单独使用队列，而使用递归的做法，对于每个节点的邻接节点，判断是否已经访问，如果访问则
// 添加链接关系，没有则先添加新节点到map，然后添加链接关系然后递归上述过程即可

// 队列中存放的应当是，已经复制到nodeMap但是没有访问遍历的节点
// 具体注释见代码

#include <iostream>
#include <vector>
#include <unordered_map>
#include <queue>
#include <algorithm>
using namespace std;

class Solution {
public:
    UndirectedGraphNode *cloneGraph(UndirectedGraphNode *node);
};

UndirectedGraphNode *Solution::cloneGraph(UndirectedGraphNode *node) {
	unordered_map<UndirectedGraphNode *, UndirectedGraphNode *> nodeMap;
	queue<UndirectedGraphNode *> notVisited;
	if (node == nullptr)
		return node;
	notVisited.push(node);
	UndirectedGraphNode *newGraph = new UndirectedGraphNode(node->label);
	nodeMap[node] = newGraph;

	while (!notVisited.empty()) {
		UndirectedGraphNode *cur = notVisited.front();
		notVisited.pop();
		// 对于每个未访问节点，创建复制节点，并把映射关系存放到map中
		// 判断邻居节点是否访问过
		for (auto p : cur->neighbors) {
		    if (nodeMap.find(p) == nodeMap.end()) {   // 邻居节点词典没有遍历到，则添加如未访问队列中待之后遍历
		    	notVisited.push(p);
		    	// 创建这个邻居节点的副本，放入映射关系，并给新图添加neighbors关系
		    	UndirectedGraphNode *newNode = new UndirectedGraphNode(p->label);
		    	nodeMap[p] = newNode;
		    	nodeMap[cur]->neighbors.push_back(newNode);
		    } else {
		    	// 否则只需要添加邻居关系给新图中的节点即可
		    	nodeMap[cur]->neighbors.push_back(nodeMap[p]);
		    }
		}
	}
	return newGraph;
}


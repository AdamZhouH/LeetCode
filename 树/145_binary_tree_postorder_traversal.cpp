// 二叉树后续遍历的非递归版本
// 非递归版本的基本思路和前面的前序 中序都是一样的，遍历顺序的不同导致细节处理不同
// 比如放入遍历结果的顺序，中序是边走边放入path，前序则是，走到头再放入path
// 以上两者在进入下一次迭代时，传递的都是右儿子的指针，同时，当前的父节点也已经出栈
// 也就是说每个节点只能一次出现在栈顶的位置，这样每次从右子树进入迭代，也可以保证左子树不会重复访问
// 但是后序遍历有些不同
// 后续遍历要先遍历完成左右子树才能访问根节点
// 我们先让遍历一直往左走，直到最左端，但是，此时栈顶结点不能访问也不能出栈
// (对于先序，此时我们可以直接访问，然后，出栈，然后，进入下一次迭代之前设置为出栈节点的右边儿子，
//  对于中序，我们出栈，然后进入下次迭代之前设置当前指针为出栈节点的右儿子，和上面相似，本质上是遍历顺序的先后的不同)
// 因为当前节点虽然左儿子不存在，但是右边儿子可能存在，需要把当前指针设置为当前栈顶的右儿子
// 然后进入下一次迭代，当右子树遍历完成，返回后，先前节点(非叶子节点)又一次出现作为栈顶
// 此时如果不加判断，按照之前的逻辑，会再次遍历右子树的部分，造成死循环
// 因此，在这之上加以改进，设置一个pre指针指向前一个访问的节点，返回到下次迭代时
// 如果当前指针为空，判断
// 当一个栈顶元素，第二次出现时，我们可以直接访问，然后直接出栈这个元素
// 还有就是当一个节点左右孩子都不存在，也可以直接访问然后出栈
// 根据以上思路，我们可以给出下面的代码

// 代码量并不大，思考量比较多

#include <iostream>
#include <string>
#include <vector>
#include <stack>
using namespace std;

#ifndef NULL
#define NULL 0
#endif

struct TreeNode {
     int val;
     TreeNode *left;
     TreeNode *right;
     TreeNode(int x) : val(x), left(NULL), right(NULL) {}
 };

class Solution {
public:
	vector<int> postorderTraversal(TreeNode *root);
};

vector<int> Solution::postorderTraversal(TreeNode *root) {
	vector<int> result;
	if (root == nullptr)
		return result;
	stack<TreeNode *> path;
	TreeNode *currNode = root;
	TreeNode *preNode = nullptr;

	while (currNode || !path.empty()) {
		// 当前节点不为空，则一直往左走
		if (currNode) {
			path.push(currNode);
			currNode = currNode->left;
		} else {   // 否则，当前节点为空则判断当前栈顶的右儿子是否为空并且是否访问过
			currNode = path.top();
			// 非空并且没有访问过，则进入下一次迭代
			if (currNode->right && currNode->right != preNode)
				currNode = currNode->right;
			else {  // 否则说明右子树也迭代完毕或者并不存在，可以让当前的栈顶元素出栈，并保存preNode
				preNode = path.top();
				path.pop();
				result.push_back(preNode->val);
				// 这一步是最重要的，否则导致死循环
				// 这一步的意义在于说明栈中当前节点的右子树已经全部遍历完毕
				// 当返回到下一次迭代时，不会再去访问栈顶的左子树，而是直接栈顶继续出栈
				currNode = nullptr;
			}
		}
	}
	return result;
}

int main(void) {
	vector<int> traverPath;
	TreeNode *root = new TreeNode(1);
	TreeNode *node1 = new TreeNode(2);
	TreeNode *node2 = new TreeNode(3);

	root->right = node1;
	node1->left = node2;

	Solution solution;
	traverPath = solution.postorderTraversal(root);
	for (auto var : traverPath)
		cout << var << " ";
	cout << endl;
	return 0;
}

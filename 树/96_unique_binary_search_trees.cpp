// 这道题目涉及一个数学公式
// 但是并不妨碍我们做题，这类求种类个数的问题，首先向到的是递归，分治，动态规划
// 考虑BST树中序遍历的性质，任意一颗BST树中序遍历结果都是一系列数的有序排列，也就是1,2,3,4....
// 树的形态不同，对应着根节点的选取的不同，递归地，左右子树的根节点的选择不同
// 考虑根据一个排序数组构造一颗非空的BST，第一步，选择一个数作为根，那么根据BST性质
// 根左侧的是左子树的遍历结果，同理右侧，则以这个节点为根的BST树的数目就是  左子树BST树的个数 *  右子树BST树的个数
// 问题被分解为子问题，两个子问题递归解决
// 同理，每个数都可能作为最初的根节点，则记对于n个节点，一共存在f(n)中BST树，则
// f(n) = f(0)*f(n-1) + f(1)*f(n-2) + ... f(n-1)*f(0)
// 得到递归公式，然后动态规划转换为迭代即可
// 初始f(0)=1 

// 说明，这个f(n)其实就是卡特兰数的递归公式啦
// 对于一类问题，经过抽象转换，变为求一个满足一定条件的01序列的问题
// 比如
// 对于n个元素的出栈入栈的顺序个数，我们把入栈计为1,出为0,则一列操作就是01序列，那么合法的入栈出栈顺序，必然对应这样一个01序列
// 其中，从左到右扫描到的人一个点，都保证，其左侧的0的个数小于等于1的个数，否则就是不合法
// 再比如n对括号一共几种组合的问题，计(为0,)为1,从左到右扫描，则1的个数不能多于0的个数
// 问题抽象转换后，再利用分治和动态规划思想，先确定一个点，然后考虑剩余部分，递归的完成
// 遇到此类组合问题，要多思考本质的东西，多总结

// 详情见博客：https://blog.csdn.net/u010582082/article/details/69569237?locationNum=7&fps=1

#include <iostream>
#include <vector>
#include <string>
using namespace std;

class Solution {
public:
    int numTrees(int n);
};

int Solution::numTrees(int n) {
    vector<int> f;
    f.push_back(1);  // f(0)
    f.push_back(1);  // f(1)
    if (n == 0 || n == 1)
        return 1;
    // 迭代的计算f[n]
    for (int i = 2; i <= n; i++) {
        int sum = 0;
        for (int j = 0; j <= i - 1; j++) {
            sum += f[j] * f[i - 1 - j];
        }   
        f.push_back(sum);
    }
    return f[n];
}

int main(void) {
    Solution solu;
    int var;
    while (cin >> var) 
        cout << solu.numTrees(var) << endl;
    return 0;
}
#include <iostream>
#include <string>
#include <vector>
#include <algorithm>

using namespace std;
#ifndef UNION_FIND
class Solution {
public:
    int minIncrementForUnique(vector<int>& A) {
        if (A.size() <= 1)
            return 0;
        // 先排序，然后遍历，如果当前数字和之前的数字相同，则+1
        sort(A.begin(), A.end());
        vector<int> B; B.push_back(A[0]);
        int sumA = A[0], sumB = A[0];
        for (int i = 1; i < A.size(); i++) {
            if (A[i] <= B[i - 1])
                B.push_back(B[i-1] + 1);
            else
                B.push_back(A[i]);
            sumA += A[i];
            sumB += B[i];
        }
        return sumB-sumA;
    }
};
#else
// 利用并查集
// 并查集中的元素表示根，下标则表示元素本身
// 并查集是针对线性探测的一种优化方法
// 底层利用hashmap实现
class UnionFind {
public:
    void Union(int a, int b);
    int Find(int a);
    int help(int var);
private:
    unordered_map<int, int> data;
};

int UnionFind::Find(int a) {
    while (a != data[a]) { // 说明a不是根元素
        // 同时做路径压缩
        data[a] = data[data[a]];
        a = data[a];
    }
    // 暂时没有做路径压缩
    // 果然，没有做路径压缩就超时了，这道题必须进行路径压缩
    // 路径压缩后，通过，但是仍然效率比较低，可能是因为底层使用的是map结构，如果用数组会好很多
    
    return a;
}
void UnionFind::Union(int a, int b) {
    int roota = Find(a);
    int rootb = Find(b);
    if (roota > rootb)
        data[rootb] = roota;
    else
        data[roota] = rootb;
}

int UnionFind::help(int var) {
    // 判断元素是否存在于并查集中，如果存在则应该将var放入一个新的位置，同时更新
    // 在此位置之前的元素和之后的元素(如果存在)的并查集的根
    // 如果元素不存在，则将元素放入，并且更新左侧以及右侧的并查集(如果左侧或者右侧元素存在)
    if (data.count(var)) {
        int root = Find(var);
        int ret = root + 1 - var;
        // root+1元素一定是新放入的，之前不存在
        data[root+1] = root+1;
        Union(root, root+1);
        if (data.count(root + 2))
            Union(root+1, root+2);
        return ret;
    } else {
        data[var] = var;
        if (data.count(var - 1))
            Union(var - 1, var);
        if (data.count(var + 1))
            Union(var, var + 1);
        return 0;
    }
}

class Solution {
public:
    int minIncrementForUnique(vector<int>& A) {
        int move = 0;
        UnionFind uf;
        for (auto var : A) {
            move += uf.help(var);
        }
        return move;
    }
};
#endif
int main(void) {
	vector<int> A = {3,2,1,2,1,7};
	Solution slu;
	cout << slu.minIncrementForUnique(A) << endl;
	return 0;
}


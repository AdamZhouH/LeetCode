#include <queue>
#include <vector>
#include <algorithm>
#include <iostream>
#include <unordered_map>
using namespace std;

class Solution {
public:
    int nthUglyNumber(int n);
};

// 利用一个最小堆，可以获取当前的最小丑数，每次获取一个当前的最小丑数
// 但是注意，需要生成所有n个丑数，因此，每pop出当前最小丑数，需要push三个在当前最小丑数基础上生成的
// 3个新的丑数，同时还要注意，已经push到堆中的丑数不能重复push，因此利用一个hash判断是否此丑数之前生成过
// 当已经生成了n个丑数时，则可以不需要再生成丑数了
// 之前的有个做法，在生成n个丑数时候，循环就退出了，这样不行
// 因为生成的n个丑数并不一定是最小的n个丑数，可能后面还存在更小的丑数
// 因此，一定要pop到第n个丑数才能保证是第n小的丑数（并且此时已经生成的丑数个数应该是大于n的，这样才能筛出n个最小的丑数）
int Solution::nthUglyNumber(int n) {
    priority_queue<long, vector<long>, greater<long>> q;
    unordered_map<long, int> visited;
    q.push(1); visited[1]++;
    long ret = 0;
    for (int i = 1; i <= n; i++) {
        ret = q.top(); q.pop();
        if (visited[ret*2] == 0) { q.push(ret*2); visited[ret*2]++;}
        if (visited[ret*3] == 0) { q.push(ret*3); visited[ret*3]++;}
        if (visited[ret*5] == 0) { q.push(ret*5); visited[ret*5]++;}
    }
    return ret;
}

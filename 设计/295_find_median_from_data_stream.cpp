#include <iostream>
#include <string>
#include <map>
#include <algorithm>
#include <cassert>
#include <queue>
using namespace std;

class MedianFinder {
public:
    MedianFinder() = default;
    void addNum(int num);
    double findMedian();
private:
    map<int, int> numbers;
    int len = 0;
};

void MedianFinder::addNum(int num) {
    numbers[num]++;
    len++;
}

// 利用搜索二叉树作为存储元素的数据结构
// 从而达到快速搜索
double MedianFinder::findMedian() {
    // 先找到第n/2个元素，注意如果n为奇数，应该是第n/2+1个元素
    assert(len > 0);
    auto it = numbers.begin();
    int cnt = 0;
    int a = 0;
    int middle = len % 2 ? len / 2 + 1 : len / 2;
    for (; it != numbers.end(); it++ ) {
        cnt += it->second;
        if (cnt >= middle) {
            a = it->first;
            break;
        }
    }
    if (len % 2) return double(a);
    // 找到第n/2+1个元素
    int b = 0;
    if (cnt == len / 2) b = (++it)->first;
    else b = it->first;
    return double(a + b) / 2;
}

// 这种思路超时了，应该换一种思路
// 应该用两个堆来实现，一个存放左半边的较小元素，另一个存放右半边较大元素
// 保证两个堆的元素的个数之差不超过1，从而保证平衡，方便直接从堆顶取元素
// 左侧应该是一个大根堆，右侧的堆则是小根堆

class Solution {
public:
    Solution() = default;
    void addNum(int num);
    double findMedian();
private:
    priority_queue<int, vector<int>, less<int>> leftSide;
    priority_queue<int, vector<int>, greater<int>> rightSide;
};

// 当两个堆都为空，则元素插入左的大根堆
// 比较元素和右侧小根堆的元素的大小，如果大于则插入右侧小根堆，否则插入左侧大根堆
// 同时，元素插入导致了两个堆的元素个数差，必须保证元素个数差不超过1，因此需要调整
// 两个堆的元素个数关系，如果左侧比右侧多2个，则将左侧堆顶放入右侧，同理，如果右侧多2个，则插入堆顶到左侧
void Solution::addNum(int num) {
    /*
    if (leftSide.empty() && rightSide.empty()) {
        leftSide.push(num);
    } else if (rightSide.empty()) {
        // 此时肯定为1个元素，不能直接放入右侧堆，因为这个元素可能比前一个元素更小
        if (num > leftSide.top()) {
            rightSide.push(num);
        } else {
            rightSide.push(leftSide.top());
            leftSide.pop();
            leftSide.push(num);
        }
    } else {
        if (num > rightSide.top()) rightSide.push(num);
        else leftSide.push(num);
        // priority.size的类型必须特别注意，因为其类型是size_t，无符号类型，如果小数-大数，不会得到负数，而是一个更大的正数
        // 因此这里先求长度，转换为一个int类型，方便后面的比较
        int leftlen = leftSide.size(), rightlen = rightSide.size();
        if (rightlen - leftlen >= 2) {
            leftSide.push(rightSide.top());
            rightSide.pop();
        } 
        if (leftlen - rightlen >= 2) {
            rightSide.push(leftSide.top());
            leftSide.pop();
        }
    }
    */
    // 实际上代码可以简化，如果右侧为空，首先就插入到右侧堆，因为右侧堆放的是大元素，先放入右侧堆
    // 免去上面判断左右堆顶大小然后交换的过程
    if (rightSide.empty() || num > rightSide.top()) rightSide.push(num);
    else leftSide.push(num);
    int len1 = leftSide.size(), len2 = rightSide.size();
    if (len1 - len2 > 1) { rightSide.push(leftSide.top()); leftSide.pop(); }
    if (len2 - len1 > 1) { leftSide.push(rightSide.top()); rightSide.pop(); }
} 

double Solution::findMedian() {
    if (leftSide.size() != rightSide.size())
        return leftSide.size() > rightSide.size() ? double(leftSide.top()) : double(rightSide.top());
    return double(leftSide.top() + rightSide.top()) / 2.0; 
} 

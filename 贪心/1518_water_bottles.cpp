#include <vector>
#include <algorithm>
using namespace std;

class Solution {
public:
    int numWaterBottles(int numBottles, int numExchange);
    int numWaterBottles(int numBottles, int numEmptyBottles, int numExchange);
};

// 最基本的思路就是模拟了
// 每次模拟喝酒，然后剩下瓶子的个数，每次统计能够喝到多少瓶酒
// 模拟可以是递归实现也可以是非递归实现

// 递归实现版本
int Solution::numWaterBottles(int numBottles, int numEmptyBottles, int numExchange) {
    if (numEmptyBottles + numBottles < numExchange) return numBottles;
    return numBottles + numWaterBottles((numBottles+numEmptyBottles)/numExchange,
                                        (numBottles+numEmptyBottles)%numExchange, 
                                        numExchange);
}

int Solution::numWaterBottles(int numBottles, int numExchange) {
    return numWaterBottles(numBottles, 0, numExchange);
}
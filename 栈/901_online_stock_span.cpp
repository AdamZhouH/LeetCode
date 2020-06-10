#include <vector>
#include <iostream>
#include <stack>
#include <utility>
using namespace std;

class StockSpanner {
public:
    StockSpanner();
    int next(int price);
private:
    stack<pair<int, int>> stk;
    int curridx;
};

// 很明显应该用单调栈来做，找到左边第一个更大的元素的下标，因此利用单调递减栈
// 由于要计算跨度，肯定要保存下标信息，同时要比较股价，因此还需要股价信息，用一个pair来保存
StockSpanner::StockSpanner() : curridx(0) { }

int StockSpanner::next(int price) {
    while (!stk.empty() && price >= stk.top().second) stk.pop();
    int ans = 0;
    if (stk.empty()) ans = curridx + 1;
    else ans = curridx - stk.top().first;
    stk.push({curridx, price});
    curridx++;
    return ans;
}

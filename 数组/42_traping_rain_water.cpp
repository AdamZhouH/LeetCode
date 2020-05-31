#include <vector>
#include <stack>
using namespace std;
// 看起来很难，实际上想明白了很简单的一道题

// 想明白一点，从一侧，往中间最高处进行遍历，如果当前的高度，比前一个最大高度大，那么这两个高度之间肯定可以存水
// 那么只要往这一侧一直遍历，每当遇到一个可以更新的最大值，就计算这两者之间的雨水，然后更新最大值，然后继续遍历，直到达到最高点
// 分别从左右两侧执行上述的操作，可以得到最终的雨水量
// 实际上从一侧往最高点遍历，每次计算时，都是因为遇到了当前的最大元素，遍历的轨迹是一个单调栈

class Solution {
public:
    int trap(vector<int>& height);
};

int Solution::trap(vector<int> &height) {
    if (height.size() <= 1) return 0;
    int ret = 0;
    int maxPos = 0, maxHeight = height[0];
    for (int i = 1; i < height.size(); i++) {
        if (height[i] >= maxHeight) {
            maxPos = i;
            maxHeight = height[i];
        }
    }
    // 分别从左侧和右侧往最大高度遍历，每当遇到一个比之前的最大元素更大或者等于的，就计算可以存水的面积
    
    int currmax = height[0];
    int currpos = 0;
    for (int i = 1; i <= maxPos; i++) {
        if (height[i] < currmax) continue;
        ret += (i-currpos-1)*currmax;
        for (int j = currpos+1; j < i; j++) ret -= height[j];
        currpos=i;
        currmax=height[i];
    }
    currmax = height.back();
    currpos = height.size()-1;
    for (int i = height.size()-2; i >=maxPos; i--) {
        if (height[i] < currmax) continue;
        ret += (currpos-i-1)*min(height[i],height[currpos]);
        for (int j = currpos-1; j > i; j--) ret -= height[j];
        currpos = i;
        currmax=height[i];
    }
    return ret;
}

// 补充单调栈解法，主要是要知道每个元素的左右两侧第一个更大的元素
// 然后可以计算他们之间的存储水的面结
int trap(vector<int>& height) {
    if (height.size() < 3) return 0;
    stack<int> stk;
    int container = 0;
    for (int i = 0; i < height.size(); i++) {
        while (!stk.empty() && height[stk.top()] <= height[i]) {
            int idx = stk.top(); stk.pop();
            if (stk.empty()) break;
            container += (min(height[stk.top()], height[i])-height[idx]) * (i-stk.top()-1);
        }
        stk.push(i);
    }
    return container;
}


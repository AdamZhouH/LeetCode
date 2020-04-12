#include <vector>
#include <iostream>
#include <stack>
using namespace std;

class Solution {
public:
    int largestRectangleArea(vector<int>& heights);
};

// 理解单调栈的作用
// 单调递增栈，元素大于栈顶，则元素入栈，元素小于栈顶，则说明当前元素是栈顶元素的右侧第一个比它小的数字
// 然后将栈顶元素出栈，如果当前元素还比栈顶元素小，那么当前元素也是新的栈顶元素的右侧第一个比它小的数字，一直出栈，直到栈顶元素更小，再将当前元素入栈
// 要计算以某条矩形为高的最大矩形面积，应该让其底部的宽度尽可能往两侧延伸
// 直到遇到左右两侧第一个比这个矩形条的高度更小的矩形条，此时的宽度就是最大宽度
// 利用单调栈来寻找每个矩形条的左右侧的第一个比它小的矩形条，从而避免暴力遍历
// 1.寻找右侧第一个比它小的，很明显，按照刚才叙述的单调递增栈的做法，可以找到每一个矩形条的右侧第一个比它小的元素
// 2.寻找左侧第一个比它小的，显然，在栈中的元素，假定栈往上增长，并且入栈保存严格递增顺序，那么stack[n-1]肯定要小于stack[n]
//   并且我们按照从左到右的扫描顺序进行元素的扫描和入栈和相关的出栈规则，那么可以保证stack[n-1]肯定是stack[n]左侧第一个更小元素
// 因此，通过一个单调栈，可以一次遍历将比它小的在左侧第一个和在右侧第一个元素都找到，从而计算矩形面积
// 对于元素相同的情况，当当前元素和栈顶元素相同时，将栈顶元素出，当前元素入，将同一个高度的矩形的右边界增加
// 注意，我们入栈的是下标，因为要计算矩形的宽度

int Solution::largestRectangleArea(vector<int>& heights) {
    if (heights.size() == 0) return 0;
    if (heights.size() == 1) return heights[0];
    stack<int> stk; 
    int maxerea = 0;
    for (int i = 0; i < heights.size(); i++) {
        while (!stk.empty() && heights[stk.top()] > heights[i]) {
            int prev = stk.top(); stk.pop();
            // 获取prev的左侧第一个和右侧第一个更小的元素的下标
            int left;
            left = stk.empty() ? -1 : stk.top();  // 为空表示左侧没有更小的元素了
            maxerea = max(maxerea, (i - left - 1) * heights[prev]);
        }
        // 如果当前栈非空并且元素和当前元素相同，则pop掉，在把当前元素下标入栈，从而扩大矩形宽度
        if (!stk.empty() && heights[stk.top()] == heights[i]) stk.pop();
        stk.push(i);
    }
    // 计算栈中剩余的一些高度的面积，这些元素保持单调递增的规律，最后一个元素肯定没有出栈，因此右边界为heights.size()
    int left, right = heights.size();
    while (!stk.empty()) {
        int prev = stk.top(); stk.pop();
        left = stk.empty() ? -1 : stk.top();
        maxerea = max(maxerea, (right - left - 1) * heights[prev]);
    }
    return maxerea;
}

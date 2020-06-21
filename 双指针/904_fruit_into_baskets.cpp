#include <vector>
#include <string>
using namespace std;

class Solution {
public:
    // 记录只包含两个元素的最长子数组
    // 显然利用滑动窗口即可
    int totalFruit(vector<int>& tree) {
        if (tree.size() <= 2) return tree.size();
        int ms = 1;
        int i = 0, j = 0;
        // a记录第一个遇到的元素，b记录第二个遇到的元素
        int a = -1, b = -1;
        while (j < tree.size()) {
            if (tree[j] == a || tree[j] == b) { j++; continue; }
            if (a == -1) { a = tree[j]; j++; continue; }
            if (b == -1) { b = tree[j]; j++; continue;}
            ms = max(ms, j - i);
            // 将i移动到合适的位置以及更新a和b
            a = tree[j-1], b = tree[j];
            i = j - 1;
            while (i >= 0 && tree[i] == a) i--;
            i++;
        }
        ms = max(ms, j-i);
        return ms;
    }
};

// 其实上述代码用map也可以，当map中的元素个数超过2时，更新最大长度，移动左指针知道map
// 中元素个数更少，否则继续移动右指针
// 注意出循环后，也还需要更新一次最大长度，避免遗漏

#include <iostream>
#include <vector>
#include <string>
using namespace std;


// 按照括号嵌套的深度分类，奇数深度放A，偶数深度放B，或者相反也可以
// 这样可以保证两者的深度都不超过原seq最大嵌套深度的一半

class Solution {
public:
    vector<int> maxDepthAfterSplit(string seq) {
        int currDepth = 0;
        vector<int> ret;
        for (int i = 0; i < seq.size(); i++) {
            if (seq[i] == '(') {
                currDepth++;
                ret.push_back(currDepth % 2);
            } else {
                ret.push_back(currDepth % 2);
                currDepth--;
            }
        }
        return ret;
    }
};

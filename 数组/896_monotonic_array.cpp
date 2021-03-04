#include <vector>
#include <string>
using namespace std;

class Solution {
public:
    bool isMonotonic(vector<int>& A) {
        // 如果既出现增也出现减，说明就不是单调数列
        bool inc = true;
        bool des = true;
        for (int i = 1; i < A.size(); i++) {
            if (A[i] > A[i-1]) des = false;
            if (A[i] < A[i-1]) inc = false;
        }
        return inc || des;
    }
};

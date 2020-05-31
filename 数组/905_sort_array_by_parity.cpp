#include <vector>
using namespace std;

class Solution {
public:
    vector<int> sortArrayByParity(vector<int>& A) {
        int left = -1;
        for (int i = 0; i < A.size(); i++) {
            if (A[i] % 2 == 0) {
                left++;
                int tmp = A[left];
                A[left] = A[i];
                A[i] = tmp;
            }
        }
        return A;
    }
};

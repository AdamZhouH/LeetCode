#include <vector>
using namespace std;

class Solution {
public:
    vector<vector<int>> flipAndInvertImage(vector<vector<int>>& A) {
        for (auto &vec: A) {
            for (int i = 0, j = vec.size() - 1; i <= j; i++, j--) {
                if (i == j) { vec[i] = 1 - vec[i]; continue;}
                if (vec[i] == vec[j]) {
                    vec[i] = vec[j] = 1 - vec[i];
                }
            }
        }
        return A;
    }
};

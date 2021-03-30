#include <vector>
using namespace std;

class Solution {
public:
//     bool searchMatrix(vector<vector<int>>& matrix, int target) {
//        
//     }
    bool searchMatrix(vector<vector<int>>& matrix, int target) {
        // bool flag = false;
        // for (int i = 0; i < matrix.size(); i++) {
        //     flag = find(matrix[i], target);
        //     if (flag) break;
        // }
        // return flag;
        
        int idx = findRow(matrix, target);
        if (idx < 0) return false;
        return find(matrix[idx], target);
    }
    
    int findRow(const vector<vector<int>>& matrix, int target) {
        int left = 0, right = matrix.size() - 1;
        while (left <= right) {
            int mid = left + (right - left) / 2;
            if (matrix[mid][0] == target) return mid;
            if (matrix[mid][0] < target) left = mid + 1;
            else right = mid - 1;
        }
        return right;
    }                                    
                                        
    bool find(const vector<int> &vec, int target) {
        int left = 0, right = vec.size() - 1;
        while (left <= right) {
            int mid = left + (right - left) / 2;
            if (vec[mid] == target) return true;
            if (vec[mid] > target) right = mid - 1;
            else left = mid + 1;
        }
        return false;
    }
};

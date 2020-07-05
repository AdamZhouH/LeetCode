#include <vector>
using namespace std;

class Solution {
public:
    bool canMakeArithmeticProgression(vector<int>& arr) {
        if (arr.size() <= 2) return true;
        sort(arr.begin(), arr.end());
        long diff = arr[1]-arr[0];
        for (int i = 2; i < arr.size(); i++) {
            if (long(arr[i]-arr[i-1]) != diff) return false;
        }
        return true;
    }
};

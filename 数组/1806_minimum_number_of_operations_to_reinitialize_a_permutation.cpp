#include <vector>
#include <iostream>
using namespace std;

class Solution {
public:
    // brute force
    int reinitializePermutation(int n) {
        if (n == 2) 
            return 1;
        vector<int> perm(n, 0);
        vector<int> arr(n, 0);
        for (int i = 0; i < n; i++) 
            perm[i] = i;
        vector<int> orig = perm;
        int cnt = 0;
        while (true) {
            for (int i = 0; i < n; i++) {
                if (i & 1) {
                    arr[i] = perm[n/2+(i-1)/2];   
                } else {
                    arr[i] = perm[i/2];
                }
            }
            perm.swap(arr);
            cnt++;
            if (perm == orig)
                break;
        }
        return cnt;
    }
    
    bool equal(const vector<int> &lhs, const vector<int> &rhs) {
        if (lhs.size() != rhs.size()) return false;
        if (lhs.empty()) return true;
        for (int i = 0; i < lhs.size(); i++) 
            if (lhs[i] != rhs[i])
                return false;
        return true;
    }
};

// tips
int reinitializePermutation(int n) {
        if (n == 2) return 1;
        int pos = 2;
        int cnt = 1;
        while (pos != 1) {
            if (pos * 2 < n) 
                pos = 2 * pos;
            else 
                pos = 2 * pos - n + 1;
            cnt++;
        }
        return cnt;
    }

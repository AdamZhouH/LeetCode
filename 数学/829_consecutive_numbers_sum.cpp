class Solution {
public:
    // 枚举思路
    // (2x+k+1)k=2N，逐个枚举k
    int consecutiveNumbersSum(int N) {
        int ans = 0;
        for (long k = 1; k*k <= 2*N; k++) {
            if (2*N % k == 0) {
                if ((2*N / k - k - 1) % 2 == 0) ans++; 
            }
        }
        return ans;
    }
};
#include <iostream>
using namespace std;

//递归以及递归转dp优化，先把递归的思路想明白就行
// 鉴于这是个数学概率题，主要是要明确这是条件概率，不能用方案统计的方法，直接统计每种情况的个数，然后相除
class Solution {
public:
    double new21Game(int N, int K, int W) {
        return dfs(0, N, K, W);
    }
    
    double dfs(int sum, int N, int K, int W) {
        if (sum >= K) return sum <= N ? 1.0 : 0.0;
        double ret = 0;
        for (int i = 1; i <= W; i++) {
            ret += 1.0/W * dfs(sum + i, N, K, W);
        }
        return ret;
    }
};


class Solution {
public:
    double new21Game(int N, int K, int W) {
        if (K == 0) return 1.0;
        vector<double> probs(K+W, 0.0);
        for (int i = K; i < K+W && i <= N; i++) probs[i] = 1.0;
        probs[K-1] = accumulate(probs.begin()+K, probs.end(), double(0)) / W;
        for (int i = K-2; i >= 0; i--)
            probs[i] = probs[i+1] + (probs[i+1] - probs[i+W+1]) / W;
        return probs[0];
    }  
};
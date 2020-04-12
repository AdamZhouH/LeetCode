#include <iostream>
#include <vector>
#include <string>
using namespace std;

class Solution {
public:
    int superEggDrop(int K, int N);
};

// 开始以为按照二分去选择，每次二分使用一个鸡蛋
// 并且缩小一半的搜索区间，只留下最后一个鸡蛋线性检测剩下的区间
// 实际上这个思路并不work，借助解题中一个大佬的例子，假设一共100楼，2个鸡蛋，如果剩余一个用来线性探测
// 最坏情况下可能要50次，但实际上，第一次用五分而不是二分，那么剩余一个用来线性探测
// 不超过20次，因此不能用二分的思路去做题
// 这题的最佳选择策略和二分是没有关系的
//
// 考虑每一层扔鸡蛋，扔下去的结果两种，碎、不碎
// 如果碎了，说明F在0~i-1之间，还需要在1~i-1即i-1层楼中搜索
// 如果没有碎，说明F在i~N之间，还需要再i+1~N层即N-i层楼中搜索
// 记dp[i][k]表示有k个鸡蛋，i层楼中确定F的具体值的最小搜索次数
// 那么，假设某次搜索在第j楼，根据上面的思路，在第j楼扔下，存在两种结果：碎、不碎
// 然后根据结果分别在j楼上面或者下面的搜索区间继续搜索F的值
// 因此可以得到递推公式
// dp[i][k] =min{ max(dp[j-1][k-1], dp[i-j][k]) + 1 | 1<=j<=i  }
// 显然，k>=1，而i为0时，表示没有任何楼层，那么dp[0][k]=0
// 当k=1，只有一个鸡蛋，只能线性搜索，dp[i][1]=i

int Solution::superEggDrop(int K, int N) {
    vector<vector<int>> dp(N + 1, vector<int>(K + 1, 0));
    // 初始化dp数组
    for (int i = 0; i <= N; i++) dp[i][1] = i;
    for (int i = 1; i <= N; i++) {
        for (int k = 2; k <= K; k++) {
            int res = INT_MAX;
            for (int j = 1; j <= i; j++) {
                res = min(res , max(dp[j-1][k-1], dp[i-j][k]) + 1);
            }
            dp[i][k] = res;
        }
    }
    return dp[N][K];
}

// min(max(dp[i-1][k-1], dp[N-i][k]))
// dp[i-1][k-1]函数单调递增，并且最小值为dp[0][k-1]为0，最大值为dp[N-1][k-1]
// dp[N-i][k]函数单调递减，并且最小值为dp[0][k]为0，最大值为dp[N-1][k]
// 上述两个函数一定在区间[1,N]内一定存在交点，但交点不一定是整数交点，如果非整数交点，则需要
// 比较交点横坐标左右两侧最近的两个值，然后取最小值，这是为什么在二分查找的过程中需要记录res的原因
// 如果整数交点一定存在，是可以不用去记录的，当相等时，直接取值即可，这里容易搞不清楚因此说明一下
int superEggDropBS(int K, int N) {
    if (K == 1) return N;
    if (N == 1) return 1;
    
    vector<vector<int>> dp(N + 1, vector<int>(K + 1, 0));
    
    // 初始化dp数组
    for (int i = 1; i <= N; i++) dp[i][1] = i;
    for (int k = 1; k <= K; k++) dp[1][k] = 1;
    
    for (int i = 2; i <= N; i++) {
        for (int k = 2; k <= K; k++) {
            /*
            int res = INT_MAX;
            for (int j = 1; j <= i; j++) {
                res = min(res, max(dp[j - 1][k - 1], dp[i - j][k]) + 1);
            }
            */
            // 这一段改用二分查找，而不从1枚举到i
            int start = 1, end = i, mid;
            int res = INT_MAX;
            // 可能存在找不到的情况，因为两者的交点一定存在，但是横坐标不一定是一个整数，因此这里的res记录必不可少
            // 在没有整数交点的情况下，res会记录到交点两侧的的横坐标对应的较小值
            // 存在整数交点的情况下，res自然就记录到了整数交点处的最小值
            while (start <= end) {
                mid = start + (end - start) / 2;
                if (dp[mid-1][k-1] == dp [i-mid][k]) {
                    res = min(res, dp[mid-1][k-1] + 1);
                    break;
                } else if (dp[mid-1][k-1] > dp[i-mid][k]) {
                    end = mid - 1;
                    res = min(res, dp[mid-1][k-1] + 1);
                } else {
                    start = mid + 1;
                    res = min(res, dp[i-mid][k] + 1);
                }
            }
            dp[i][k] = res;
        }
    }
    return dp[N][K];
}

// 动态规划的dp定义和子问题定义确定了dp递推公式，不同的角度可能有不同的dp解法
// 并且存在时间复杂度、空间复杂度上的差异
// 这种dp反正我是想不到的，题解中的大佬牛逼
// 这里给出这种的dp角度的问题求解
//
// 1、无论你在哪层楼扔鸡蛋，鸡蛋只可能摔碎或者没摔碎，碎了的话就测楼下，没碎的话就测楼上。
// 2、无论你上楼还是下楼，总的楼层数 = 楼上的楼层数 + 楼下的楼层数 + 1（当前这层楼）。
// 根据这个特点，可以写出下面的状态转移方程：
// dp[k][m] = dp[k][m - 1] + dp[k - 1][m - 1] + 1
// dp[k][m - 1] 就是楼上的楼层数，因为鸡蛋个数 k 不变，也就是鸡蛋没碎，扔鸡蛋次数 m 减一；
// dp[k - 1][m - 1] 就是楼下的楼层数，因为鸡蛋个数 k 减一，也就是鸡蛋碎了，同时扔鸡蛋次数 m 减一。
// 上述递推公式可以这样理解，一次扔鸡蛋至少能推测1层楼，剩余m-1次扔鸡蛋则分别可以推测dp[k-1][m-1]和dp[k][m-1]层楼
// dp[k-1][m-1]表示如果这次扔鸡蛋破了，那么只剩下k-1个鸡蛋和m-1次扔鸡蛋的机会可以探测到的最高楼层数
// dp[k][m-1]表示这次扔鸡蛋没有婆，还剩下k个鸡蛋和m-1次扔鸡蛋机会可以探测到的最高楼层数
// 同时还有本身扔鸡蛋的这一层楼
// 一共能够推测的楼层就是上述三者之和

int superEggDropDP2(int K, int N) {
    vector<vector<int>> dp(K+1, vector<int>(N+1, 0));
    int m = 0;
    for (; dp[K][m] < N;) {
        m++;
        for (int k = 1; k <= K; k++)
            dp[k][m] = 1 + dp[k-1][m-1] + dp[k][m-1];
    }
    return m;
}
#include <iostream>
#include <vector>
using namespace std;


// 先给出暴力做法，直接递归回溯
class Solution {
public:
    string getPermutation(int n, int k);
    void getPermutation(int idx, int &count, string &ans);
private:
    vector<int> visited;
    string curr;
    int kth;
};

// inline void swap(vector<int> &nums, int i, int j) { int tmp = nums[i]; nums[i] = nums[j]; nums[j] = tmp; }

void Solution::getPermutation(int idx, int &count, string &ans) {
    // 剪枝一下
    //if (!ans.empty()) return;
    if (idx >= visited.size()) {
        count++;
        if (count == kth) ans = curr;
        return;
    }
    for (int i = 0; i < visited.size(); i++) {
        if (!visited[i]) {
            visited[i] = 1;
            curr.push_back(i+1 + '0');
            getPermutation(idx+1, count, ans);
            curr.pop_back();
            visited[i] = 0;
        }
    }
}

string Solution::getPermutation(int n, int k) {
    visited.resize(n, 0), kth = k;
    string ans = "";
    int count = 0;
    getPermutation(0, count, ans);
    return ans;
}

// 数学做法
// 确定第一个数字之后，后续的数组组成(n-1)!个排列
// 因此，根据k每次都先确定第一个数字是哪个
// 可以写成递归或者迭代的形式

class Solution {
public:
   string getPermutation(int n, int k) {
        vector<int> factorials(n,0);
        vector<char> nums(n,'0');
        factorials[0]=1;
        nums[0]='1';
        for(int i=1;i<n;i++)
        {
            factorials[i]=factorials[i - 1] * i;
            nums[i]=(i+1)+'0';
        }
        k--;
        string res="";
        for (int i=n-1;i>=0;i--)
        {
            int idx=k/factorials[i];
            k=k-idx*factorials[i];
            res+=nums[idx];
            for(int j=idx;j<n-1;j++)
                nums[j]=nums[j+1];
        }
        return res;
    }
};


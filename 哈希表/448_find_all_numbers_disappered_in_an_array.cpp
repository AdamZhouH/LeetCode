#include <vector>
#include <string>
#include <algorithm>
#include <iostream>
using namespace std;

// 首先可以想到的是原地hash碰撞（由于元素的特殊性和数组长度的特殊性）
// 将数组当成hash表，数组中每个元素通过简单的hash函数，放到正确的位置
// 比如a[i]应该放到a[a[i]-1]的位置，如果元素已经在正确的位置，则无需其他操作
// 如果元素不在正确的位置上，那么将其放到正确位置后，被替换的位置的元素被顶出
// 重复上述操作，直到当前迭代进行不下去（即元素已经在正确的位置上）
// 算法正确性的简要说明
//     1.数组中每个元素都可以找到自己的正确的位置，已经在正确位置的元素肯定不会被其他不同的元素顶出
//     2.元素如果存在重复，那么也不会影响结果，可以自行模拟一下，如果存在重复元素，那么有个元素最终会会占用某个其他元素的位置
//       将元素均放在正确的位置后，再度遍历，便可以知道哪些元素不在数组中
// 时间复杂度说明
//     1.如果当前元素已经在正确的位置，则不发生替换
//     2.当存在一系列的迭代替换时，若干个元素会被放置到正确的位置，并且下次遇到这个元素时，不会再发生迭代的替换了
//       考虑所有元素，实际上每个元素只会被顶出一次，然后放置到正确的位置
//       因此，虽然有个while循环，但其每次迭代的while循环时间复杂度之和也还是O(n)而不是O(n^2)
//     3.综上，时间复杂度保持在O(n)
class Solution {
public:
	vector<int> findDisappearedNumbers(vector<int> &nums) {
		vector<int> missedNums;
		if (nums.size() <= 1) return missedNums;
		for (int i = 0; i < nums.size(); i++) {
			if (nums[i] == i + 1) continue;
			int val = nums[i];
			while (val != nums[val - 1]) {
				int temp = nums[val - 1];
                nums[val - 1] = val;
                val = temp;
			}
		}
		for (int i = 0; i < nums.size(); i++) 
			if (nums[i] != i + 1) missedNums.push_back(i + 1);
		return missedNums;
	}
};


// 另一种思路
// 仍然是将数组当成hash表
// 用hash表来计数，最后遍历hash表，如果当前位置已经被计数过，那么说明这个位置hash到的元素出现过
// 明确数组元素的范围是1-n
// 遍历每个元素
// 当前元素应该放置到的位置是a[i]-1
// 我们在这个位置上计数，一个好的方法该位置处的元素直接+n，那么最后遍历，如果发现某个位置的元素>n，说明出现过
// 由于遍历元素时，我们可能hash到的位置是当前位置后的位置（那个位置的元素还没遍历过）
// 那么遍历到那个位置时，元素的值可能>n，我们需要还原出刚开始的那个元素
// 很显然，+n后取余即可
vector<int> findDisappearedNumbers2(vector<int> &nums) {
    vector<int> ret;
    int n = nums.size();
    for (auto &num: nums) {
        // 不能是num % n - 1，这可能得到负数，
        int idx = (num - 1) % n;
        nums[idx] += n;
    }
    for (int i = 0; i < n; i++) {
        if (nums[i] <= n) {
            ret.push_back(i+1);
        }
    }
    return ret;
}
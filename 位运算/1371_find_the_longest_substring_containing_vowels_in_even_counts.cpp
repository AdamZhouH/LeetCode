class Solution {
public:
    int findTheLongestSubstring(string s);
};

// 思路 没有 看了题解
// 状态压缩+哈希表
int Solution::findTheLongestSubstring(string s) {
    // aeiou每个元音用一个bit一共5个bit，32种奇偶次数组合状态，比如10101可以表示aiu出现奇数次数
    // oe则出现偶数次数，每当遍历一个字符，就可以改变当前的aeiou出现的奇偶次数，也即是改变状态
    // 显然，如果两次出现了同样的状态，假设第一次出现在i处
    // 第二次出现在j处，那么i+1-j之间的字符串肯定是满足aeiou出现均为偶数次数的
    // 因为只有经历了偶数个aeiou，才能回到之前的状态，为了使得合理的字符串最长
    // 那么第一次出现此状态时，就需要记录到下标，然后下次遇到相同状态，计算最大长度
    unordered_map<int, int> stateToIndex;
    int state = 0x0;
    // 初始化，刚开始时，state的状态已经是0x00000，已经出现，因此必须记录
    stateToIndex[state] = -1; 
    // a e i o u 分别在第12345个bit，来表示出现次数的奇偶性
    int maxlen = 0;
    for (int i = 0; i < s.size(); i++) {
        if (s[i] == 'a') state ^= 0x00001;
        if (s[i] == 'e') state ^= 0x00010;
        if (s[i] == 'i') state ^= 0x00100;
        if (s[i] == 'o') state ^= 0x01000;
        if (s[i] == 'u') state ^= 0x10000;
        if (stateToIndex.count(state)) maxlen = max(maxlen, i - stateToIndex[state]);
        else stateToIndex[state] = i;
    }
    return maxlen;
}

//引用一个大佬的解题思考和总结
/**
 * 状态压缩＋哈希表。类似的题出现好几次了。 如1124。 状态压缩后，哈希表的用处是求最长的连续子串，满足子数组的和为k。 此题k为0， 1124题k为1.
 *遇到奇偶个数校验，想到XOR
 *遇到有限的参数（小于20个）表状态， 想到状态压缩 （bitmask）
 *遇到求最长的连续子串使得和为k（maximum continuous subarray(substring) with sum equal to k）想到 前缀和 加哈希表记录第一次出现某一状态的位置。
*/
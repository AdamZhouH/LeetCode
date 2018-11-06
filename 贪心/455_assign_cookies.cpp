class Solution {
public:
    int findContentChildren(vector<int>& g, vector<int>& s) {
        // 贪心思路，饼干和孩子的胃口分别排序
        sort(g.begin(), g.end());
        sort(s.begin(), s.end());
        int count = 0;
        // 双指针，i用于遍历孩子的需求，j用于遍历饼干的大小
        int i = 0, j = 0;
        while (i < g.size() && j < s.size()) {
            // 找到满足当前孩子需求的最小的一块饼干
            while (s[j] < g[i] && j < s.size()) j++;
            
            if (j < s.size()) {
                // 满足当前孩子需求，分配饼干
                count++;
                i++, j++;
            } else {
                // 不存在满足当前孩子的饼干了
                break;
            }
        }
        
        return count;
    }
};
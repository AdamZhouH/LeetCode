#include <iostream>
#include <string>
#include <stack>
using namespace std;

// Unix文件路径简化
// 需要判断和前一个路径中的字符的关系
// 和元素出栈入栈联想到一起

/**需要简化的情况
1.最后一个目录的/
2.连续的//用单个/替代
3.根目录后不能../
4.其他情况正常简化即可
*/

// 无脑暴力解法

class Solution {
public:
    string simplifyPath(string path) {
        stack<string> stk;
        int len = path.size();
        for (int i = 0; i < len;) {
            // 每次循环取//之间的字符串
            while (path[i] == '/' && i < len)
                i++;
            if (i == len)
                break;
            int j = i + 1;
            for (; j < len; j++)
                if (path[j] == '/')
                    break;
            string p = path.substr(i, j - i);
            if (p == "..") {
                // 栈为空说明当前是根目录，栈非空，则出栈一个元素表示回到上一个目录
                if (!stk.empty())
                    stk.pop();
            } else if (p != ".") {
                stk.push(p);
            }
            i = j;
        }
        // 拼接栈上存储的路径
        // 注意顺序
        if (stk.empty())
            return "/";
        string finalPath = "";
        while (!stk.empty()) {
            finalPath = "/" + stk.top() + finalPath;
            stk.pop();
        }
        return finalPath;
    }
};

// Github解题思路板块很多人讨论 /.../这种情况下的路径判断
// 实际上这种输入应该是不存在的，...在Linux中会被当成普通的文件名
// 在Github中手动输入含有此路径的测试用例，也会发现实际上Github对于这种测试用例中的...进行了屏蔽
// 因此，个人认为，这种输入情况无需考虑，如果需要考虑的话，进行进一步处理即可

// 实际这里用vector也行

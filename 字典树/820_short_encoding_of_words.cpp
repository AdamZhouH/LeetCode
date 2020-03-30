#include <string>
#include <cstring>
#include <vector>
#include <iostream>
#include <algorithm>
using namespace std;

// 观察给出的例子可知，如果一个但是属于另一个单词的后缀，则较短单词的长度便可以忽略
// 因为共同的后缀部分被重复利用
// 问题便是将字典中所有可以成为另一个单词后缀的单词找到，因为这部分的单词的长度可以忽略
// 将剩下单词的长度相加即可
// 方法：
// 1.直接查找，单词按照长度从长到短排序，然后判断当前单词是否能在结果字符集中找到，并且是结果字符
// 集合中某个单词的后缀
// 2.字典树，将字符串从后续开始遍历，然后存入字典树
// 涉及字典树的实现，字典树的查找和插入
// 最后计算字典树中字符的个数即可
class Solution {
public:
    int minimumLengthEncoding(vector<string>& words);
};
#ifndef TRIETREE
int Solution::minimumLengthEncoding(vector<string>& words) {
    string buffer;
    sort(words.begin(), words.end(), [](const string& a, const string& b) { return a.size() > b.size(); });
    int cnt = 0;
    for (auto &word : words) {
        auto pos = buffer.find(word);
        if (pos == string::npos || buffer[pos+word.size()] != '#') {
            cnt += word.size() + 1;
            buffer += word + "#";
        }
    }
    return cnt;
}
#else
// 利用字典树实现
// 每个单词从后往前插入到字典树中，便实现了共享后缀
// 最后计算每个叶子节点的路径长度之和即可，但如果需要遍历字典树也会有一定的开销
// 因此用一个map来记录每个单词的末尾节点的指针，针对每个单词末尾节点判断是否是叶子节点，从而避免遍历

class TrieNode {
public:
    char c = '\0';
    TrieNode *child[26] = {nullptr};
};

bool isLeaf(TrieNode *root) {
    for (int i = 0; i < 26; i++) {
        if (root->child[i]) return false;
    }
    return true;
}

TrieNode *insert(TrieNode *root, const string &word) {
    TrieNode *node = root;
    for (int i = 0; i < word.size(); i++) {
        if (!node->child[word[i]-'a']) 
            node->child[word[i]-'a'] = new TrieNode();
        node = node->child[word[i]-'a'];
    }
    return node;
}

int Solution::minimumLengthEncoding(vector<string>& words) {
    // 因为求的是后缀，因此将每个单词进行逆序
    for_each(words.begin(), words.end(), [](string& str){reverse(word.begin(), word.end());});
    TrieNode *root = new TrieNode();
    unordered_map<TrieNode *, int> record;
    for (int i = 0; i < words.size(); i++) {
        record[insert(root, words[i])] = i;
    }
    int ret = 0;
    for (auto &p : record) {
        if (isLeaf(p.first)) ret += words[p.second].size() + 1;
    }
    return ret;
}
#endif 

int main(void) {
    vector<string> svec = {"time", "me", "bell"};
    Solution slu;
    cout << slu.minimumLengthEncoding(svec) << endl;
    return 0;
}

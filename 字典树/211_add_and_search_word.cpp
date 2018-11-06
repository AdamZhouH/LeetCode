// 添加和搜索单词--数据结构设计题目
// 很显然，利用字典树去实现相应的数据结构会效率比较高
// 利用hash也可以，但是字符串比较的效率不高
// 题目要求支持搜索文字和搜索正则表达式字符串
// 注意，此题目不仅仅要求前缀匹配而且要完全匹配

#include <iostream>
#include <string>
using namespace std;

class WordDictionary {
    public:
        // 初始化数据结构
        WordDictionary();
        // 添加单词到数据结构中
        void addWord(string word);
        // 字符串搜索，返回bool，并且支持.字符匹配（部分正则匹配规则）
        bool search(string word);
    private:
        class TrieTreeNode {
            public:
                char var;   // 实际存在的儿子节点的个数
                size_t num; // 通过这个字符的单词格式，用于前缀匹配
                size_t wordCount;  // 以这个字符为结尾的单词的个数
                TrieTreeNode *sub[26] = { nullptr }; 
                TrieTreeNode() : var(0), num(0), wordCount(0) { }
        };
        bool dfs(TrieTreeNode *root, string word);
        TrieTreeNode *root;
};

WordDictionary::WordDictionary() {
    root = new TrieTreeNode();
}

void WordDictionary::addWord(string word) {
    TrieTreeNode *currNode = root;
    for (int i = 0; i < word.size(); i++) {
        if (currNode->sub[word[i] - 'a']) {  // 当前字符存在
            currNode = currNode->sub[word[i] - 'a'];
            currNode->num++; 
        } else {        // 当前字符并不存在，则创建新节点，并设置好父节点 var 和当前节点的num 
            TrieTreeNode *newNode = new TrieTreeNode();
            newNode->num++;
            currNode->sub[word[i] - 'a'] = newNode;
            currNode->var++;
            currNode = newNode;
        }
        if (i == word.size() - 1) {  // 判断是否是单词最后一个字符，是的话，wordCount统计数加1，然后退出循环
            currNode->wordCount++;
            break;
        }
    }
}

// 利用递归DFS写会方便点，而且利用尾递归，编译器会优化成迭代
bool WordDictionary::search(string word) {
    return dfs(root, word);
}

// DFS实现
bool WordDictionary::dfs(TrieTreeNode *root, string word) {
    if (word.empty())
        return false;
    if (word.size() == 1) {
        if (word[0] == '.') {
            bool result = false;
            for (int i = 0; i < 26; i++) 
                if (root->sub[i] && root->sub[i]->wordCount > 0)
                    return true;
            return result;
        } else if (root->sub[word[0] - 'a'] && root->sub[word[0] - 'a']->wordCount > 0)
            return true;
        return false;       
    }   // 以上是递归的基准情形，处理空字符和单独一个字符的单词的查询

    // 递归处理

    if (word[0] != '.') 
        return root->sub[word[0] - 'a'] && dfs(root->sub[word[0] - 'a'], word.substr(1));
    else {   // 如果是 .，则由于可以匹配任何一个字符，需要每个儿子节点都做一个匹配
        bool result = false;
        for (int i = 0; i < 26; i++)
            if (root->sub[i])
                result = result || dfs(root->sub[i], word.substr(1));
        return result;
    }
}

int main(void) {
    WordDictionary dictionary;
    dictionary.addWord("fuck");
    string s;
    while (cin >> s) {
        cout << dictionary.search(s) << endl;
    }
    return 0;
}

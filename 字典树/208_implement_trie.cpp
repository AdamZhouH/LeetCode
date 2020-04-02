#include <vector>
#include <string>
#include <iostream>
using namespace std;

class TrieNode {
public:
    char val;
    bool hasWord;
    TrieNode **child;
    TrieNode(): val('\0'), child(new TrieNode *[26] { nullptr }), hasWord(false) {}
    ~TrieNode() {
        for (int i = 0; i < 26; i++) {
            delete child[i];
        }
        delete [] child;
    } 
};

class Trie {
public:
    /** Initialize your data structure here. */
    Trie();
    /** Inserts a word into the trie. */
    void insert(string word);
    /** Returns if the word is in the trie. */
    bool search(string word);
    /** Returns if there is any word in the trie that starts with the given prefix. */
    bool startsWith(string prefix);
    ~Trie();
private:
    TrieNode *root;
};

Trie::Trie() : root(new TrieNode()) { }

void Trie::insert(string word) {
    // Trie树中插入字符串
    TrieNode *ptr = root;
    for (auto val : word) {
        if (ptr->child[val-'a'] == nullptr) {
            ptr->child[val-'a'] = new TrieNode();
        }
        ptr = ptr->child[val-'a'];
    }
    ptr->hasWord = true;
}

bool Trie::search(string word) {
    TrieNode *ptr = root;
    for (auto val : word) {
        if (ptr->child[val-'a'] != nullptr)
            ptr = ptr->child[val-'a'];
        else
            return false;
    }
    if (ptr->hasWord)
        return true;
    return false;
}

bool Trie::startsWith(string prefix) {
    TrieNode *ptr = root;
    for (auto val : prefix) {
        if (ptr->child[val-'a'] != nullptr)
            ptr = ptr->child[val-'a'];
        else
            return false;
    }
    return true;
}

Trie::~Trie() {
    delete root;
}

int main(int argc, char *argv[]) {
    Trie trie;
    trie.insert("hello");
    cout << trie.search("hel") << endl;
    cout << trie.startsWith("hel") << endl;
    trie.insert("fuck");
    return 0;
}

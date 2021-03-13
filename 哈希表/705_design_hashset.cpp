#include <iostream>
#include <vector>
using namespace std;

// 简单的设计题，用拉链法
class MyHashSet {
public:
    // 拉链法
    // 暂时不考虑rehash
    MyHashSet() {
        hashSet.resize(kSize);
        for (int i = 0; i < kSize; i++) {
            hashSet[i] = new Node(0);
        }
    }
    
    void add(int key) {
        Node *ret = find(key);
        if (ret) return;
        else {
            Node *newNode = new Node(key);
            int idx = key % kSize;
            newNode->next = hashSet[idx]->next;
            hashSet[idx]->next = newNode;
        }
    }
    
    void remove(int key) {
        int idx = key % kSize;
        Node *pre = hashSet[idx];
        Node *cur = pre->next;
        while (cur) {
            if (cur->key == key) {
                pre->next = cur->next;
                cur->next = nullptr;
                return;
            }
            pre = cur;
            cur = cur->next;
        }
        return;
    }
    
    bool contains(int key) {
        return find(key) != nullptr;
    }
private:
    const int kSize = 256;
    
    struct Node {
        int key;
        Node *next;
        Node(int k) : key(k), next(nullptr) { }
    };
    
    vector<Node *> hashSet;
    
    Node *find(int key) {
        int idx = key % kSize;
        Node *ptr = hashSet[idx]->next;
        while (ptr) {
            if (ptr->key == key)
                return ptr;
            ptr = ptr->next;
        }
        return nullptr;
    }
};
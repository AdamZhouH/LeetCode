#include <iostream>
#include <vector>
#include <unordered_map>
using namespace std;

struct Node {
  int val;
  Node *next;
  Node *random;
  Node(int v) : val(v), next(nullptr), random(nullptr) { }
};

class Solution {
public:
    // 感觉上类似图的克隆，关键是找到每个原始节点和现在节点的映射关系
    Node* copyRandomList(Node* head) {
        if (!head) return nullptr;
        Node *ptr = head;
        unordered_map<Node *, Node *> record;
        // 先创建节点
        while (ptr) {
            Node *newNode = new Node(ptr->val);
            record[ptr] = newNode;
            ptr = ptr->next;
        }
        // 复制链接关系
        ptr = head;
        while (ptr) {
            Node *newNode = record[ptr];
            newNode->next = record[ptr->next];
            newNode->random = record[ptr->random];
            ptr = ptr->next;
        }
        // 返回新链表头节点
        return record[head];
    }
};

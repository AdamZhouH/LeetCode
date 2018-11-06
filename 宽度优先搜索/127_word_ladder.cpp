#include <iostream>
#include <unordered_set>
#include <vector>
#include <string>
#include <queue>
using namespace std;

// 题目有诈，理解清楚题目意思
// 转换过程中的单词，意思是，包括结尾在内的，都必须出现在队列中
// 如果endWord不出现在字典中，那么肯定是没有转换序列的，即使最后仅仅差一步
// 注意和网上其他人的答案相互区别，适应不同场景

// 思考过程
// 显然，每个位置处的字符都可以变换，而且存在25中其他的变换，从'a'~'z'挨个试
// 那么按照这个步骤走下来，变换一次，得到一系列单词，变换两次，又得到一系列单词
// 如果可以得到最后的endWord，那么寻找过程中每个变换的单词就构成一个有向图
// 第一层，就是变换了一个位置的字符的单词
// 第二层，就是变换了两个字符的单词
// 以此类推
// 问题抽象为在一个无权图中，寻找到某个结点的最短路径
// 因此，考虑BFS遍历图中的结点，找到endWord则直接返回
// 而BFS遍历常用的手段就是利用队列保存每层的结点数，然后对每个队中结点，先出队，访问它，然后把它的邻接结点入队
// 直到队列为空，从而完成遍历过程
// 这里要记住的一个小trick就是，由于我们要计算层次数，在每个BFS操作之前，先保存好这一层的结点数，从而达到正确记录层数变化的目的
// 同时，注意，在变换的过程中，单词不可以重复，而且重复的话，也就不是最短路径，为了放置重复
// 我们在把一个单词从wordList放入wordQueue时，要把这个单词从wordList中删除


class Solution {
public:
	int ladderLength(string beginWord, string endWord, vector<string> &wordList) {
		unordered_set<string> wordList_(wordList.begin(), wordList.end());
		queue<string> wordQueue;
		wordQueue.push(beginWord);
		int level = 1;
		while (!wordQueue.empty()) {
			int size = wordQueue.size();
			while (size--) {
				string word = wordQueue.front();
				wordQueue.pop();
				if (word == endWord)
					return level;
				else
					bfs(word, wordList_, wordQueue);
			}
			level++;
		}
		return 0;

	}
private:
	// 根据给定的单词，把单词改变一个字符之后且存在于字典中的单词进入队列
	// 并且从原来的wordList中删除这些已经入队的单词
	void bfs(string word, unordered_set<string> &wordList, queue<string> &wordQueue) {
		int wordLength = word.size();
		for (int i = 0; i < wordLength; i++) {
			char oldLetter = word[i];
			for (char c = 'a'; c <= 'z'; c++) {
				
				word[i] = c;
				if (wordList.find(word) != wordList.end()) {
					wordQueue.push(word);
					wordList.erase(word);
				}
				
			}
			word[i] = oldLetter;
		}
	}
};

int main(void) {
	vector<string> wordSet = {"hot", "dot", "dog", "lot", "log"};
	string beginWord = "hit";
	string endWord = "cog";
	Solution solution;
	cout << solution.ladderLength(beginWord, endWord, wordSet) << endl;
	return 0;
}
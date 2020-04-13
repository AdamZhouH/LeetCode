#include <iostream>
#include <vector>
#include <unordered_set>
#include <unordered_map>
#include <queue>
#include <algorithm>
using namespace std;

/**
 * 效率比较低的解法，但是逻辑比较清楚，
 * 使用了优先队列存放推文信息，优先队列将推文按照时间倒叙排列，undered_map<int, unordered_set<int>> 存放用户和用户的关注列表，
 * unordered_map<int, priority_queue<pair<int,int>>> 存放的是每个user的推文信息，推文中包括推文id和一个时间戳id，后者用来排序 
 * 然后就是暴力操作，关注和取消关注都很简单，主要是获取推文，
 * 每次获取一个用户的推文都会先获取他关注的所有的人的各10条推文放入一个候选priority_queue中（不满10条就全部取出来），
 * 因为本题中的推文不能删除，因此获取了top推文后，还需要还原回去。大概思路就这样。
*/
struct Cmp {
    bool operator() (const pair<int,int> &lhs, const pair<int,int> &rhs) { return lhs.second < rhs.second; }
};

class Twitter {
public:
    Twitter();
    void postTweet(int userId, int tweetId);
    vector<int> getNewsFeed(int userId);
    void follow(int followerId, int followeeId);
    void unfollow(int followerId, int followeeId);
private:
    static long ID;
    void fetch10Twitter(int userId, priority_queue<pair<int,int>, vector<pair<int,int>>, Cmp> &candicate);
    void fetch10Twitter(vector<int> &result, priority_queue<pair<int,int>, vector<pair<int,int>>, Cmp> &candidate);
    unordered_map<int, unordered_set<int>> followerInfo;
    unordered_map<int, priority_queue<pair<int,int>, vector<pair<int,int>>, Cmp>> twitterInfo;
};

long Twitter::ID = 0;


Twitter::Twitter() {}

void Twitter::follow(int followerId, int followeeId) {
    // 忘记了这种骚操作，自己关注自己
    if (followerId == followeeId) return;
    followerInfo[followerId].insert(followeeId);
}

void Twitter::unfollow(int followerId, int followeeId) {
    if (followerInfo[followerId].count(followeeId))
        followerInfo[followerId].erase(followeeId);
}

void Twitter::postTweet(int userId, int tweetId) {
    twitterInfo[userId].push({tweetId, ID++});
}

void Twitter::fetch10Twitter(int userId, priority_queue<pair<int,int>, vector<pair<int,int>>, Cmp> &candidate) {
    int cnt = twitterInfo[userId].size() < 10 ? twitterInfo[userId].size(): 10;
    vector<pair<int,int>> help;
    while (cnt--) {
        auto twitterId = twitterInfo[userId].top();
        twitterInfo[userId].pop();
        help.push_back(twitterId);
        candidate.push(twitterId);
    }
    for (int i = 0; i < help.size(); i++) twitterInfo[userId].push(help[i]);
}

void Twitter::fetch10Twitter(vector<int> &result, priority_queue<pair<int,int>, vector<pair<int,int>>, Cmp> &candidate) {
    int cnt = candidate.size() < 10 ? candidate.size() : 10;
    while (cnt--) {
        result.push_back(candidate.top().first);
        candidate.pop();
    }
}

vector<int> Twitter::getNewsFeed(int userId) {
    priority_queue<pair<int,int>, vector<pair<int,int>>, Cmp> candidateMessages;
    for (auto user : followerInfo[userId]) fetch10Twitter(user, candidateMessages);
    fetch10Twitter(userId, candidateMessages);
    vector<int> ret;
    fetch10Twitter(ret, candidateMessages);
    return ret;
}
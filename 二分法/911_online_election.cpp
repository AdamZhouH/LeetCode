#include <vector>
#include <iostream>
#include <unordered_map>
using namespace std;

class TopVotedCandidate {
public:
    TopVotedCandidate(vector<int>& persons, vector<int>& times);
    int q(int t);
private:
    vector<int> result;
    vector<int> time;
};

TopVotedCandidate::TopVotedCandidate(vector<int>& persons, vector<int>& times) {
    time = times;
    result = vector<int> (time.size(), -1);
    unordered_map<int, int> record;
    int maxvote = INT_MIN, p = -1;
    for (int i = 0; i < times.size(); i++) {
        record[persons[i]]++;
        if (record[persons[i]] >= maxvote) maxvote = record[persons[i]], p = persons[i];
        result[i] = p;
    }
}

int TopVotedCandidate::q(int t) {
    // 二分查找用于找到第一个小于等于当前时间t的时间
    int left = 0, right = time.size() - 1;
    while (left <= right) {
        int mid = left + (right - left) / 2;
        if (time[mid] == t) return result[mid];
        if (time[mid] > t) right = mid - 1;
        else left = mid + 1;
    }
    return result[right];
}

int main(void) {
	vector<int> persons = {0,1,1,0,0,1,0};
	vector<int> times = {0,5,10,15,20,25,30};
	TopVotedCandidate top = TopVotedCandidate(persons, times);
	vector<int> time = {3,12,25,15,24,8};
	for (auto val : time) {
		cout << top.q(val) << ' ';
	}
	return 0;
}
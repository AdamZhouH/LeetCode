#include <string>
#include <unordered_set>
#include <sstream>
using namespace std;

class Solution {
public:
    int numDifferentIntegers(string word) {
        for (string::size_type i = 0; i < word.size(); i++) {
            if (!isdigit(word[i])) word[i] = ' ';
        }
        istringstream input(word);
        unordered_set<string> record;
        string str;
        while (input >> str) {
            auto pos = str.find_first_not_of('0');
            if (pos != string::npos) record.insert(str.substr(pos));
            else record.insert("0");
        }
        return record.size();
    }
};

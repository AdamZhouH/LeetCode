#include <vector>
using namespace std;

class Solution {
public:
    string dayOfTheWeek(int day, int month, int year) {
        vector<int> days = {31,28,31,30,31,30,31,31,30,31,30,31};
        vector<string> week = {"Friday","Saturday","Sunday","Monday","Tuesday","Wednesday","Thursday",};

        int totalDays = day;
        for (int i = 1971; i < year; i++) {
            totalDays += (i % 4 == 0 && i % 400 || i % 400 == 0) ? 366 : 365;
        }
        for (int i = 1; i < month; i++) {
            totalDays += (i != 2 ? days[i-1] : 
                                    (year % 4 == 0 && year % 100 || year % 400 == 0)? 29 : 28);
        }
        return week[(totalDays-1) % week.size()];
    }
};

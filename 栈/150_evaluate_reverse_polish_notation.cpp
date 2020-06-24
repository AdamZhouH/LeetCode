#include <vector>
#include <stack>
#include <vector>
using namespace std;

class Solution {
public:
    int evalRPN(vector<string>& tokens) {
        if (tokens.empty()) return 0;
        stack<long> stk;
        for (int i = 0; i < tokens.size(); i++) {
            if (tokens[i].size() == 1 && !(isdigit(tokens[i][0]))) {
                char op = tokens[i][0];
                //assert(stk.size() >= 2);
                int a = stk.top(); stk.pop();
                int b = stk.top(); stk.pop();
                switch (op) {
                    case '+':{
                        stk.push(b+a);
                        break;
                    }
                    case '-': {
                        stk.push(b-a);
                        break;
                    }
                    case '*': {
                        stk.push(b*a);
                        break;
                    }
                    case '/': {
                        stk.push(b/a);
                        break;
                    }
                }
            } else {
                stk.push(stol(tokens[i]));
            }

        }
        //assert(stk.size() == 1);
        return stk.top();
    }
};

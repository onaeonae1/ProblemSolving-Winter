#include <iostream>
#include <string>
#include <vector>
#include <stack>
#include <set>
using namespace std;

int main() {
    const int C_START = 97;
    const int C_NUM = 26;
    int c; cin>>c;
    string str, before;
    while (c--) {
        int n; cin>>n;
        int start;
        vector<set<int> > arr(C_NUM);
        vector<bool> visited(C_NUM, 0);
        // input init
        for (int i = 0; i < n; ++i) {
            cin >> str;
            if (i == 0) {
                start = str[0] - C_START;
                before = str;
                continue;
            }
            int strSize = before.size() < str.size() ? before.size() : str.size();
            for (int j = 0; j < strSize; ++j) {
                if (before[j] != str[j]) {
                    arr[before[j] - C_START].insert(str[j] - C_START);
                    if (str[j] - C_START == start) start = before[j] - C_START;
                    break;
                }
            }
            before = str;
        }
        //topological sort
        bool end = false;
        bool end2 = false;
        vector<char> ret;
        stack<int> stackk;
        set<int> suspect;
        stackk.push(start);
        for (int visitedNum = 0; visitedNum < C_NUM; visitedNum++) {
            visited[start] = true;
            set<int>::iterator it;
            for (it = arr[start].begin(); it != arr[start].end(); ++it) {
                int next = *it;
                if(visited[next]) {
                    suspect.insert(next);
                    continue;
                }
                stackk.push(next);
            }
            if(!stackk.empty()) start = stackk.top();
            while(visited[start]) {
                if(!suspect.empty() && suspect.end() != suspect.find(start)) {
                    ret[0] = '$';
                    end = true;
                    break;
                }
                ret.push_back( (char)(start + C_START) );
                stackk.pop();
                if(stackk.empty()) {
                    end2 = true;
                    break;
                }
                start = stackk.top();
            }
            if(end) break;
            if(end2) {
                for(int i = 0; i < C_NUM; ++i) {
                    if(!visited[i]) {
                        ret.push_back( (char)(i + C_START) );
                    }
                }
                break;
            }
        }
        if(ret[0] == '$') cout << "INVALID HYPOTHESIS" <<endl;
        else {
            for(int i = ret.size() - 1; i >= 0; --i) {
                cout << ret[i];
            }
             cout << endl;
        }
    }
}

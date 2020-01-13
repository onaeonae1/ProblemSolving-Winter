#include <iostream>
#include <vector>
#include <string>

using namespace std;

const int C_NUM = 26;

bool eulerianCircuit(vector<vector<bool> >& used, vector<vector<string> >& words, vector<int>& ret, int cur, int n) {
    if(ret.size() == n) return 1;
    int next;
    for (int i = 0; i < words[cur].size(); ++i) {
        if(!used[cur][i]) continue;
        ret.push_back(i*100 + cur);
        used[cur][i] = false;
        next = words[cur][i].back() - 'a';
        if (eulerianCircuit(used, words, ret, next, n) ) return 1;
        used[cur][i] = true;
        ret.pop_back();
    }
    return 0;
}

int main() {
    int c; cin>>c;
    while(c--) {
        //input setting
        int n; cin>>n;
        vector<vector<string> > words(C_NUM);
        vector<vector<bool> > used(C_NUM);
        vector<int> outDegree(C_NUM);
        vector<int> inDegree(C_NUM);
        string str;
        int front, back;
        for (int i = 0; i < n; ++i) {
            cin>>str;
            front = str[0] - 'a';
            back = str.back() - 'a';
            words[front].push_back(str);
            used[front].push_back(true);
            inDegree[back]++;
            outDegree[front]++;
        }
        //check IMPOSSIBLE case
        int start, end, gap;
        start = end = 0;
        bool endBool = false;
        for (int i = 0; i < C_NUM; ++i) {
            gap = inDegree[i] - outDegree[i];
            if(gap != 0) {
                // i번째 알파벳으로 시작하는 string이 여러개 있을 경우 그 중 어느 알파벳이 start가 될지 알 수 없으므로 start string을 따로 표시할 수는 없음
                if(gap == 1 && end == 0) end++;
                else if(gap == -1 && start == 0) start++;
                else {
                    endBool = true;
                    break;
                }
            }
        }
        if(endBool || start != end) {
            cout<<"IMPOSSIBLE"<<endl;
            continue;
        }
        //check eulerianCircuit
        vector<int> ret;
        if(start == 1) {
            for (int i = 0; i < C_NUM; ++i) {
                if(outDegree[i] == inDegree[i] + 1) {
                    if(eulerianCircuit(used, words, ret, i, n) ) endBool = true;
                    break;
                }
            }
        }
        else {
            for (int i = 0; i < C_NUM; ++i) {
                if(eulerianCircuit(used, words, ret, i, n) ) {
                    endBool = true;
                    break;
                }
            }
        }
        if(endBool) {
            for (int i = 0; i < ret.size(); ++i) {
                cout<<words[ret[i] % 100][ret[i] / 100]<<' ';
            }
        }
        else cout<<"IMPOSSIBLE";
        cout<<endl;
    }
}

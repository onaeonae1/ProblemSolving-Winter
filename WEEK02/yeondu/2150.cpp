#include <iostream>
#include <cstring>
#include <algorithm>
#include <utility>
#include <vector>
#include <stack>

using namespace std;

const int MAX = 10001;
bool visited[MAX];

void findSCC_1(stack<int>& s, vector<vector<int> >& g, int cur) {
    visited[cur] = true;
    int next;
    for (int i = 0; i < g[cur].size(); ++i) {
        next = g[cur][i];
        if(!visited[next]) findSCC_1(s, g, next);
    }
    s.push(cur);
}
void findSCC_2(vector<int>& ret, stack<int>& s, vector<vector<int> >& g, int cur) {
    visited[cur] = true;
    ret.push_back(cur);
    int next;
    for (int i = 0; i < g[cur].size(); ++i) {
        next = g[cur][i];
        if(!visited[next]) findSCC_2(ret, s, g, next);
    }
}

int main() {
    int V, E; cin>>V>>E;
    vector<vector<int> > graph(V+1);
    vector<vector<int> > inverseG(V+1);
    int v1, v2;
    while(E--) {
        cin>>v1>>v2;
        graph[v1].push_back(v2);
        inverseG[v2].push_back(v1);
    }
    stack<int> s;
    for (int i = 1; i <= V; ++i) {
        if( !visited[i] ) {
            findSCC_1(s, graph, i);
        }
    }
    memset(visited, 0, sizeof(visited));
    int next;
    vector<vector<int> > result;
    vector<pair<int, int> > retOrder;
    while (!s.empty()) {
        next = s.top();
        s.pop();
        vector<int> ret;
        if( !visited[next] ) {
            findSCC_2(ret, s, inverseG, next);
            sort(ret.begin(), ret.end());
            result.push_back(ret);
            retOrder.push_back(make_pair(ret[0], result.size() - 1));
        }
    }
    int retSize = retOrder.size();
    cout<<retSize<<endl;
    sort(retOrder.begin(), retOrder.end());
    for(int i = 0; i < retSize; ++i) {
        int realOrder = retOrder[i].second;
        for(int j = 0; j < result[realOrder].size(); ++j) {
            cout<<result[realOrder][j]<<' ';
        }
        cout<<-1<<endl;
    }
}

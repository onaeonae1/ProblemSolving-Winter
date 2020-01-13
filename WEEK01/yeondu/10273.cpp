#include <iostream>
#include <vector>
#include <utility>

using namespace std;

int dfs(vector<int>& ret, vector<int>& path, vector<int>& value, vector<vector<pair<int, int> > >& adj, int cur) {
    if(ret[cur] != -1) return ret[cur];
    int next, temp;
    int cnt = 0;
    ret[cur] = 0;
    for (int i = 0; i < adj[cur].size(); ++i) {
        next = adj[cur][i].first;
        temp = dfs(ret, path, value, adj, next);
        if( ret[cur] < ret[next] - adj[cur][i].second ) {
            ret[cur] = ret[next] - adj[cur][i].second;
            path[cur] = next;
            cout<<"cur: "<<cur<<", cnt: "<<cnt<<endl;
            cnt = temp;
        }
    }
    ret[cur] += value[cur];
    cnt += 1;
    return cnt;
}

int main() {
    int T; cin>>T;
    while(T--) {
        int N, E; cin>>N>>E;
        vector<int> value(N+1);
        int temp;
        for (int i = 1; i <= N; ++i) {
            cin>>temp;
            value[i] = temp;
        }
        vector<vector<pair<int, int> > > adj(N+1);
        int a, b, c;
        for (int i = 0; i < E; ++i) {
            cin>>a>>b>>c;
            adj[a].push_back(make_pair(b, c));
        }
        vector<int> ret(N+1, -1);
        vector<int> path(N+1, -1);
        int cnt = dfs(ret, path, value, adj, 1);
        cout<<ret[1]<<' '<<cnt<<endl;
        for ( int i = 1; i != -1; ) {
            cout<<i<<' ';
            i = path[i];
        }
        cout<<endl;
    }
}

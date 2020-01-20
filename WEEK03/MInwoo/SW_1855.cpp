
#include<iostream>
#include<queue>
#include<cstring>
#include<queue>
#include<algorithm>
using namespace std;

int T;
int N;
vector<vector<int>> map;
queue<int> myqueue;
int founded[100001];
int depth_value[100001];
int par[100001][18];

int lca(int x, int y) {
	if(depth_value[x] > depth_value[y]) swap(x, y);
	for(int i = 17; i >=0; i--) {
		if(depth_value[y] - depth_value[x] >= (1 << i)) y = par[y][i];
	}
	if(x == y) return x;
	for(int i = 17; i >= 0; i--) {
		if(par[x][i] != par[y][i]) {
			x = par[x][i];
			y = par[y][i];
		}
	}
	return par[x][0];
}

void pre_bfs() {

	int current_node;
	int next_node;

	myqueue.push(1);

	while(!myqueue.empty()) {
		current_node = myqueue.front();
		myqueue.pop();

		for(int i = 0; i < map[current_node].size(); i++) {
			next_node = map[current_node][i];
			if(founded[next_node] == 1) continue;	
			depth_value[next_node] = depth_value[current_node] + 1;
			myqueue.push(next_node);
			//partial tree 0번에 바로 위 부모 노드 저장
			par[next_node][0] = current_node;
		}
	}
}

long long after_bfs() {
	
	int current_node;
	int next_node;
	int com_an;
	long long answer = 0;

	int prev_node = 1;

	myqueue.push(1);

	while(!myqueue.empty()) {
		current_node = myqueue.front();
		myqueue.pop();

		for(int i = 0; i < map[current_node].size(); i++) {
			next_node = map[current_node][i];
			if(founded[next_node] == 1) continue;	
			founded[next_node] = 1;
			myqueue.push(next_node);
		}
		
		com_an = lca(prev_node, current_node);
		answer += depth_value[current_node] + depth_value[prev_node] - 2*depth_value[com_an];
		prev_node = current_node;
	}
	return answer;
}

void f() {
    for (int j = 1; j < 18; j++) {
        for (int i = 1; i <= N; i++) {
            par[i][j] = par[par[i][j - 1]][j - 1];
        }
    }
}

int main() {

	int mycount = 1;

	scanf("%d", &T);
	while(T--) {

		int temp;

		scanf("%d", &N);
		memset(founded, 0, sizeof(founded));
		memset(depth_value, 0, sizeof(depth_value));
		memset(par, 0, sizeof(par));
		map = vector<vector<int>> (N+1, vector<int>());

		for(int node = 2; node <= N; node++) {
			scanf("%d", &temp);
			map[temp].push_back(node);
		}

		pre_bfs();
		f();
		cout <<"#"<<mycount<<" "<<after_bfs()<<endl;
		mycount++;
	}
}

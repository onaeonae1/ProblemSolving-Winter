#include<iostream>
#include<vector>
#include<stack>
#include<stdio.h>
#include<cstring>
#include<algorithm>
using namespace std;

int V, E;
int visited[10001];
int r;
vector<vector<int>> map;
vector<vector<int>> r_map;
vector<vector<int>> scc;
stack<int> mystack;

bool cmp(vector<int> x, vector<int> y) {
	return x[0] <y[0];
}

void dfs(int vertex) {
	visited[vertex] = 1;
	for(int next = 0; next < map[vertex].size(); next++) {
		if(visited[next] == 0) dfs(next);
	}
	mystack.push(vertex);
}

void dfs1(int vertex, int c) {
	visited[vertex] = 1;
	scc[c].push_back(vertex);
	for(int next : r_map[vertex]) {
		if(visited[next] == 0) dfs1(next, c);
	}
}

int main() {

	int a, b;

	scanf("%d %d", &V, &E);
	map = vector<vector<int>>(V+1);
	r_map = vector<vector<int>>(V+1);

	for(int i = 0; i < E; i++) {
		scanf("%d %d", &a, &b);
		map[a].push_back(b);
		map[b].push_back(a);
	}

	for(int i = 1; i <= V; i++) {
		if(visited[i] == 0) dfs(i);
	}
	
	memset(visited, 0, sizeof(visited));

	while(map.size()) {
		int here = mystack.top();
		mystack.pop();
		if(visited[here]) continue;
		scc.resize(++r);
		dfs1(here, r-1);
	}

	for(int i = 0; i < r; i++) {
		sort(scc[i].begin(), scc[i].end());
	}
	sort(scc.begin(), scc.end(), cmp);
	printf("%d\n", r);
	for(int i = 0; i < r; i++) {
		for(int x : scc[i]) {
			printf("%d ", x);
		}
		printf("-1\n");
	}
}

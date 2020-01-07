#include<iostream>
#include<algorithm>
#include<vector>
#include<stack>
#include<cstring>
#define MAX 10001
using namespace std;
int visited[MAX]; //방문 체크 목적
vector<vector<int>>scc;
vector<vector<int>>vt; //방향 그래프
vector<vector<int>>rvt; //역방향 그래프
stack<int> st; //dfs 돌린 후 정점들에 대한 스택
int v, e; //정점, 간선의 갯수
int result;

bool compare(vector<int> alpha, vector<int> beta) {
	return alpha.front() < beta.front();
}
void dfs(int v) {
	visited[v] = true;
	for (int i = 0; i < vt[v].size(); i++) {
		int next = vt[v].at(i);
		if (!visited[next]) {
			dfs(next);
		}
	}
	//스택에 넣어줌
	st.push(v);
}
void func(int v, int c) {
	visited[v] = true;
	scc[c].push_back(v);
	for (int i = 0; i < rvt[v].size(); i++) {
		int next = rvt[v].at(i);
		if (!visited[next]) {
			func(next, c);
		}
	}
}
int main() {
	scanf("%d %d", &v, &e);
	int x, y;
	//그래프 초기화
	vt.resize(v + 1);
	rvt.resize(v + 1);
	//그래프 모델링
	for (int i = 0; i < e; i++) {
		scanf("%d %d", &x, &y); //간선의 정보 x->y
		vt[x].push_back(y); //방향 그래프
		rvt[y].push_back(x); //역방향 그래프
	}
	//방향 그래프에 대해 DFS, stack에 삽입해줌
	for (int i = 1; i <= v; i++) {
		if (!visited[i]) { //방문 안했다면
			dfs(i); //dfs 진행
		}
	}
	//dfs 돌린 후 역방향에서 사용하기 위해
	//visited를 다시 초기화 해준다.
	memset(visited, 0, sizeof(visited));
	//역방향 탐색
	while (st.size()) {
		int now = st.top();
		st.pop();
		if (!visited[now]) {
			scc.resize(++result);
			func(now, result - 1);
		}
	}
	//문제 조건에 맞도록 정렬 해주는 과정
	for (int i = 0; i < result; i++) {
		sort(scc[i].begin(), scc[i].end());
	}
	sort(scc.begin(), scc.end(), compare);
	printf("%d\n", result);
	for (int i = 0; i < result; i++) { //생긴 그룹의 수만큼
		for (int element : scc[i]) {
			printf("%d ", element);
		}
		printf("-1\n");
	}
	return 0;
}

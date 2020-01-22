#include<iostream>
#include<vector>
#include<cstring>
#define MAX 20005 //정점의 최대 갯수
using namespace std;
vector<int> adj[MAX]; //간선
int colors[MAX]; //색
int v, e;
bool result = true;
void search(int now, int color) { //dfs루다가 탐색
	colors[now] = color;
	vector<int>& near = adj[now]; //현재 정점과 연결된 간선
	for (int i = 0; i < near.size(); i++) { //연결된 정점들에 대해
		int element = near.at(i); 
		if (colors[element] == color) { //연결된 애가 나랑 같은 색이라면?
			result = false;
			return;
		}
		if (colors[element] == 0) { //색칠되어 있지 않음
			colors[element] = (color * -1);//반대색으로 칠함
			search(element, color*-1);
		}
	}
}
int main() {
	int c;
	int cA = 1;
	scanf("%d", &c);
	while (c--) {
		result = true;
		memset(colors, 0, sizeof(colors));
		scanf("%d %d", &v, &e);
		for (int i = 1; i <= v; i++) {
			adj[i].clear();
		}
		//그래프 만들기
		for (int i = 0; i < e; i++) {
			int head, tail;
			scanf("%d %d", &head, &tail);
			adj[head].push_back(tail);
			adj[tail].push_back(head);
		}
		for (int i = 1; i <= v; i++) { //1번 정점부터 n번 정점까지
			if (result == false) { //이미 이분 그래프의 조건을 만족하지 않음
				break;
			}
			if (colors[i] == 0) {
				search(i, cA);
			}
		}
		if (result == true) {
			printf("YES \n");
		}
		else {
			printf("NO \n");
		}
	}
	return 0;
}

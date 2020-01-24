#include <iostream>
#include <algorithm>
#include <queue>
#include <vector>
#include <cstring>
using namespace std;
int dist[20002];
vector<vector<pair<int, int>>> vt; //vt[alpha] = {beta, value} : alpha에서 beta로 value 가중치를 갖는 간선존재
int main() {
	int vertex, edge;
	scanf("%d%d", &vertex, &edge);
	//초기화
	vt.resize(vertex + 1);
	memset(dist, -1, sizeof(dist));
	//그래프 만들기
	for (int i = 0; i < edge; i++) {
		int alpha, beta, value;
		scanf("%d%d%d", &alpha, &beta, &value);
		vt[alpha].push_back({ beta,value });
	} 
	priority_queue<pair<int, int>> pq;
	int start, target;
	scanf("%d %d", &start, &target);
	pq.push({ 0,start });//시작 정보
	while (pq.size()) {//pq가 빌 때까지 다익스트라 알고리즘 동작
		int now = pq.top().second;
		int val = -pq.top().first;//최소힙으로 쓰려고 음수 사용
		pq.pop(); //큐에서 제거
		if (dist[now] == -1) { //갱신되지 않은 대상에 대해
			dist[now] = val;
			for (auto ver : vt[now]) {
				int next = ver.first;
				int nval = -ver.second - val;
				if (dist[next] == -1) {
					pq.push({ nval,next });
				}
			}
		}
	}
	printf("%d", dist[target]);
	return 0;
}

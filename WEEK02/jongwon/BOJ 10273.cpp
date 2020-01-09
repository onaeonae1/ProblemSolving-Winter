#include <iostream>
#include <vector>
using namespace std;
vector<int> vertex; //정점들의 값 ->동굴에 들어있는 보물의 가치
vector<int> dp; //정점에 대한 DP 테이블 -> 해당 정점을 방문했을 때 얻을 수 있는 최대 가치 메모이제이션
vector<int> tracking; //한 정점에 대해 정답으로서, 연결된 다른 정점
vector<int> answer; //정답
vector<vector<pair<int, int > > > graph; //graph[head] -> (tail, weight) : head에서 tail로 가는 비용
int topological(int here) { //위상정렬
	int &ret = dp[here];
	if (ret != 0) {
		return ret;
	}
	for (int i = 0; i < graph[here].size(); i++) { //정점들에 대해
		int there = graph[here][i].first; //연결된 다른 정점
		int weight = graph[here][i].second; //연결되는데 필요한 비용
		int temp = topological(there) - weight; //위상 정렬을 돌고 와서 weight 고려
		if (temp > ret) {
			ret = temp; //DP 업데이트
			tracking[here] = there;
		}
	}
	ret += vertex[here]; //해당 정점의 보물 가치
	return ret;
}

void dfs(int here) { //정답인 경로 추적 tracing을 따라서 dfs를 돌린다.
	answer.push_back(here);
	if (tracking[here] == -1) { 
		return; 
	}
	else {
		dfs(tracking[here]);
	}
}

int main() {
	int c;
	scanf("%d", &c);
	while (c--) {
		int n, m; //정점 , 간선의 수
		scanf("%d %d", &n, &m);
		//벡터들 초기화
		vertex = vector<int>(n + 1);
		dp = vector<int>(n + 1);
		tracking = vector<int>(n + 1, -1);
		graph = vector<vector<pair<int, int > > >(n + 1);

		for (int i = 1; i <= n; i++) {
			scanf("%d", &vertex[i]);
		}
		for (int i = 0; i < m; i++) {
			int head, tail, weight;
			scanf("%d %d %d", &head, &tail, &weight);
			graph[head].push_back(make_pair(tail, weight));
		}

		int temp = topological(1);
		dfs(1); //1번 정점부터 시작하므로 여기서부터 탐색한다.
		printf("%d %d \n", temp, answer.size());
		for (int i = 0; i < answer.size(); i++) {
			printf("%d ", answer[i]);
		}
		printf("\n");
		answer.clear();
	}
	return 0;
}

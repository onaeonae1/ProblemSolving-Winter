#include<iostream>
#include<vector>
#include<utility>
#include<algorithm>
#include<stack>
#include<fstream>
using namespace std;

int T;
int N, E;
vector<int> max_sum; //주어진 map내에서 최대 수익
int branch_point;
int flag;
int testcase;
int average;
vector<int> visited;
vector<int> mycount;//필수
vector<int> v_profit;//필수
vector<vector<pair<int,int>>> map;//필수
vector<stack<int>> answer;//필수

void getinfo() {

	int a,b;
	int temp;

	cin >> N >> E;
	visited = vector<int>(N+1, 0);
	map = vector<vector<pair<int,int>>>(N+1, vector<pair<int,int>>());
	v_profit.push_back(0);

	for(int i = 0; i < N; i++) {
		cin >> temp;
		v_profit.push_back(temp);
		average += temp;
	}

	for(int i = 0; i < E; i++) {
		cin >> a >> b >> temp;
		map[a].push_back({b, temp});
		average -= temp;
	}

	average = average / N;

	return;
}

void dfs(int source, int benefit) {

	int next_vertex;
	int next_cost;
	int next_sum;

	if(E == 0) {
		max_sum[testcase] = v_profit[1];
		answer[testcase].push(1);
	}
	
	if(visited[source] == 1) return;
	visited[source] = 1;

	for(int i = 0; i < map[source].size(); i++) {
		
		if(flag = 1) {
			branch_point = source;
			flag = 0;
		}
		
		next_vertex = map[source][i].first;
		next_cost = map[source][i].second;

		next_sum = benefit - next_cost + v_profit[next_vertex];
		max_sum[testcase] = max(max_sum[testcase], next_sum);
		dfs(next_vertex, next_sum);
	}

	//visited[source] = 1;

	if(branch_point == source) flag = 1;

	if(benefit == max_sum[testcase] && average <= max_sum[testcase]) {
		while(!answer[testcase].empty()) answer[testcase].pop();
		mycount[testcase] = 0;
		flag = 1;
	}
	if(flag == 1) {
		answer[testcase].push(source);
		mycount[testcase]++;
	}
	return;
}

void printall() {
	
	int temp = 0;

	while(temp < testcase) {
		cout << max_sum[temp] << " " << mycount[temp] << endl;
		while(!answer[temp].empty()) {
			cout << answer[temp].top() << " ";
			answer[temp].pop();
		}
		cout << endl;
		temp++;
	}
}

int main() {

	//freopen("input.txt", "r", stdin);

	cin >> T;

	mycount = vector<int>(T+1, 0);
	max_sum = vector<int>(T+1, -99999);
	answer = vector<stack<int>>(T+1, stack<int>());

	while(T--) {

		flag = 0;
		average = 0;
		v_profit.clear();

		getinfo();
		dfs(1, v_profit[1]);
		testcase++;
	}
	printall();
}

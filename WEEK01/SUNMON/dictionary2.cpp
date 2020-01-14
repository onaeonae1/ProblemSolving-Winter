/**
 * RESULT: [CORRECT], 32ms
 * NAME: DICTIONARY
 * LINK: https://algospot.com/judge/problem/read/DICTIONARY
 * DATE: 2020-01-13
 * AUTHOR: sunmon
 * TIP:
 * 1. 인접 행렬 이용
 * 2. 
**/
#define ALPHA 26
#include <iostream>
#include <cstring> 
#include <vector>
#include <utility> // pair
#include <algorithm> //reverse

using namespace std;

vector<int> visited;
vector<vector<int> > adj;
vector<int> order;

//인접행렬 생성
void makeList(const vector<string>& words)
{
    adj = vector<vector<int> >(ALPHA, vector<int>(ALPHA,0));

    //단어목록 하나씩 돌면서 연관성을 인접행렬에 추가
    for(int i = 0; i<words.size()-1; i++)
    {
        int len = min(words[i].length(), words[i+1].length());
        for(int j = 0; j<len; j++)
        {
            int prev, next;
            prev = words[i][j]-'a';
            next = words[i+1][j]-'a';
            if(prev == next) continue;
            adj[prev][next]=1;
            break;
        }
    }
}

//dfs
void dfs(int here)
{
    visited[here] = 1;
    for(int there = 0; there<adj.size(); there++)
        if(!visited[there] && adj[here][there]==1) dfs(there);
    order.push_back(here);
}

//위상정렬 결과 리턴. 모순이 있으면 빈 벡터 반환
vector<int> topologicalSort()
{
    visited = vector<int>(ALPHA);
    order.clear();

    //전체 dfs 순회
    for(int node = 0; node < adj.size(); node++)
    {
        if(!visited[node]) dfs(node);
    }

    //dfs결과를 뒤집어 노드 간 연결 순서 정렬
    reverse(order.begin(), order.end());

    //모순이 있는지 찾기
    for(int i = 0; i<order.size(); i++)
    {
        for(int j = i+1; j<order.size(); j++)
        {
            int prev = order[i], next = order[j];
            if(adj[next][prev] == 1) return vector<int>();
        }
    }
    return order;
}



int main()
{
    int testcase;
    cin >> testcase;


    while(testcase--)
    {
        int W;
        cin >> W;
        vector<string> words(W);
        for(auto& w: words) cin >> w;
        
        makeList(words);
        if(topologicalSort().size() == 0) cout << "INVALID HYPOTHESIS\n";
        else
        {
            for(auto& a: order) cout << (char)(a+'a');
            cout <<endl;
        }
    }
}

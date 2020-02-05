/**
 * @name 도미노
 * @link: https://www.acmicpc.net/problem/4196
 * @date 2020-02-05
 * @author sunmon
 * TIP:
 *  1. 사이클이 있을 수 있다 -> scc별로 DAG 그리기
 *  2. 위상정렬 문제. DAG에서 indegree가 없는 노드 수를 세면 된다.
**/

#include <iostream>
#include <vector>
#include <algorithm>
#include <stack>
using namespace std;

int V, E;   //도마노 수, 간선 수
vector<vector<int> > adj;   //연결된 도미노 그래프를 표현한 인접리스트. 도미노 번호는 0부터 시작!
vector<int> discovered;         //노드(도미노)가 발견된 순서 저장
stack<int> unlabeled;             //발견은 됐으나 아직 scc로 안 묶인 노드들을 저장한다
vector<int> sccID;              //노드의 scc번호를 저장
int nodeCounter, sccCounter;    

//here에서 갈 수 있는 노드 중 가장 먼저 발견된 순서를 리턴한다
//이미 scc로 묶인 노드는 신경안쓰고 패스한다
int scc(int here)
{
    int ret = discovered[here] = nodeCounter++;
    unlabeled.push(here);

    //인접 노드 탐색
    for(int there : adj[here])
    {
        //아직 탐색 안 했으면 보러가기. 트리 간선. 
        if(discovered[there] == -1) ret = min(ret, scc(there));
        
        //이미 봤고 scc로 안 묶였으면 같은 사이클이 될 수 있다
        else if(sccID[there] == -1) ret = min(ret, discovered[there]);
    }

    // here이 scc사이클을 매듭짓는 노드라면 현재 노드와 자식들을 scc로 묶는다
    if( discovered[here] == ret)
    {
        while(true)
        {
            int u = unlabeled.top();
            sccID[u] = sccCounter;
            unlabeled.pop();
            if(u == here) break;
        }
        sccCounter++;
    }
    return ret;
}

//타잔 scc 알고리즘을 수행하고 그 결과를 리턴한다
vector<int> tarjanSCC()
{
    unlabeled = stack<int>();
    discovered = sccID = vector<int>(V, -1); 
    sccCounter = nodeCounter = 0;
    for(int i = 0; i<V; i++)
        if(sccID[i] == -1) scc(i);
    return sccID;
}

//위상정렬을 위한 dfs
void dfs(int here, vector<int>& visited)
{
    visited[here] = 1;
    for(int there : adj[here])
    {
        if(!visited[there]) dfs(there, visited);
    }
}

//도미노를 손으로 쓰러뜨려야 하는 횟수를 리턴한다
int usingHand()
{
    //scc별로 위상정렬하여 저장
    vector<pair<int,int> > dom;         //first: scc번호, second: 도미노 노드번호
    vector<int> visited(V,0);
    int hand = 0;
    vector<int> temp = tarjanSCC();

    for(int i = 0; i<V; i++)
        dom.push_back({-temp[i], i});
    sort(dom.begin(), dom.end());

    //scc별로 위상정렬한 결과로 dfs
    for(pair<int,int> d: dom)
    {
        if(!visited[d.second])
        {
            dfs(d.second, visited);
            ++hand;
        }
    }

    return hand;
}



//도미노간 연결 그래프 그리기
void makeGraph()
{
    adj.clear();
    adj.resize(V);

    for(int i = 0; i<E; i++)
    {
        int a, b;
        cin >> a >> b;
        adj[a-1].push_back(b-1);
    }
}

int main()
{
    int testcase;
    cin >> testcase;
    while(testcase--)
    {
        cin >> V >> E;
        makeGraph();
        cout << usingHand() << endl;
    }
}

/**
 * RESULT: Correct, 16ms
 * NAME: 회의실배정 MEETINGROOM
 * LINK: https://algospot.com/judge/problem/read/MEETINGROOM
 * DATE: 2020-02-07
 * AUTHOR: sunmon
 * TIP:
**/
#include <iostream>
#include <algorithm>
#include <vector>
#include <utility>
#include <stack>
using namespace std;

vector<pair<int, int> > meetings;
vector<vector<int> > adj;   //인접리스트 그래프
stack<int> visited;
vector<int> discovered, sccID;
int sccCounter, nodeCounter;


bool disjoint(const pair<int, int>& a, const pair<int,int>& b)
{
    return (a.second <= b.first || b.second <= a.first);
}

//adj그래프, 2 -SAT문제
//n번팀은 meetings[2n], meetings[2n+1]중 하나를 써야 함
void makeGraph()
{
    //전역변수 초기화
    int meet = meetings.size();
    adj.clear();
    adj.resize(meet*2);

    //한팀은 두 회의 중 하나를 열어야 한다.
    for(int i = 0; i<meet; i+=2)
    {
        int a = i, b = a+1;
        adj[2*a+1].push_back(2*b);
        adj[2*b+1].push_back(2*a);
        adj[2*a].push_back(2*b+1);
        adj[2*b].push_back(2*a+1);
    }


    //회의가 겹치면 둘 중 하나는 안 열려야 한다
    for(int i = 0; i<meet; i++)
    {
        for(int j = i+1; j< meet; j++)
        {
            if(!disjoint(meetings[i], meetings[j]))
            {
                adj[i*2].push_back(j*2+1);
                adj[j*2].push_back(i*2+1);
            }
        }
    }

}

//here에서 갈 수 있는 노드 중 가장 먼저 발견된 순서를 리턴한다
//이미 scc로 묶인 노드는 신경안쓰고 패스한다
int scc(int here)
{
    int ret = discovered[here] = nodeCounter++;
    visited.push(here);

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
            int u = visited.top();
            sccID[u] = sccCounter;
            visited.pop();
            if(u == here) break;
        }
        sccCounter++;
    }
    return ret;
}

//타잔 scc 알고리즘을 수행하고 그 결과를 리턴한다
vector<int> tarjanSCC()
{
    visited = stack<int>();
    discovered = sccID = vector<int>(adj.size(), -1); 
    sccCounter = nodeCounter = 0;
    for(int i = 0; i<adj.size(); i++)
        if(sccID[i] == -1) scc(i);
    return sccID;
}


//scc만들고 각 scc별로 참/거짓 묶기
//2-SAT문제의 답을 반환
vector<int> solve2SAT()
{
    vector<int> sccLabel = tarjanSCC();

    //IMPOSSIBLE판단
    for(int i = 0; i<sccLabel.size(); i+=2)
    {
        if(sccLabel[i] == sccLabel[i+1]) return vector<int>();
    }


    //scc별로 묶어서 DAG만들어 위상정렬
    vector<pair<int,int> >order;
    for(int i = 0; i< sccLabel.size(); i++)
    {
        order.push_back({-sccLabel[i], i});
    }
    sort(order.begin(), order.end());

    vector<int> value(meetings.size(), -1);
    for(int i = 0; i<order.size(); i++)
    {
        int isNot = (order[i].second % 2);
        int meetNum = order[i].second / 2;

        if(value[meetNum] != -1) continue;
        value[meetNum] = isNot;
    }

    return value;
}


int main()
{
    int testcase;
    cin >> testcase;
    while(testcase--)
    {
        meetings.clear();

        int n;
        cin >> n;
        
        for(int i = 0; i<n*2; i++)
        {
            int b,e;
            cin >> b >> e;
            meetings.push_back({b,e});
        }

        makeGraph();
        vector<int> answer = solve2SAT();
        if(answer.size()==0) cout << "IMPOSSIBLE\n";
        else{
            cout << "POSSIBLE\n";
            for(int i = 0; i<answer.size(); i++)
            {
                if(answer[i]) cout << meetings[i].first << " " << meetings[i].second << endl;
            }

        }

        
    }
}

/**
 * RESULT: 시간초과
 * NAME: 끝말잇기
 * LINK: https://algospot.com/judge/problem/read/WORDCHAIN
 * DATE: 2020-01-13
 * AUTHOR: sunmon
 * TIP:
**/

#include <iostream>
#include <vector>
#include <algorithm>
#include <string>

using namespace std;
vector<string> words;               //끝말잇기에 쓰일, 입력받은 단어 목록
vector<vector<int> >adj;            //adj[i][j] : 알파벳[i]와[j]사이 간선의 수
vector<string>graph[26][26];       //graph[i][j] : i로 시작해서 j로 끝나는 단어 저장
//indegree[i]: i로 시작하는 단어의 수
//outdegree[i]: i로 끝나는 단어의 수
vector<int> indegree, outdegree;


//here부터 시작하는 오일러서킷 or 트레일을 path에 저장한다
void getEuler(int here, vector<int>& path){
    for(int i = 0; i<26; i++)
    {
        while(adj[here][i]>0)
        {
            adj[here][i]--;
            getEuler(i,path);
        }
    }
    path.push_back(here);
}

//알파벳간 오일러 경로를 만들어서 리턴한다
vector<int> makePath()
{
    vector<int> path;
    int start = -1, end = -1;


    //트레일 시작점과 끝 점 알아낸다
    for(int i = 0; i<26; i++)
    {
        int delta = outdegree[i] - indegree[i];
        if(delta > 1 || delta < -1) return path;

        //시작점 구하기, 시작점이 두 개면 빈 벡터 반환
        if(delta == 1)
        {
            if(start == -1) start = i;
            else return path;
        }
        //끝점 구하기, 끝점이 두 개면 빈 벡터 반환
        else if(delta == -1)
        {
            if(end == -1) end = i;
            else return path;
        }
    }

    //시작은 있는데 끝이 없거나, 그 반대의 경우 빈 벡터 반환
    if(start * end < 0) return path;

    //오일러 트레일 시작
    if(start > -1) getEuler(start, path);

    //오일러 서킷 시작
    else
    {
        for(int i = 0; i<26; i++)
        {
            if(!outdegree[i]) continue;
            getEuler(i, path);
            break;
        }
    }

    return path;
}


//전역 변수 초기화
void makeGraph()
{
    //words 입력받기
    int N;
    cin >> N;
    words = vector<string>(N);
    for(auto& w: words) cin >> w;

    //전역 변수 초기화
    adj = vector<vector<int> >(26, vector<int>(26,0));
    indegree = outdegree = vector<int>(26,0);
    for(auto& a: graph) for(auto& b: a) b.clear();


    for(string& w : words)
    {
        int from = w.front() - 'a';
        int to = w.back() - 'a';
        adj[from][to]++;
        graph[from][to].push_back(w);
        outdegree[from]++;
        indegree[to]++;
    }
}

string solve()
{
    makeGraph();
    string ret = "";
    vector<int> path = makePath();
    if(path.size() == 0) return "IMPOSSIBLE";

    reverse(path.begin(), path.end());
    for(int i = 0; i<path.size()-1; i++)
    {
        int from = path[i], to = path[i+1];
        if(ret.size()) ret += " ";
        ret += graph[from][to].back();
        graph[from][to].pop_back();
    }

    return ret;
}

int main()
{
    int testcase;
    cin >> testcase;
    while(testcase--)
    {
        string answer = solve();
        cout << answer << endl;
    }
}

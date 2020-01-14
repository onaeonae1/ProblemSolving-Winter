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
vector<string> words;       //끝말잇기 단어
vector<vector<int> >adj;    //adj[i][j] : word[i]->word[j]로 끝말잇기 가능 여부
vector<int> visited;        //visited[i]: i번째 단어 방문 여부
vector<int> chain;          //끝말잇기 단어 순서 

//끝말잇기 성공 여부 리턴. 성공하면 1, 아니면 0
int dfs(int here)
{
    //모든 단어를 사용했는지 검사
    int ret = visited[here] = 1;
    for(auto& v: visited) ret &= v;

    //연결된 다음 글자로 끝말잇기
    for(int next = 0; next<words.size(); next++)
    {
        if(!visited[next] && adj[here][next]==1) ret |= dfs(next);
    }

    visited[here]=0;
    if(ret == 1) chain.push_back(here);
    return ret;
}

//끝말잇기 결과 벡터 리턴
vector<int> dfsAll()
{
    chain.clear();
    visited = vector<int>(adj.size());
    for(int i = 0; i<words.size(); i++)
    {
        if(dfs(i)) return chain;
    }
    return vector<int>();
}

int main()
{
    int testcase;
    cin >> testcase;
    while(testcase--)
    {
        int N;
        cin >> N;
        words = vector<string>(N);
        for(auto& w: words) cin >> w;

        //인접행렬 초기화
        adj = vector<vector<int> >(N, vector<int>(N));
        for(int i = 0; i<words.size(); i++)
        {
            for(int j = 0 ; j<words.size(); j++)
            {
                if(words[i].back() == words[j].front()) adj[i][j] = 1;
            }
        }

        //끝말잇기 결과 출력
        if(dfsAll().size()==0) cout << "IMPOSSIBLE";
        else for(auto& c: chain) cout << words[c] << " ";
        cout << endl;
    }
}

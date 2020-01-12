/**
 * [correct], 36ms
 * https://algospot.com/judge/problem/read/DICTIONARY
 * 2020-01-12 by sunmon
**/

#include <iostream>
#include <cstring> 
#include <vector>
#include <utility> // pair
#include <algorithm> //reverse
#include <list>

using namespace std;

vector<int> visited;
vector< list<int> > adj;
vector<int> order;



void makeList(const vector<string>& words)
{
    adj.clear();

    for(int i = 1; i<words.size(); i++)
    {
        int len = min(words[i].size(), words[i-1].size());
        for(int j = 0; j<len; j++)
        {
            if(words[i][j] == words[i-1][j]) continue;
            int from = words[i-1][j]-'a';
            int to = words[i][j] - 'a';

            //adj에 from이 있으면 그 뒤에 to 추가, 없으면 새로 from추가 후 to추가
            vector< list<int> >::iterator it;
            for(it = adj.begin(); it != adj.end(); it++)
            {
                if(it->front() == from) break;
            }

            if(it == adj.end())
            {
                list<int> list_;
                list_.push_back(from);
                adj.push_back(list_);
                it = adj.end()-1;
            }

            it->push_back(to);
            break;
        }
    }
}


void dfs(int node)
{
    visited[node] = 1;
    for(auto& n : adj)
    {
        if(n.front() != node) continue;
        for(auto& next: n)
            if(visited[next] == 0) dfs(next);
        break;
    }
    order.push_back(node);
}

vector<int> topologicalSort()
{
    visited = vector<int>(26, 0);
    order.clear();

    for(int i = 0; i<adj.size(); i++)
    {
        if(visited[adj[i].front()] == 0) dfs(adj[i].front());
    }
    
    reverse(order.begin(), order.end());

    for(int i = 0; i<order.size(); i++)
    {
        for(int j = i+1; j<order.size(); j++)
        {
            //adj 벡터에서 order[j]노드 찾기
            vector< list<int> >::iterator it;
            for(it = adj.begin(); it != adj.end(); it++)
            {
                //order[j]노드로 시작하는 리스트에서 order[i]노드 찾기
                if(it->front() != order[j]) continue;
                for(list<int>::iterator a = it->begin(); a != it->end(); a++)
                {
                    if(*a == order[i]) return vector<int>();
                }
            }

        }

    }
    return order;
}


int main()
{
    int testcase = 0;
    cin >> testcase;
    while(testcase --)
    {
        int wordSize;
        cin >> wordSize;

        // words 초기화
        vector<string> words;
        // words = {};
        words.resize(wordSize);

        //input
        for(auto& a: words) cin >> a;


        //dfs
        makeList(words);

        vector<int> answer = topologicalSort();
        if(answer.size() == 0) cout << "INVALID HYPOTHESIS" << endl;
        else
        {
            for(auto& a: answer)
            {
                cout << (char)(a + 'a');
            }
            cout << endl;
        }
    }
}

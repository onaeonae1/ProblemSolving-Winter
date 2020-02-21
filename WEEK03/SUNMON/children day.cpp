/**
 * RESULT: 정답, 48ms
 * NAME: CHILDRENDAY
 * LINK: https://algospot.com/judge/problem/read/CHILDRENDAY
 * DATE: 2020-02-20
 * AUTHOR: sunmon
 * TIP:
 * 1. nk + m == n으로 나누면 나머지가 m이다
 * 2. bfs
 * 3. 숫자 너무 커서 int로 반환 불가. 따로 string으로 path 복구하는 과정 필요
**/


#include <iostream>
#include <vector>
#include <queue>
#include <map>
#include <algorithm>
#include <set>
#include <string>
using namespace std;
string digit;
vector<string> numbers;     //numbers[mod] : 나머지가 mod일 때 선택한 digit저장
vector<int> parents;        //parents[mod] : 나머지가 mod일때 부모 저장
int m, n;

int bfs()
{
    queue<int> q;
    q.push(0);
    parents[0] = 0;

    while(!q.empty())
    {
        int c = q.front();
        q.pop();

        for(char& s : digit)
        {
            int cc = c * 10 + (s-'0');  //cc는 n+m을 넘지 않음?
            int mod = cc % n;
            if(cc >= n) mod += n;
            if(parents[mod] == -1)
            {
                q.push(mod);
                parents[mod] = c;
                numbers[mod] = s;
            } 
        }
    }
    return parents[n+m];
}

void solve()
{
    int answer = bfs();
    if(answer == -1) cout << "IMPOSSIBLE\n";
    else
    {
        string ans = "";
        int here = n+m;
        while(parents[here]!=here)
        {
            ans += numbers[here];
            here = parents[here];
        }
        reverse(ans.begin(), ans.end());
        cout << ans << endl;
    }
}

int main()
{
    int testcase;
    cin >> testcase;
    while(testcase--)
    {
        cin >> digit >> n >> m;
        sort(digit.begin(), digit.end());
        parents = vector<int>(n+n, -1);
        numbers = vector<string>(n+n);
        solve();
    }
}

/**
 * RESULT: CORRECT, 972ms
 * NAME: SORTGAME
 * LINK: https://algospot.com/judge/problem/read/SORTGAME
 * DATE: 2020-02-20
 * AUTHOR: sunmon
 * TIP:
 * 1. 상태벡터 이용
 * 2. bfs
**/

#include <iostream>
#include <vector>
#include <queue>
#include <map>
#include <algorithm>
using namespace std;
vector<int> numbers;
map<vector<int>,int> toSort;

vector<int> getRelativeNums(vector<int>& nums)
{
    vector<int> tmp(nums.size(), 0);
    for(int i = 0; i<nums.size(); i++)
    {
        for(int j = 0; j<i; j++)
        {
            nums[i] > nums[j] ? tmp[i]++ : tmp[j]++;
        }
    }
    return tmp;
}

void bfs(vector<int>& relativeNums)
{
    vector<int> perm(relativeNums.size());
    for(int i = 0; i<perm.size(); i++) perm[i] = i;


    //print
    // for(int& i: perm) cout << i << " ";
    // cout << endl;


    queue<vector<int> > q;
    q.push(perm);
    toSort[perm] = 0;
    
    while(!q.empty())
    {
        vector<int> here = q.front();
        q.pop();
        int cost = toSort[here];

        for(int i = 0; i<relativeNums.size(); i++)
        {
            for(int j = i+2; j<=relativeNums.size(); j++)
            {
                reverse(here.begin()+i, here.begin()+j);
                if(!toSort.count(here))
                {
                    toSort[here] = cost + 1;
                    q.push(here);
                }
                reverse(here.begin()+i, here.begin()+j);
            }
        }
    }
}

int solve()
{
    vector<int> relativeNums = getRelativeNums(numbers);
    bfs(relativeNums);

    return toSort[relativeNums];
}

int main()
{
    int testcase;
    cin >> testcase;

    while(testcase--)
    {
        int n;
        cin >> n;

        numbers.clear();
        numbers.resize(n);
        for(int& i : numbers) cin >> i;

        cout << solve() << endl;
    }
}
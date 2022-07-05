/*
    https://leetcode.cn/problems/smallest-string-with-swaps/
    2022-06-21
*/
#include <vector>
#include <queue>
#include <unordered_map>
using namespace std;
class Solution {
public:

    vector<int> parent;
    vector<int> rank;

    int Find(int x)
    {
        if(x != parent[x])
            parent[x] = Find(parent[x]);
        return parent[x];
    }

    void Union(int x, int y)
    {
        int X = Find(x), Y = Find(y);
        if(X == Y)
            return;
        if(rank[X] < rank[Y])
            parent[X] = Y;
        else{
            parent[Y] = X;
            if(rank[X] == rank[Y])
                rank[X]++;
        }
    }

    string smallestStringWithSwaps(string s, vector<vector<int>>& pairs) {

        int n = s.size();
        parent.resize(n);
        rank.resize(n, 0);

        for(int i = 0; i < n; i++)
            parent[i] = i;

        for(auto e : pairs)
            Union(e[0], e[1]);
        
        unordered_map<int, priority_queue<char, vector<char>, greater<char> > > m;

        for(int i = 0; i < n; i++)
            m[Find(i)].push(s[i]);

        int t;
        for(int i = 0; i < n; i++)
        {
            t = Find(i);
            if(!m[t].empty())
            {
                s[i] = m[t].top();
                m[t].pop();
            }
        }
        return s;
    }
};
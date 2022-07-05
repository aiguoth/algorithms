/*
    https://leetcode.cn/problems/is-graph-bipartite/
    2022-06-08
*/
#include <vector>
using namespace std;

class Solution {
public:

    vector<int> parent;

    int Find(int x)
    {
        if(x != parent[x])
            parent[x] = Find(parent[x]);
        return parent[x];
    }

    void Union(int x, int y)
    {
        int X = Find(x);
        int Y = Find(y);

        if(X != Y)
            parent[X] = Y;
    }

    bool IsConnected(int x, int y)
    {
        return Find(x) == Find(y);
    }

    bool isBipartite(vector<vector<int>>& graph) {

        int n = graph.size();
        parent.resize(n);

        for(int i = 0; i < n; i++)
            parent[i] = i;

        for(int u = 0; u < n; u++)
        {
            for(int & v : graph[u])
            {
                if(IsConnected(u, v))
                    return false;
                else
                    Union(graph[u][0], v);
            }
        }

        return true;
    }
};
/*
    https://leetcode.cn/problems/swim-in-rising-water/
    2022-06-22
*/
#include <vector>
#include <queue>
using namespace std;
struct Edge{
    int x, y, w;
    Edge(int a, int b, int c) : x(a), y(b), w(c) {}
    bool operator<(const Edge &rhs) const
    {
        return w > rhs.w;
    }
};

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

    bool IsConnected(int x, int y)
    {
        return Find(x) == Find(y);
    }


    int swimInWater(vector<vector<int>>& grid) {

        int n = grid.size();
        parent.resize(n * n);
        rank.resize(n * n, 0);
        for(int i = 0; i < n * n; i++)
            parent[i] = i;
        
        priority_queue<Edge> q;

        int t;
        for(int i = 0; i < n; i++)
        {
            for(int j = 0; j < n; j++)
            {
                t = i * n + j;
                if(j + 1 < n)
                    q.push(Edge(t, t + 1, max(grid[i][j], grid[i][j + 1])));
                if(i + 1 < n)
                    q.push(Edge(t, t + n, max(grid[i][j],grid[i + 1][j])));
            }
        }

        int ans = 0;
        while(!q.empty())
        {
            Edge edge = q.top();
            q.pop();
            Union(edge.x, edge.y);
            if(IsConnected(0, n * n - 1))
            {
                ans = edge.w;
                break;
            }
        }
        return ans;
    }
};
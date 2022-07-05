/*
    https://leetcode.cn/problems/path-with-minimum-effort/
    2022-06-21
*/
#include <vector>
#include <queue>
using namespace std;

struct Edge{
        int x, y, w;
        Edge(int a, int b, int c) : x(a), y(b), w(c) {}
    bool operator<(const Edge &b) const
    {
        return w > b.w;
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

    int minimumEffortPath(vector<vector<int>>& heights) {

        int rows = heights.size(), cols = heights[0].size();

        parent.resize(rows * cols);
        rank.resize(rows * cols, 0);
        for(int i = 0; i < rows * cols; i++)
            parent[i] = i;

        priority_queue<Edge> q;

        int t;
        for(int i = 0; i < rows; i++)
        {
            for(int j = 0; j < cols; j++)
            {
                t = i * cols + j;

                if(j + 1 < cols)
                    q.push(Edge(t, t + 1, abs(heights[i][j] - heights[i][j + 1])));
                if(i + 1 < rows)
                    q.push(Edge(t, t + cols, abs(heights[i][j] - heights[i + 1][j])));
            }
        }
        int ans = 0;
        while(!q.empty())
        {
            Edge e = q.top();
            q.pop();
            Union(e.x, e.y);

            if(IsConnected(0, cols * rows - 1)) // Union 后， 判断 左上与右下是否相连。如果相连则e.w为答案
            {
                ans = e.w; 
                break;
            }    
        }
        return ans;
    }
};
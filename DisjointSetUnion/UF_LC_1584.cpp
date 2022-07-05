/*
    https://leetcode.cn/problems/min-cost-to-connect-all-points/
    2022-06-13
*/

#include <vector>
using namespace std;

struct Edge{
    int u;  // index
    int v;  // index
    int d;  // distance
};

class Solution {
public:

    vector<int> parent;
    vector<int> size;

    int Find(int x)
    {
        if(x != parent[x])
            parent[x] = Find(parent[x]);
        return parent[x];
    }

    // 返回合并后 当前集合元素的数量。
    int Union(int x, int y)
    {
        int X = Find(x), Y = Find(y);
        if(X == Y)
            return -1;
        
        if(size[X] < size[Y])
        {
            parent[X] = Y;
            size[Y] += size[X];
            return size[Y];
        }
        else
        {
            parent[Y] = X;
            size[X] += size[Y];
            return size[X];
        }
    }

    bool IsConnected(int x, int y)
    {
        return Find(x) == Find(y);
    }

    int minCostConnectPoints(vector<vector<int>>& points) {

        int n = points.size();
        int nn = (n - 1) * n / 2;
        parent.resize(n);
        size.resize(n);
        vector<Edge> edge(nn);

        for(int i = 0; i < n; i++)
        {
            parent[i] = i;
            size[i] = 1;
        }
        int k = 0;
        for(int i = 0; i < n; i++)
        {
            for(int j = i + 1; j < n; j++)
            {
                edge[k++] = {i, j, abs(points[i][0] - points[j][0]) + abs(points[i][1] - points[j][1])};
            }
        }

        sort(edge.begin(), edge.end(), [](const Edge& a,const Edge& b){return a.d < b.d;});

        int s, ans = 0;
        for(int i = 0; i < nn; i++)
        {
            if(!IsConnected(edge[i].u, edge[i].v))
            {
                s = Union(edge[i].u, edge[i].v);
                if(s == n) // 当前边 i 的加入 表示已找到最小代价的最小生成树。
                    return ans + edge[i].d;
                else if(s != -1) // 还未找到
                    ans += edge[i].d;    
            }

        }
        return ans;

    }
};
/*
    https://leetcode.cn/problems/detect-cycles-in-2d-grid/
    2022-06-22
*/
#include <vector>
using namespace std;
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

    void Union(int x, int y)
    {
        int X = Find(x), Y = Find(y);
        if(X == Y)
            return;
        if(size[X] < size[Y])
        {
            parent[X] = Y;
            size[Y] += size[X];
        }else{
            parent[Y] = X;
            size[X] += size[Y];
        }
    }

    bool IsConnected(int x, int y)
    {
        return Find(x) == Find(y);
    }

    bool containsCycle(vector<vector<char>>& grid) {

        int m = grid.size(), n = grid[0].size();
        parent.resize(m * n);
        size.resize(m * n, 1);

        for(int i = 0; i < m * n; i++)
            parent[i] = i;

        int t;
        for(int i = 0; i < m; i++)
        {
            for(int j = 0; j < n; j++)
            {
                t = i * n + j;
                if(j + 1 < n && grid[i][j] == grid[i][j + 1])
                {
                    if(!IsConnected(t, t + 1))
                        Union(t, t + 1);
                    else if(size[Find(t)] >=4)
                            return true;
                }

                if(i + 1 < m && grid[i][j] == grid[i + 1][j])
                {
                    if(!IsConnected(t, t + n))
                        Union(t, t + n);
                    else if(size[Find(t)] >= 4)
                            return true;
                }
            }
        }
        return false;
    }
};
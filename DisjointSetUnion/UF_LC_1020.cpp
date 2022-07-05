/*
    https://leetcode.cn/problems/number-of-enclaves/
    2022-06-12
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
        
        if(size[X] <= size[Y])
        {
            parent[X] = Y;
            size[Y] += size[X];
        }
        else
        {
            parent[Y] = X;
            size[X] += size[Y];
        }
    }
    
    bool IsConnected(int x, int y)
    {
        return Find(x) == Find(y);
    }

    int numEnclaves(vector<vector<int>>& grid) {

        int m = grid.size(), n = grid[0].size();
        parent.resize(m * n);
        size.resize(m * n);
        int x;
        for(int i = 0; i < m; i++)
        {
            for(int j = 0; j < n; j++)
            {   
                x = i * n + j;  
                if(i == 0 || j == 0 || i == m - 1 || j == n - 1)
                    parent[x] = 0;
                else
                    parent[x] = x;
                size[x] = 1;
            }
        }
        int X, Y;
        static const int dir[2][2] = {{0,1}, {1, 0}};
        for(int i = 0; i < m; i++)
        {
            for(int j = 0; j < n; j++)
            {
                if(grid[i][j] == 1)
                {
                    for(int k = 0; k < 2; k++)
                    {
                        X = i + dir[k][0];
                        Y = j + dir[k][1];

                        if(X < m && Y < n && grid[X][Y] == 1)
                            Union(i * n + j, X * n + Y);
                    }
                }
                
            }
        }

        int ans = 0;
        for(int i = 0; i < m ; i++)
        {
            for(int j = 0; j < n; j++)
            {
                int cur = i * n + j;
                if(grid[i][j] == 1 && !IsConnected(cur, 0) && Find(cur) == cur)
                    ans += size[cur];
            }
        }
        return ans;
    }
};
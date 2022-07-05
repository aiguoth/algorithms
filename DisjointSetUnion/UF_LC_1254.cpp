/*
    https://leetcode.cn/problems/number-of-closed-islands/
    2022-06-20
*/

#include <vector>
#include <unordered_set>
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

    bool IsConnected(int x, int y)
    {
        return Find(x) == Find(y);
    }

    int closedIsland(vector<vector<int>>& grid) {
        
        int n = grid.size(), m = grid[0].size();

        parent.resize(n * m);
        rank.resize(n * m, 0);

        int t;
        for(int i = 0; i < n; i++)
        {
            for(int j = 0; j < m; j++)
            {   
                t =  i * m + j;  
                if(i == 0 || j == 0 || i == n - 1 || j == m - 1)
                    parent[t] = 0;
                else
                    parent[t] =t;
            }
        }
        static const int dir[2][2] = {{1, 0}, {0, 1}};
        int x, y;
        for(int i = 0; i < n; i++)
        {
            for(int j = 0; j < m; j++)
            {
                if(grid[i][j] == 0)
                {
                    for(int k = 0; k < 2; k++)
                    {
                        x = i + dir[k][0];
                        y = j + dir[k][1];
                        if(x < n && y < m && grid[x][y] == 0)
                            Union(i * m + j, x * m + y);
                    }
                }
            }
        }

        unordered_set<int> s;
        int ans = 0;
        for(int i = 1; i < n - 1; i++)
        {
            for(int j = 0; j < m - 1; j++)
            {
                t = Find(i * m + j);
                if(grid[i][j] == 0 && s.count(t) == 0 && !IsConnected(t,0))
                {
                    s.insert(t);
                    ans++;
                }
            }
        }
        return ans;
    }
};
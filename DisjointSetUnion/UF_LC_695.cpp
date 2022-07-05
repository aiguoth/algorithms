/*
    https://leetcode.cn/problems/ZL6zAn/
    2022-06-11
*/

#include <vector>
using namespace std;

class Solution {
public:

    vector<int> parent;
    vector<int> size; // 记录面积 只有 x == parent[x] 时 size[x]的值是准确的
    
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

    int maxAreaOfIsland(vector<vector<int>>& grid) {

        int m = grid.size(), n = grid[0].size();
        parent.resize(m * n);
        size.resize(m * n);
        for(int i = 0; i < m * n; i++)
        {
             parent[i] = i;
             size[i] = 1;
        }   

        // 要么往右，要么往下，没必要考虑向上和向左
        const int dir[2][2] = {{1, 0}, {0, 1}};
        for(int i = 0; i < m; i++)
        {
            for(int j = 0; j < n; j++)
            {
                if(grid[i][j] == 1)
                {
                    for(int k = 0; k < 2; k++)
                    {
                        int X = i + dir[k][0];
                        int Y = j + dir[k][1];

                        if(X < m && Y < n && grid[X][Y] == 1)
                        {
                            Union(i * n + j, X * n + Y);
                        }
                    }
                }
            }
        }

        int ans = 0;
        for(int i = 0; i < m; i++)
        {
            for(int j = 0; j < n; j++)
            {
                int x = i * n + j;
                if(grid[i][j] == 1 && x == parent[x])
                    ans = max(ans, size[x]);
            }
        }
        return ans;
    }
};
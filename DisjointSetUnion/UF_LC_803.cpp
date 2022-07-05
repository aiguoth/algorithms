/*
    https://leetcode.cn/problems/bricks-falling-when-hit/
    2022-07-05
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
    vector<vector<int>> gridBak;
    vector<int> hitBricks(vector<vector<int>>& grid, vector<vector<int>>& hits) {
    
        int m = grid.size(), n = grid[0].size();
        parent.resize(m * n + 1);
        size.resize(m * n + 1, 1);
        size[m * n] = 0;
        for(int i = 0; i <= m * n; i++)
            parent[i] = i;

        gridBak = grid;     // 备份原grid
        for(auto& hit : hits)
            grid[hit[0]][hit[1]] = 0;  // 将要hit的都置0，将所有hit是的砖块都敲掉，之后倒序依次合并，敲掉的砖块 = 将当前砖块合并的数量 - 合并之前的数量。

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
        
        for(int i = 0; i < n; i++)
            if(grid[0][i] == 1)
                Union(i, m * n);
        
        vector<int> ans(hits.size(), 0);

        static const int d[4][2] = {{0,1}, {0, -1}, {1, 0}, {-1, 0}};
        int prev, next, x, y;
        
        prev = size[Find(m * n)];   // 记录前后两次的size大小。
        for(int i = hits.size() - 1; i >= 0; i--)   // 倒序遍历
        {
            x = hits[i][0], y = hits[i][1];
            if(gridBak[x][y] == 0)  // 如果原grid[i][j]为 0 则 continue
                continue;
            grid[x][y] = 1;
            for(int k = 0; k < 4; k++)  // 遍历四个方向
            {
                X = x + d[k][0];
                Y = y + d[k][1];

                if(X == -1 && Y >= 0 && Y < n ) //  如果与上方(稳定)相连则合并
                    Union(x * n + y, m * n);
                else if(X >= 0 && X < m && Y >= 0 && Y < n && grid[X][Y] == 1)
                    Union(x * n + y, X * n + Y);
        
            }

            next = size[Find(m * n)];   // 记录当前hits[i] 合并之后的大小，除去本身，即 next - prev - 1
            ans[i] = max(0, next - prev - 1);
            prev = next;                // 依次迭代
        }

        return ans;
    }
};
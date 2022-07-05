/*
    https://leetcode.cn/problems/making-a-large-island/
    2022-06-14
*/
#include <vector>
#include <unordered_set>
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
        if(X == Y)return;

        if(size[X] < size[Y])
        {
            parent[X] = Y;
            size[Y] += size[X];
        }else{
            parent[Y] = X;
            size[X] += size[Y];
        }
    }

    int largestIsland(vector<vector<int>>& grid) {

        int n = grid.size();
        
        parent.resize(n * n);
        size.resize(n * n, 1);
        for(int i = 0; i < n * n; i++)
            parent[i] = i;

        static const int dir[2][2] = {{1, 0}, {0, 1}}; 
        int X, Y;
        for(int i = 0; i < n; i++)
        {
            for(int j = 0; j < n; j++)
            {
                if(grid[i][j] == 1)
                {
                    for(int k = 0; k < 2; k++)
                    {
                        X = i + dir[k][0];
                        Y = j + dir[k][1];
                        if(X < n && Y < n && grid[X][Y] == 1)
                            Union(i * n + j, X * n + Y);
                    }
                    
                }
            }
        }

        // maxArea = *max_element(size.begin(), size.end());
        // 可使用 *max_element 代替，size 的最大值一定是最大的面积，因为合并是单调增的过程。
        int maxArea = 0;
        for(int i = 0; i < n * n; i++)
        {
            if(grid[i % n][i % n] == 1&& i == parent[i])
                maxArea = max(maxArea, size[i]);
        }
        

        static const int d[4][2] = {{0, -1}, {-1, 0}, {0, 1}, {1, 0}};

        int tempArea;
        unordered_set<int> s;
        for(int i = 0; i < n; i++)
        {
            for(int j = 0; j < n; j++)
            {
                if(grid[i][j] == 0)
                {
                    tempArea = 1;
                    for(int k = 0; k < 4; k++)
                    {
                        X = i + d[k][0];
                        Y = j + d[k][1];

                        // 通过找 grid[i][j]四个方向的岛屿的面积，当然需要unordered_set去重,防止面积多次计算
                        if(X >= 0 && X < n && Y >= 0 && Y < n && grid[X][Y] == 1)
                        {
                            int t = Find(X * n + Y);
                            if(s.count(t) == 0)
                            {
                                s.insert(t);
                                tempArea += size[t];
                            }
                        }
                    }
                    maxArea = max(maxArea, tempArea);
                    s.clear();  // 需要清空，以便不影响后续的过程
                }
            }
        }
        return maxArea;
    }
};
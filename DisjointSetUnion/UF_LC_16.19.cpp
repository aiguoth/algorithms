/*
    《程序员面试金典（第六版）》中的题目
    https://leetcode.cn/problems/pond-sizes-lcci/
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

    vector<int> pondSizes(vector<vector<int>>& land) {

        int n = land.size(), m = land[0].size();

        parent.resize(n * m);
        size.resize(n * m, 1);
        
        for(int i = 0; i < n * m; i++)
            parent[i] = i;
        
        // 从左往右，从上往下，只需要探索 4个方向即可
        static const int d[4][2] = {{0, 1}, {1, 1}, {1, 0}, {1, -1}};
        int X, Y;
        for(int i = 0; i < n; i++)
        {
            for(int j = 0; j < m; j++)
            {
                if(land[i][j] == 0)
                {
                    for(int k = 0; k < 4; k++)
                    {
                        X = i + d[k][0];
                        Y = j + d[k][1];
                        
                        if( X >= 0 && X < n && Y >= 0 && Y < m && land[X][Y] == 0)
                            Union(i * m + j, X * m + Y);
                    }   
                }
            }
        }

        vector<int> ans;
        unordered_set<int> s;

        for(int i = 0; i < n; i++)
        {
            for(int j = 0; j < m; j++)
            {
                if(land[i][j] == 0)
                {
                    int t = Find(i * m + j);
                    if(s.count(t) == 0)
                    {
                        s.insert(t);
                        ans.push_back(size[t]);
                    }
                }
            }
        }
        sort(ans.begin(), ans.end());
        return ans;
    }
};
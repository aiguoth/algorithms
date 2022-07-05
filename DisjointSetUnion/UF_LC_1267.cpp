/*
    https://leetcode.cn/problems/count-servers-that-communicate/
    2022-06-21
*/

#include <vector>
#include <unordered_set>
using namespace std;
class Solution {
public:

    vector<int> parent;
    vector<int> size;
    int cnt;
    
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
        else{
            parent[Y] = x;
            size[X] += size[Y];
        }
    }

    int countServers(vector<vector<int>>& grid) {

        int m = grid.size(), n = grid[0].size();

        parent.resize(m * n + 1);
        size.resize(m * n + 1, 1);

        int t, cnt = 0;
        vector<vector<int>> a(250 * 250, vector<int>(2, 0));
        for(int i = 0; i < m; i++)
        {
            for(int j = 0; j < n; j++)
            {   
                t = i * n + j;
                if(grid[i][j] == 0)
                    parent[t] = m * n;
                else
                {
                    parent[t] = t;
                    a[cnt++] = {i, j};
                }
            }
        }
        parent[m * n] = m * n;
        for(int i = 0; i < cnt; i++)
        {
            for(int j = i + 1; j < cnt; j++)
            {
                if(a[i][0] == a[j][0] || a[i][1] == a[j][1])
                    Union(a[i][0] * n + a[i][1], a[j][0] * n + a[j][1]);
            }
        }

        unordered_set<int> s;
        int ans = 0;
        for(int i = 0; i < cnt; i++)
        {
            int e = Find(a[i][0] * n + a[i][1]);
            if(s.count(e) == 0 && size[e] > 1)
            {
                ans +=size[e];
                s.insert(e);
            }
        }
        return ans;
    }
};
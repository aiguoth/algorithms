/*
    https://leetcode.cn/problems/possible-bipartition/
    2022-06-09
*/

#include <vector>
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
        else
        {
            parent[Y] = X;
            if(rank[X] == rank[Y])
                rank[X]++;
        }
    }

    bool IsConnected(int x, int y)
    {
        return Find(x) == Find(y);
    }

    // 通俗讲：敌人的敌人就是朋友
    // 二部图 [x, y + n] 或 [x + n, y] 应该是同一集合的。 
    // 将 n * 2 后 [x, y] 中 x 与 y 不能在一组，但可以使得 Union(x, y + n), Union(x + n, y)在一组。
    // 即 x 与 y 不是同一个集合的元素， 通过 + n 操作 模拟 x 与 y 的 敌人（y + n）应该是可以合并的。 
    bool possibleBipartition(int n, vector<vector<int>>& dislikes) {

        int n2 = 2 * n;
        parent.resize(n2 + 1);
        rank.resize(n2 + 1);

        for(int i = 1; i <= n2; i++)
        {
            parent[i] = i;
            rank[i] = 1;
        }

        int m = dislikes.size();
        for(int i = 0; i < m; i++)
        {
            if(IsConnected(dislikes[i][0], dislikes[i][1]))
                return false;
            Union(dislikes[i][0], dislikes[i][1] + n);
            Union(dislikes[i][0] + n, dislikes[i][1]);
        }

        return true;
    }
};
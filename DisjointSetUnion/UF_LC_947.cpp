/*
    https://leetcode.cn/problems/most-stones-removed-with-same-row-or-column/
    将每个连通分量删成一个点，删掉的数量之和便是答案 : n - 连通分量数
    2022-06-20
*/
#include <vector>
using namespace std;

class Solution {
public:
    vector<int> parent;
    vector<int> rank;
    int cnt; // 记录当前连通分量的个数
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
        cnt--;
    }

    int getCnt()
    {
        return this->cnt;
    }

    int removeStones(vector<vector<int>>& stones) {

        int n = stones.size();
        cnt = n;
        parent.resize(n);
        rank.resize(n, 0);
        for(int i = 0; i < n; i++)
            parent[i] = i;

        for(int i = 0; i < n; i++)
        {
            for(int j = i + 1; j < n; j++)
            {
                if(stones[i][0] == stones[j][0] || stones[i][1] == stones[j][1])
                    Union(i, j);
            }
        }
        return n - getCnt();
    }
};
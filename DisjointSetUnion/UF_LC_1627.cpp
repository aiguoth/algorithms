/*
    https://leetcode.cn/problems/graph-connectivity-with-threshold/
    2022-06-27
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
        {
            parent[X] = Y;
        }else{
            parent[Y] = X;
            if(rank[X] == rank[Y])
                rank[X]++;
        }
    }

    bool IsConnected(int x, int y)
    {
        return Find(x) == Find(y);
    }

    vector<bool> areConnected(int n, int threshold, vector<vector<int>>& queries) {

        parent.resize(n + 1);
        rank.resize(n + 1, 0);
        for(int i = 1; i <= n; i++)
            parent[i] = i;
        
        for(int i = threshold + 1; i < n; i++)
        {

            for(int j = i; j <= n; j += i)    // 加上倍数，不用两两求公共因数并判断是否存在大于threshold.
            {
                Union(i, j);
            }
        }

        vector<bool> ans;
        for(auto e : queries)
        {
            if(IsConnected(e[0], e[1]))     // 如果 e[0] 或 e[1] 小于等于 threshold 可以不用判断是否Connected
                ans.push_back(true);
            else
                ans.push_back(false);
        }
        return ans;
    }
};
/*
    https://leetcode.cn/problems/number-of-operations-to-make-network-connected/
    2022-06-07
*/

#include <vector>
using namespace std;

class UF
{
private:
    int *parent;
    int *rank;
    int cnt;

public:
    UF(int n)
    {
        parent = new int[n];
        rank = new int[n];
        cnt = n;

        for(int i = 0; i < n; i++)
        {
            parent[i] = i;
            rank[i] = 1;
        }
    }
    ~UF()
    {
        delete []parent;
        delete []rank;
    }

    int Find(int x)
    {
        if(x!=parent[x])
            parent[x] = Find(parent[x]);
        return parent[x];
    }

    void Union(int x, int y)
    {
        int X = Find(x);
        int Y = Find(y);

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
        return Find(x)==Find(y);
    }

    int GetSetNum()
    {   
        int count = 0;
        for(int i = 0; i < cnt; i++)
        {
            if(i == parent[i])
                count++;
        }
        return count;
    }
};

class Solution {
public:
    int makeConnected(int n, vector<vector<int>>& connections) {

        UF uf(n);
        int cnt = 0;
        for(auto& e : connections)
        {
            if(uf.IsConnected(e[0], e[1]))
                cnt++;
            else
            {
                uf.Union(e[0], e[1]);
            }
        }
        int needEdgeNum = uf.GetSetNum() - 1;
        int diff = needEdgeNum - cnt;
        if(diff > 0)
            return -1;
        
        return needEdgeNum;  
    }
};
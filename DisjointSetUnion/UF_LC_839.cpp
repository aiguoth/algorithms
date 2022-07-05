/*
    https://leetcode.cn/problems/H6lPxb/
    2022-06-14
*/
#include <string>
#include <vector>
using namespace std;

class Solution {
public:

    vector<int> parent;
    vector<int> rank;   // 数量较少，可以不用rank。
    
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

    bool judge(const string& a,const string & b)
    {   
        if(a == b)
            return true;
        int cnt = 0;
        for(int k = 0; k < a.size(); k++)
        {
            if(a[k] != b[k])
            {
                cnt++;
                if(cnt > 2)
                    return false;
            }    
        }
        return cnt <= 2;
    }

    int numSimilarGroups(vector<string>& strs) {

        int n = strs.size();
        parent.resize(n);
        rank.resize(n);
        int ans = n;

        for(int i = 0; i < n; i++)
        {
            parent[i] = i;
            rank[i] = 1;
        }
        
        for(int i = 0; i < n; i++)
        {
            for(int j = i + 1; j < n; j++)
            {
                if(!IsConnected(i, j) && judge(strs[i], strs[j]))
                {
                    Union(i, j);
                    ans--;
                }
            }
        }
        return ans;

    }
};
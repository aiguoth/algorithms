/*
    https://leetcode.cn/problems/count-unreachable-pairs-of-nodes-in-an-undirected-graph/
    2022-06-29
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

    long long countPairs(int n, vector<vector<int>>& edges) {

        parent.resize(n);
        size.resize(n, 1);
        for(int i = 0; i < n; i++)
            parent[i] = i;

        for(auto& e : edges)
            Union(e[0], e[1]);

        unordered_set<int> s;
        vector<int> arr(n, 0);
        int t, index = 0;
        for(int i = 0; i < n; i++)
        {
            t = Find(i);
            if(s.count(t) == 0)
            {   
                arr[index++] = size[t];
                s.insert(t);
            }
        }

        long long ans = 0, temp = n;
        for(int i = 0; i < index; i++)
        {
            ans += (temp - arr[i]) * arr[i];
            temp -= arr[i]; 
        }
        return ans;
    }
};
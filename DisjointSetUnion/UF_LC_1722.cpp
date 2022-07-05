/*
    https://leetcode.cn/problems/minimize-hamming-distance-after-swap-operations/
    2022-06-28
*/
#include <vector>
#include <unordered_map>
#include <unordered_set>
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
        else{
            parent[Y] = X;
            if(rank[X] == rank[Y])
                rank[X]++;
        }
    }

    bool IsConnected(int x, int y)
    {
        return Find(x) == Find(y);
    }

    int minimumHammingDistance(vector<int>& source, vector<int>& target, vector<vector<int>>& allowedSwaps) {

        int n = source.size();
        parent.resize(n);
        rank.resize(n, 0);
        for(int i = 0; i < n; i++)
            parent[i] = i;
        
        for(auto e : allowedSwaps)
            Union(e[0], e[1]);
        
        unordered_map<int, unordered_multiset<int>> um;

        for(int i = 0; i < n; i++)
            um[Find(i)].insert(source[i]);

        int ans = 0;
        for(int i = 0; i < n; i++)
        {
            auto& umSet = um[Find(i)];
            auto t = umSet.find(target[i]);
            
            if(t != umSet.end()) 
                umSet.erase(t);     // 删除迭代器指向的内容，如果直接erase(target[i]), 会将所有的target[i]都删除掉
            else
                ans++;
        
        }
        return ans;
    }
};
/*
    2022-06-10
    将 num[i] 与它的所有大于1的因数合并
    https://leetcode.cn/problems/largest-component-size-by-common-factor/
*/

#include <vector>
#include <unordered_map>
#include <algorithm>
using namespace std;

class Solution {
public:

    vector<int> parent;
    vector<int> rank;
    vector<int> size;

    int Find(int x)
    {
        if(x != parent[x])
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
        {
            parent[X] = Y;
            size[Y] += size[X];
            size[X] = 0;
        }else
        {
            parent[Y] = X;
            size[X] += size[Y];
            size[Y] = 0;

            if(rank[X] == rank[Y])
                rank[X]++;
        }
    }

    int largestComponentSize(vector<int>& nums) 
    {
        int MaxNum = *max_element(nums.begin(), nums.end());

        parent.resize(MaxNum + 1);
        rank.resize(MaxNum + 1);
        size.resize(MaxNum + 1);

        for(int i = 0; i <= MaxNum; i++)
        {
            parent[i] = i;
            rank[i] = 1;
            size[i] = 1;
        }

        for(int& e : nums)
        {
            int sqrtE = sqrt(e);

            for(int i = 1; i <= sqrtE; i++)
            {
                if((e % i) == 0)
                {
                   if(i != 1) // 不能与 1 合并
                        Union(e, i);
                    Union(e, e / i);
                }
            }
        }

        unordered_map<int, int> umap;
        for(int& e : nums)
        {
            umap[Find(e)]++; // 统计各个集合的数量
        }

        int ans = -1;
        for(auto& [key, value] : umap) // C++17
        {
            ans = max(ans, value);
        }
        return ans;
    }
};
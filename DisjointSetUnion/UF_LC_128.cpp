/*
    https://leetcode.cn/problems/longest-consecutive-sequence/
    2022-06-09
*/
#include <map>
#include <vector>
using namespace std;

class Solution {
public:

    map<int, int> parent;
    map<int, int> rank;          // 基于 rank 优化
    map<int, int> size;          // 记录以 i 为根的节点的数量

    int Find(int x)
    {
        if(x != parent[x])
        {
            parent[x] = Find(parent[x]);
        }
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
            size[X] = 0;       // 合并后 需要将数量置 0 
        }
        else
        {
            parent[Y] = X;
            size[X] += size[Y];
            size[Y] = 0;
            if(rank[X] == rank[Y])
                rank[X]++;
        }
    }

    int longestConsecutive(vector<int>& nums) {

        int n = nums.size();
        
        // 初始化
        for(int i = 0; i < n; i++)
        {
            parent[nums[i]] = nums[i];
            rank[nums[i]] = 1;
            size[nums[i]] = 1;
        }

        // 此处将连续区间的数都合并到同一个区间，后续只需要判断区间节点数量即可
        for(int j = 0; j < n; j++)
        {   
            // 如果 nums[j] + 1 也出现在 nums 中则将两个合并
            if(parent.count(nums[j] + 1) != 0)
            {
                Union(nums[j], nums[j] + 1);
            }
        }
        int MaxCnt = 0;
        for(auto [key, cnt] : size)
        {
            MaxCnt = max(MaxCnt, cnt);
        }
        return MaxCnt;

    }
};
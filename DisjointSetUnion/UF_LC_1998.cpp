/*
    https://leetcode.cn/problems/gcd-sort-of-an-array/
    2022-06-12
    hard
*/
#include <cmath>
#include <vector>
#include <algorithm>
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

    bool gcdSort(vector<int>& nums) {

        int maxNum = *max_element(nums.begin(), nums.end());

        parent.resize(maxNum + 1);
        rank.resize(maxNum + 1);

        for(int i = 2; i <= maxNum; i++)
        {
            parent[i] = i;
            rank[i] = 1;
        }

        for(auto& e : nums)
        {
            int sqrtE = sqrt(e);
            for(int i = 1; i <= sqrtE; i++)
            {
                if((e % i) == 0)
                {
                    if(i != 1)
                        Union(e, i);
                    Union(e, e / i);
                }
            }
        }
        
        vector<int> copyNum(nums.begin(), nums.end());
        sort(copyNum.begin(), copyNum.end());
        int n = nums.size();
        for(int i = 0; i < n; i++)
        {
            if(!IsConnected(copyNum[i], nums[i]))
                return false;
        }
        return true;
    }
};
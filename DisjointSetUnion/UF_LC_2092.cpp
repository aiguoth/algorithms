/*
    2022-06-09
    https://leetcode.cn/problems/find-all-people-with-secret/
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
        {
            parent[x] = Find(parent[x]);
        }
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

    static bool cmp(const vector<int> &a, const vector<int>& b)
    {
        return a[2] < b[2];
    }
    
    vector<int> findAllPeople(int n, vector<vector<int>>& meetings, int firstPerson) {
        
        parent.resize(n);
        rank.resize(n);

        for(int i = 0; i < n; i++)
        {
            parent[i] = i;
            rank[i] = 1;
        }

        Union(0, firstPerson);

        // 按照时间 time_i 升序排序
        sort(meetings.begin(), meetings.end(), cmp);

        int m = meetings.size();
        for(int i = 0; i < m;)
        {
            int j = i + 1;
            // 记录 区间[i, j) 左闭右开，这个区间可以秘密是瞬时发生的，因此对该区间进行两次遍历。
            while(j < m && meetings[i][2] == meetings[j][2])
                j++;
            
            // 两位专家 Union 起来，只要一个知晓秘密，另一个也会知晓。
            for(int k = i; k < j; k++)
            {
                Union(meetings[k][0], meetings[k][1]);
            }

            for(int k = i; k < j; k++)
            {   // 如果两位专家都不知晓秘密，那么需要将两位专家的状态还原。
                if(!IsConnected(meetings[k][0], 0))
                {
                    parent[meetings[k][0]] = meetings[k][0];
                    rank[meetings[k][0]] = 1;
                    parent[meetings[k][1]] = meetings[k][1];
                    rank[meetings[k][1]] = 1;
                }
            }
            i = j; // 进入下一个区间的判断
        }

        vector<int> ans;
        for(int i = 0; i < n; i++)
        {
            if(IsConnected(0, i))
                ans.push_back(i);
        }
        return ans;
    }
};
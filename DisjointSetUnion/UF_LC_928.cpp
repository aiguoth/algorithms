/*
    https://leetcode.cn/problems/minimize-malware-spread-ii/
    2022-06-23
*/
#include <vector>
#include <set>
#include <unordered_set>
#include <climits> // INT_MAX
using namespace std;

class Solution {
public:

    vector<int> parent;
    vector<int> size;   // 记录集合元素数量

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
    bool IsConnected(int x, int y)
    {
        return Find(x) == Find(y);
    }

    int minMalwareSpread(vector<vector<int>>& graph, vector<int>& initial) {

        // init()
        int n = graph.size();
        parent.resize(n);
        size.resize(n, 1);
        for(int i = 0; i < n; i++)
            parent[i] = i;

        set<int> uSet;
        for(const int &e : initial)
            uSet.insert(e);

        // 将不在 initial 中的 并且相连的结点 Union 起来
        for(int i = 0; i < n; i++)
        {
            for(int j = i + 1; j < n; j++)
            {
                if(graph[i][j] == 1 && uSet.count(i) == 0 && uSet.count(j) == 0)
                    Union(i, j);
            }
        }
        
        // 或者 ans = n + 1; 亦或着比 n 大即可
        int ans = INT_MAX, index = *uSet.begin();
        for(int s : uSet)   // 去除当前的 s 
        {
            vector<int> newParent(parent); // 备份不在initail的结点的parent size 数据
            vector<int> newSize(size);
            int temp = 0;
            for(int i = 0; i < n; i++)
            {
                for(int j = i + 1; j < n; j++)
                {
                    if(graph[i][j] == 1 && i != s && j != s) // 此时将除了 s 之外的结点 Union, 以此模拟删除s的效果。
                        Union(i, j);
                }
            }

            unordered_set<int> Set;
            int t;
            for(int ss : uSet) // 统计 感染数量
            {   
                t = Find(ss);
                if(s != ss && Set.count(t) == 0)
                {
                    temp += size[t];
                    Set.insert(t);
                }
            }
            if(ans > temp)  // 求最小的感染数量所对应的索引
            {
                ans = temp;
                index = s;
            }

            newParent.swap(parent); // 恢复之前 parent size 数据， 进入下一轮模拟
            newSize.swap(size);
        }
        return index;
    }
};
/*
    https://leetcode.cn/problems/couples-holding-hands/
    ( n 对情侣数量 - 集合数量) 因 2 <= n <= 30 故没使用 rank
    2022-06-08
*/

#include <vector>
using namespace std;

class Solution {
public:

    vector<int> parent;

    int find(int x)
    {
        if(x != parent[x])
        {
            parent[x] = find(parent[x]);
        }
        return parent[x];
    }

    void Union(int x, int y)
    {
        int X = find(x);
        int Y = find(y);

        if(X != Y)
            parent[X] = Y;
    }

    int minSwapsCouples(vector<int>& row) {

        int n2 = row.size(), n = n2 / 2;
        parent.resize(n2 / 2);

        for(int i = 0; i < n; i++)
            parent[i] = i;

        /* 
            如果 x == y 则 第 j 对 情侣 无需交换， 否则 Union(x, y)
            需要交换的情侣数量 = (n 对情侣的数量 - （x == parent[x]的数量)
        */
        for(int j = 0; j < n2; j += 2)
        {
            int x = row[j] / 2;
            int y = row[j + 1] / 2;
            Union(x, y);
        }

        int cnt = 0;
        for(int k = 0; k < n; k++)
        {
            if(k == parent[k])
                cnt++;
        }
        return n - cnt;
    }
};
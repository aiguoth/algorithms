/*
    https://leetcode.cn/problems/satisfiability-of-equality-equations/
    2022-06-11
*/

#include <vector>
#include <string>
using namespace std;

class Solution {
public:

    vector<int> ch;

    int Find(int x)
    {
        if(x != ch[x])
            ch[x] = Find(ch[x]);
        return ch[x];
    }

    void Union(int x, int y)
    {
        ch[Find(x)] = Find(y);
    }

    bool IsConnected(int x, int y)
    {
        return Find(x) == Find(y);
    }

    bool equationsPossible(vector<string>& equations) {

        int n = equations.size();

        ch.resize(26);
        for(int i = 0; i < 26; i++)
            ch[i] = i;

        for(int j = 0; j < n; j++)
        {
            int a = equations[j][0] - 'a', b = equations[j][3] - 'a';
            if(equations[j][1] == '=')
                Union(a, b);
        }
        for(int j = 0; j < n; j++)
        {
            int a = equations[j][0] - 'a', b = equations[j][3] - 'a';
            if(equations[j][1] != '=')
            {
                if(IsConnected(a, b))
                    return false;
            }
        }
        return true;
    }
};
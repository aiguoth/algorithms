/*
    https://leetcode.cn/problems/minimize-malware-spread/
    2022-06-08
*/

#include <vector>
#include <unordered_set>
using namespace std;

// 最初实现
namespace UF_LC_924_0 {
class UF
{
    private:
        int* parent;
        int* rank;
        int cnt;
    public:
        
        UF(int n)
        {
            parent = new int[n];
            rank = new int[n];
            cnt = n;

            for(int i = 0; i < n; i++)
            {
                parent[i] = i;
                rank[i] = 1;
            }
        }

        ~UF()
        {
            delete []parent;
            delete []rank;
        }

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

        void modify(int x, int value)
        {   
            int X = Find(x);
            parent[X] = value;
        }
};

class Solution {
public:

    int minMalwareSpread(vector<vector<int>>& graph, vector<int>& initial) {

        int n = graph.size();

        sort(initial.begin(), initial.end());

        int minIndex = initial[0];
        int minNum = -1;
        for(int e : initial)
        {
            UF uf(n + 1);
            int M = 0;
            for(int j = 0; j < n; j++)
            {
                for(int k = j + 1; k < n; k++)
                {
                    if(graph[j][k] == 1)
                        uf.Union(j, k);
                }
            }

            // 统计 每个集合的数量 可以通过 基于 size 实现
            for(int E : initial)
            {
                if(e == E)
                    continue;
                uf.modify(E, n); 
            }

            for(int i = 0; i < n; i++)
            {
                if(uf.Find(i) != n)
                    M++;
            }

            if(M > minNum)
            {
                minNum = M;
                minIndex = e;
            }
        }
        return minIndex;
    }
};
}

// 实现方法 2
namespace UF_LC_924_1 {
class UF
{
    private:
        int* parent;
        int* rank;
        int* size;
        int cnt;
    public:
        
        UF(int n)
        {
            parent = new int[n];
            rank = new int[n];
            size = new int[n];
            cnt = n;

            for(int i = 0; i < n; i++)
            {
                parent[i] = i;
                rank[i] = 1;
                size[i] = 1;
            }
        }

        ~UF()
        {
            delete []parent;
            delete []rank;
            delete []size;
        }

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

        int GetSetNum(int x)
        {
            return size[x];
        }
};

class Solution {
public:

    int minMalwareSpread(vector<vector<int>>& graph, vector<int>& initial) {

        int n = graph.size();

        sort(initial.begin(), initial.end());

        int minIndex = initial[0];
        int minNum = n + 1;
        for(int e : initial)
        {
            UF uf(n);
            int M = 0;
            for(int j = 0; j < n; j++)
            {
                for(int k = j + 1; k < n; k++)
                {
                    if(graph[j][k] == 1)
                        uf.Union(j, k);
                }
            }

            unordered_set<int> s;
            for(int E : initial)
            {
                if(e == E)
                    continue;
                int x = uf.Find(E);
                if(s.count(x))
                    continue;
                    
                M += uf.GetSetNum(x);
                s.insert(x);
            }
            if(M < minNum)
            {
                minNum = M;
                minIndex = e;
            }
        }
        return minIndex;
    }
};
}
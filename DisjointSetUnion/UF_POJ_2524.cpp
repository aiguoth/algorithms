/*
    http://poj.org/problem?id=2524
    2022-06-14
*/
#include <cstdio>
using namespace std;

const int N = 5e4 + 5;
int parent[N], rank[N];

int Find(int x)
{
    if(x != parent[x])
        parent[x] = Find(parent[x]);
    return parent[x];
}

void Union(int x, int y)
{
    int X = Find(x), Y = Find(y);
    // if(X == Y)return;

    if(rank[X] < rank[Y])
    {
        parent[X] = Y;
    }else{
        parent[Y] = X;
        if(rank[X] == rank[Y])
            rank[X]++;
    }
}

bool IsConnected(int x, int y)
{
    return Find(x) == Find(y);
}

int main()
{
    int n, m, x, y, ans;

    int cur = 1;
    while(scanf("%d%d", &n, &m))
    {
        if(n == 0 && m == 0)
            break;
        
        for(int i = 1; i <= n; i++)
        {
            parent[i] = i;
            rank[i] = 1;
        }

        ans = n;

        for(int j = 0; j < m; j++)
        {
            scanf("%d%d", &x, &y);

            if(!IsConnected(x, y))
            {
                Union(x, y);
                ans--;
            }
        }

        printf("Case %d: %d\n", cur++, ans);
    }
}
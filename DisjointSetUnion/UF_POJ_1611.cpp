/*
    http://poj.org/problem?id=1611
    2022-06-14
*/

#include<cstdio>
using namespace std;

const int N = 3e4 + 5;
int parent[N], size[N];

int Find(int x)
{
    if(x != parent[x])
        parent[x] = Find(parent[x]);
    return parent[x];
}

void Union(int x, int y)
{
    int X = Find(x), Y = Find(y);
    if(X == Y)return;

    if(size[X] < size[Y])
    {
        parent[X] = Y;
        size[Y] += size[X];
    }else{
        parent[Y] = X;
        size[X] += size[Y];
    }
}

int main()
{   
    int n, m, k, x, y, ans;

    while(scanf("%d%d",&n, &m))
    {
        if(n == 0 && m == 0)
            break;
        if(m == 0)
        {
            printf("1\n");
            continue;
        }
        
        for(int i = 0; i < n; i++)
        {
            parent[i] = i;
            size[i] = 1;
        }
        for(int j = 0; j < m; j++)
        {
            scanf("%d %d", &k, &x);
            for(int t = 1; t < k; t++)
            {
                scanf("%d", &y);
                Union(x, y);
            }
        }

        printf("%d\n", size[Find(0)]);
    }
    return 0;
}
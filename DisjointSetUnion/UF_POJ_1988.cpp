/*
        http://poj.org/problem?id=1988
        2022-06-11
*/
        
#include <cstdio>
using namespace std;

const int N = 30005;
int parent[N];
int size[N];    // size[i] ：i是根结点，记录集合的数量。
int dx[N];      // Find(x)操作之后 dx[x] 记录的值才是准确的，记录 x 下方元素的个数，Find 过程中分段累加数量。

int Find(int x)
{   
    int parentX = parent[x];
    if(x != parent[x])
    {
        parent[x] = Find(parent[x]);
        dx[x] += dx[parentX]; // 分段累加
    } 
    return parent[x];
}

void Union(int x, int y)
{
    int X = Find(x), Y = Find(y);

    parent[X] = Y;
    dx[X] = size[Y];   // 记录 X - Y 这段区间的数量。
    size[Y] += size[X];
}

int main()
{   
    for(int i = 1; i <= 30000; i++)
    {
        parent[i] = i;
        size[i] = 1;
        dx[i] = 0;
    }

    int p, x, y;
    scanf("%d\n", &p);
    char ch;
    while(p--)
    {
        scanf("%c", &ch);

        if(ch == 'M')
        {
            scanf("%d%d\n", &x, &y);
            Union(x, y);
        }
        else
        {
            scanf("%d\n", &x);
            int _ = Find(x);     // 只有 Find 之后， dx记录的值才是准确的。
            printf("%d\n", dx[x]);
        }
    }

    return 0;
}
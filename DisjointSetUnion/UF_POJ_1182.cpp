/*
    http://poj.org/problem?id=1182
    2022-06-11
*/

#include<cstdio>
using namespace std;

const int N = 5e4+5;
int parent[N], diff[N];

int Find(int x)
{
    int parentX = parent[x];
    if(x != parent[x])
    {
        parent[x] = Find(parent[x]);
        diff[x] += diff[parentX];
        diff[x] %= 3;
    }
    return parent[x];
}

int main()
{   
    int n, k;
    scanf("%d %d", &n, &k);
    if(k == 0)
        printf("0\n");
    
    for(int i = 1; i <= n; i++)
    {
        parent[i] = i;
        diff[i] = 0;
    }

    int d, x, y, cnt = 0;
    while(k--)
    {
        scanf("%d %d %d\n",&d, &x, &y);

        if((x > n || y > n) || (d == 2 && x == y))
            cnt++;
        else
        {
            int X = Find(x), Y = Find(y);

            if(d == 2)
            {
                if(X == Y)
                {
                    if((diff[x] - diff[y] + 3) % 3 != 1)
                        cnt++;
                }
                else
                {
                    parent[X] = Y;
                    diff[X] = (diff[y] - diff[x] + 3 + 1) % 3;
                }
            }
            else
            {
                if(X == Y)
                {
                    if((diff[x] - diff[y] + 3) % 3 != 0)
                        cnt++;
                }else
                {
                    parent[X] = Y;
                    diff[X] = (diff[y] -  diff[x] + 3) % 3;
                }
            }
        }
    }
    printf("%d\n", cnt);
    return 0;
}
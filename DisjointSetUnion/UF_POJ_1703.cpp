/*
    http://poj.org/problem?id=1703

    提交时，若64行代码为 scanf("%c%d%d",...) 报 Time Limit Exceeded.
    若改为 65行 scanf(" %c%d%d", ...) 则正常 AC.

    原因:
        scanf() 读取单个字符时，如果前面也使用scanf,可能会读入换行符，导致读取字符不是目标字符。
        例如 本文件的56行 scanf 中有 "\n" 换行符。导致 64行代码[注释部分]读入的ch是换行符。导致程序没能AC。
        
        scanf("%c", &ch); 程序不会忽视输入按下的回车键，而认为回车键是有效操作而继续响应。
        scanf(" %c", &ch); 在 "%c"之前的空格会通知scanf忽视前面的空行，等待一个非空行元素读入，因此避免上述问题。

    2022-06-11
*/

#include<cstdio>
#include<cstring>
using namespace std;

const int N = 2e5 + 2;

int parent[N];
int rank[N];

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

int main()
{
    int t, n, m, x, y, X, Y;
    char ch;
    scanf("%d", &t);
    while(t--)
    {
        scanf("%d%d\n",&n, &m);

        memset(rank, 0, sizeof(int) * 2 * n + 1);
        for(int i = 1; i <= 2 * n; i++)
            parent[i] = i;

        while(m--)
        {
            // scanf("%c%d%d", &ch, &x, &y) 报 Time Limit Exceeded.
            scanf(" %c%d%d", &ch, &x, &y); // AC
            
            X = Find(x), Y = Find(y);

            if(ch == 'D')
            {
                Union(x, y + n);
                Union(x + n, y);
            }
            else
            {
                if(X == Find(y + n) || Find(x + n) == Y)
                    printf("In different gangs.\n");
                else if(X == Y || Find(x + n) == Find(y + n))
                    printf("In the same gang.\n");
                else
                    printf("Not sure yet.\n");
            }

        }
    }
    return 0;
}
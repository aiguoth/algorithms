/*
                  Disjoint Set Union
        基于 非递归的路径压缩 + 按 size 合并 的 并查集实现
    
            created by aiguoth on 2022-06-06
*/

#ifndef DISJOINTSETUNION_SIZE_H
#define DISJOINTSETUNION_SIZE_H

namespace DisjointSetUnion
{
    class UF_Size
    {
        public:
            UF_Size(int cnt);
            ~UF_Size();
            int Find(int x);
            void Union(int x, int y);
            bool IsConnect(int x, int y);

        private:
            int *parent;
            int *size;
            int count;
    };
    
    UF_Size::UF_Size(int cnt)
    {
        parent = new int[cnt];
        size = new int[cnt];
        count = cnt;

        for(int i = 0; i < cnt; i++)
        {
            parent[i] = i;
            size[i] = 1;
        }
    }

    UF_Size::~UF_Size()
    {
        delete []parent;
        delete []size;
    }

    // 不同于 DisjointSetUnion_Rank 中的 Find 方法，后者通过递归将路径上的节点的parent都修改为根结点。
    // 本方法 减少层数的访问，以便达提高 Find 的效率。
    int UF_Size::Find(int x)
    {
        while ( x != parent[x] )
        {
            // 路径压缩, 下次查找时, 树的层数减少了。
            parent[x] = parent[parent[x]];
            x = parent[x];
        }

        return x;
    }

    void UF_Size::Union(int x, int y)
    {
        int xRoot = Find(x);
        int yRoot = Find(y);

        if(xRoot == yRoot)
        {
            return;
        }

        if(size[xRoot] <= size[yRoot])
        {
            parent[xRoot] = yRoot;
            size[yRoot] += size[xRoot];
        }
        else
        {
            parent[yRoot] = xRoot;
            size[xRoot] += size[yRoot]; 
        }
    }

    bool UF_Size::IsConnect(int x, int y)
    {
        return Find(x) == Find(y);
    }
}
#endif // DISJOINTSETUNION_SIZE_H
/*
                  Disjoint Set Union
        基于 递归的路径压缩 + 按 rank 合并 的 并查集实现
    
            created by aiguoth on 2022-06-06
*/

#ifndef DISJOINTSETUNION_RANK_H
#define DISJOINTSETUNION_RANK_H

namespace DisjointSetUnion
{
    class UF_Rank
    {
        public:
            UF_Rank(int cnt);
            ~UF_Rank();
            int Find(int x);
            void Union(int x, int y);
            bool IsConnected(int x, int y);
        
        private:
            int *parent;
            int *rank;
            int count;
    };

    UF_Rank::UF_Rank(int cnt)
    {
        parent = new int [cnt];
        rank = new int [cnt];
        count = cnt;

        for(int i = 0; i < cnt; ++i)
        {
            parent[i] = i;
            rank[i] = 1;
        }
    }

    UF_Rank::~UF_Rank()
    {
        delete []parent;
        delete []rank;
    }

    // 基于递归的路径压缩, 将路径上节点的parent都修改成根节点
    int UF_Rank::Find(int x)
    {
        if(x != parent[x])
        {
            parent[x] = Find(parent[x]);
        }
        return parent[x];
    }

    // 基于 rank 的合并优化
    void UF_Rank::Union(int x, int y)
    {
        int xRoot = Find(x);
        int yRoot = Find(y);

        if(xRoot == yRoot)
        {
            return;
        }

        if(rank[xRoot] < rank[yRoot])
        {
            parent[xRoot] = yRoot;
        }
        else
        {
            parent[yRoot] = xRoot;
            
            if(rank[xRoot] == rank[yRoot])
            {
                rank[xRoot]++;
            }            
        }
    }

    bool UF_Rank::IsConnected(int x, int y)
    {
        return Find(x) == Find(y);
    }
}
#endif // DISJOINTSETUNION_SIZE_H
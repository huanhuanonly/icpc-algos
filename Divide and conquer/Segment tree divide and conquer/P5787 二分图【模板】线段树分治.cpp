/**
 * => P5787 二分图 /【模板】线段树分治 ( @c 提高+/省选− )
 *
 * -> https://www.luogu.com.cn/problem/P5787
 *
 * Submissions ~> https://www.luogu.com.cn/record/161468390 By huanhuanonly
 *
 * @b Segment-tree-divide-and-conquer
 * @b Extended-domain-disjoint-set-with-rollback
 * @b Bipartite-graph
 *
 * ----June 07, 2024 [00h:42m:18s]----
*/

#include <bits/stdc++.h>

using uint    = unsigned int;
using llong   = long long int;
using ullong  = unsigned long long int;
using ldouble = long double;

class DisjointSet
{
public:
    struct node
    {
        int fa;
        int rank;
    };

    std::vector<node> tree;

    std::stack<std::pair<int&, int>, std::vector<std::pair<int&, int>>> ver_fa, ver_rank;

    explicit DisjointSet(std::size_t n)
        : tree(n)
    {
        for (int i = 0; i < n; ++i)
        {
            tree[i].fa = i;
            tree[i].rank = 1;
        }
    }

    int find(int u) const
    {
        return is_root(u) ? u : find(tree[u].fa);
    }

    void merge(int u, int v)
    {
        int fu = find(u), fv = find(v);

        if (tree[fu].rank > tree[fv].rank)
        {
            ver_fa.push({tree[fv].fa, tree[fv].fa});
            tree[fv].fa = fu;
        }
        else
        {
            ver_fa.push({tree[fu].fa, tree[fu].fa});
            tree[fu].fa = fv;
        }

        ver_rank.push({tree[fv].rank, tree[fv].rank});
        if (tree[fu].rank == tree[fv].rank)
        {
            ++tree[fv].rank;
        }
    }

    bool is_root(int u) const
    {
        return tree[u].fa == u;
    }

    bool is_same_root(int u, int v) const
    {
        return find(u) == find(v);
    }

    void undo()
    {
        if (not ver_fa.empty())
        {
            ver_fa.top().first = ver_fa.top().second;
            ver_rank.top().first = ver_rank.top().second;

            ver_fa.pop();
            ver_rank.pop();
        }
    }
};

class SegmentTree
{
public:

    std::vector<std::vector<std::pair<int, int>>> tree;
    int n;

    explicit SegmentTree(int __size, int __n)
        : tree(__size << 2), n(__n) { }

    static constexpr int ls(int p) { return p << 1; }
    static constexpr int rs(int p) { return p << 1 | 1; }

    void update(int p, int l, int r, int x, int y, const std::pair<int, int>& value)
    {
        if (x <= l and r <= y)
        {
            tree[p].push_back(value);
            return;
        }

        int mid = l + r >> 1;

        if (x <= mid)
            update(ls(p), l, mid, x, y, value);
        if (y > mid)
            update(rs(p), mid + 1, r, x, y, value);
    }


    void dfs(int p, int l, int r, DisjointSet& ds)
    {
        bool can = true;

        int cnt = 0;

        for (const auto& [u, v] : tree[p])
        {
            if (ds.is_same_root(u, v))
                can = false;
            else
            {
                ++cnt;
                ds.merge(u, n + v);
                ds.merge(v, n + u);
            }
        }

        if (can)
        {
            if (l == r)
            {
                std::cout << "Yes\n";
            }
            else
            {
                int mid = l + r >> 1;
                dfs(ls(p), l, mid, ds);
                dfs(rs(p), mid + 1, r, ds);
            }
        }
        else for (int i = l; i <= r; ++i)
        {
            std::cout << "No\n";
        }

        while (cnt--)
        {
            ds.undo();
            ds.undo();
        }
    }
};

int main(void)
{
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr), std::cout.tie(nullptr);

#ifdef __localhost
    ::freopen("in", "r", stdin);
    ::freopen("out", "w", stdout);
#endif

    int n, m, k;
    std::cin >> n >> m >> k;

    DisjointSet ds(1 + n + n);

    SegmentTree seg(k, n);

    for (int i = 0; i < m; ++i)
    {
        int x, y, l, r;
        std::cin >> x >> y >> l >> r;

        if (l == r)
            continue;

        ++l;

        seg.update(1, 1, k, l, r, std::make_pair(x, y));
    }

    seg.dfs(1, 1, k, ds);

    return 0;
}
/**
 * Educational Codeforces Round 146 (Rated for Div. 2)
 *
 * => F. Communication Towers ( @c 2700 )
 *
 * -> https://codeforces.com/contest/1814/problem/F
 *
 * Submissions ~> https://codeforces.com/contest/1814/submission/264606766 By huanhuanonly
 *
 * @b Segment-tree-divide-and-conquer
 * @b Disjoint-set-with-rollback ( @a with-lazy-propagation )
 *
 * ----June 07, 2024 [22h:25m:06s]----
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
    std::vector<int>  lazy;

    std::stack<std::pair<int, int>, std::vector<std::pair<int, int>>> ver_fa, ver_rank;

    explicit DisjointSet(std::size_t n)
        : tree(n), lazy(n)
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
            ver_fa.push({fv, tree[fv].fa});
            tree[fv].fa = fu;
            lazy[fv] -= lazy[fu];
        }
        else
        {
            ver_fa.push({fu, tree[fu].fa});
            tree[fu].fa = fv;
            lazy[fu] -= lazy[fv];
        }

        ver_rank.push({fv, tree[fv].rank});
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
            lazy[ver_fa.top().second] += lazy[find(ver_fa.top().first)];

            tree[ver_fa.top().first].fa = ver_fa.top().second;
            tree[ver_rank.top().first].rank = ver_rank.top().second;

            ver_fa.pop();
            ver_rank.pop();
        }
    }

    void add(int u, int value = 1)
    {
        lazy[find(u)] += value;
    }
};

class SegmentTree
{
public:

    std::vector<std::vector<int>> tree;

    explicit SegmentTree(int __n)
        : tree(__n << 2), vis(__n + 1) { }

    static constexpr int ls(int p) { return p << 1; }
    static constexpr int rs(int p) { return p << 1 | 1; }

    void update(int p, int l, int r, int x, int y, int value)
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

    std::vector<int> vis;

    void dfs(int p, int l, int r, const std::vector<std::vector<int>>& e, DisjointSet& ds)
    {
        int cnt = 0;

        for (const auto& i : tree[p])
            ++vis[i];

        for (const auto& i : tree[p])
        {
            for (const auto& j : e[i])
            {
                if (vis[j] and not ds.is_same_root(i, j))
                {
                    ds.merge(i, j);
                    ++cnt;
                }
            }
        }

        if (l != r)
        {
            int mid = l + r >> 1;
            dfs(ls(p), l, mid, e, ds);
            dfs(rs(p), mid + 1, r, e, ds);
        }
        else
        {
            ds.add(1);
        }

        for (const auto& i : tree[p])
            --vis[i];

        while (cnt--)
        {
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

    int n, m;
    std::cin >> n >> m;

    constexpr int N = 2e5 + 1;

    SegmentTree seg(N);

    for (int i = 1; i <= n; ++i)
    {
        int l, r;
        std::cin >> l >> r;

        seg.update(1, 1, N, l, r, i);
    }

    std::vector<std::vector<int>> e(n + 1);

    for (int i = 1; i <= m; ++i)
    {
        int u, v;
        std::cin >> u >> v;

        e[u].push_back(v);
        e[v].push_back(u);
    }

    DisjointSet ds(n + 1);

    seg.dfs(1, 1, N, e, ds);

    for (int i = 1; i <= n; ++i)
        if (ds.lazy[i])
            std::cout << i << ' ';

    return 0;
}
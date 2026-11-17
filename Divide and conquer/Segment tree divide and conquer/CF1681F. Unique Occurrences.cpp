/**
 * Educational Codeforces Round 129 (Rated for Div. 2)
 *
 * => F. Unique Occurrences ( @c 2300 )
 *
 * -> https://codeforces.com/contest/1681/problem/F
 *
 * Submissions ~> https://codeforces.com/contest/1681/submission/265065816 By huanhuanonly
 *
 * @b Segment-tree-divide-and-conquer
 * @b Disjoint-set-with-rollback
 *
 * ----June 10, 2024 [21h:55m:17s]----
*/

#include <bits/stdc++.h>

using uint    = unsigned int;
using llong   = long long int;
using ullong  = unsigned long long int;
using ldouble = long double;

// rank as size
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

            ver_rank.push({tree[fu].rank, tree[fu].rank});
            tree[fu].rank += tree[fv].rank;
        }
        else
        {
            ver_fa.push({tree[fu].fa, tree[fu].fa});
            tree[fu].fa = fv;

            ver_rank.push({tree[fv].rank, tree[fv].rank});
            tree[fv].rank += tree[fu].rank;
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

    SegmentTree(int n) : tree(n << 2) { }

    static constexpr int ls(int p) { return p << 1; }
    static constexpr int rs(int p) { return p << 1 | 1; }

    void update(int p, int l, int r, int x, int y, const std::pair<int, int>& v)
    {
        if (x <= l and r <= y)
        {
            tree[p].push_back(v);
            return;
        }

        int mid = l + r >> 1;

        if (x <= mid)
            update(ls(p), l, mid, x, y, v);
        if (y > mid)
            update(rs(p), mid + 1, r, x, y, v);
    }

    ullong dfs(int p, int l, int r, DisjointSet& ds, const auto& c)
    {
        int cnt = 0;

        for (const auto& [u, v] : tree[p])
        {
            if (ds.is_same_root(u, v) == false)
            {
                ds.merge(u, v);
                ++cnt;
            }
        }

        ullong sum = 0;

        if (l == r)
        {
            for (const auto& [u, v] : c[l])
                sum += static_cast<ullong>(ds.tree[ds.find(u)].rank) * ds.tree[ds.find(v)].rank;
        }
        else
        {
            int mid = l + r >> 1;

            sum += dfs(ls(p), l, mid, ds, c);
            sum += dfs(rs(p), mid + 1, r, ds, c);
        }

        while (cnt--)
            ds.undo();

        return sum;
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

    int n;
    std::cin >> n;

    std::vector<std::vector<std::pair<int, int>>> c(n + 1);

    SegmentTree seg(n);

    for (int i = 1; i <= n - 1; ++i)
    {
        int u, v, x;
        std::cin >> u >> v >> x;

        c[x].push_back({u, v});

        if (x - 1 >= 1)
            seg.update(1, 1, n, 1, x - 1, {u, v});
        if (x + 1 <= n)
            seg.update(1, 1, n, x + 1, n, {u, v});
    }

    DisjointSet ds(n + 1);

    std::cout << seg.dfs(1, 1, n, ds, c);

    return 0;
}
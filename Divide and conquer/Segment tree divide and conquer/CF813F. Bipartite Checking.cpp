/**
 * Educational Codeforces Round 22
 *
 * => F. Bipartite Checking ( @c 2500 )
 *
 * -> https://codeforces.com/contest/813/problem/F
 *
 * Submissions ~> https://codeforces.com/contest/813/submission/346645976 By huanhuanonly
 *
 * @b Segment-tree-divide-and-conquer
 * @b Extended-domain-disjoint-set-with-rollback
 * @b Bipartite-graph
 *
 * ----October 30, 2025 [22h:27m:37s]----
*/

#include <bits/stdc++.h>

using int8 = signed char;
using int16 = short;
using int32 = int;
using int64 = long long;

using uint8 = unsigned char;
using uint16 = unsigned short;
using uint32 = unsigned int;
using uint64 = unsigned long long;

#ifdef __GNUC__
using int128 = __int128;
using uint128 = unsigned __int128;
#endif

using real32 = float;
using real64 = double;
using real128 = long double;

class DisjointSet
{
public:

    struct node
    {
        int parent;
        int rank;
    };

    std::vector<node> tree;

    struct item
    {
        std::pair<int&, int> parent;
        std::pair<int&, int> rank;
    };

    std::stack<item, std::vector<item>> history;

    explicit DisjointSet(int n)
        : tree(n)
    {
        for (int i = 0; i < n; ++i)
        {
            tree[i].parent = i;
            tree[i].rank = 1;
        }
    }

    int root(int u)
    {
        for (; tree[u].parent != u; u = tree[u].parent);
        return u;
    }

    void merge(int u, int v)
    {
        u = root(u);
        v = root(v);

        if (tree[u].rank < tree[v].rank)
        {
            std::swap(u, v);
        }

        history.push({{tree[v].parent, tree[v].parent}, {tree[u].rank, tree[u].rank}});

        tree[v].parent = u;

        if (tree[u].rank == tree[v].rank)
        {
            ++tree[u].rank;
        }
    }

    void undo(int cnt = 1)
    {
        for (; cnt; --cnt)
        {
            history.top().parent.first = history.top().parent.second;
            history.top().rank.first = history.top().rank.second;

            history.pop();
        }
    }
};

class SegmentTree
{
public:

    std::vector<std::vector<std::pair<int, int>>> tree;

    explicit SegmentTree(int n) : tree(n << 2) { }

    static int ls(int u)
    {
        return u << 1;
    }

    static int rs(int u)
    {
        return u << 1 | 1;
    }

    void insert(int u, int l, int r, int x, int y, const std::pair<int, int>& edge)
    {
        if (x <= l and r <= y)
        {
            tree[u].push_back(edge);
            return;
        }

        const int mid = l + r >> 1;

        if (x <= mid)
        {
            insert(ls(u), l, mid, x, y, edge);
        }
        if (y > mid)
        {
            insert(rs(u), mid + 1, r, x, y, edge);
        }
    }

    void dfs(int u, int l, int r, int n, DisjointSet& dsu, std::vector<bool>& ans)
    {
        bool yes = true;

        for (int i = 0; i < tree[u].size(); ++i)
        {
            if (dsu.root(tree[u][i].first) != dsu.root(tree[u][i].second))
            {
                dsu.merge(tree[u][i].first, tree[u][i].second + n);
                dsu.merge(tree[u][i].second, tree[u][i].first + n);
            }
            else
            {
                dsu.undo(i * 2);

                yes = false;
                break;
            }
        }

        if (yes)
        {
            if (l == r)
            {
                ans[l] = yes;
            }
            else
            {
                const int mid = l + r >> 1;

                dfs(ls(u), l, mid, n, dsu, ans);
                dfs(rs(u), mid + 1, r, n, dsu, ans);
            }

            dsu.undo(tree[u].size() * 2);
        }
    }
};

int main(void)
{
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr), std::cout.tie(nullptr);

#ifdef __huanhuanonly_localhost
    ::freopen("in", "r", stdin);
    ::freopen("out", "w", stdout);
#endif

    int n, q;
    std::cin >> n >> q;

    DisjointSet dsu(n + n + 1);

    SegmentTree seg(q + 1);

    std::map<std::pair<int, int>, int> prev;

    std::pair<int, int> edge;

    for (int i = 1; i <= q; ++i)
    {
        std::cin >> edge.first >> edge.second;

        if (edge.first > edge.second)
        {
            std::swap(edge.first, edge.second);
        }

        if (auto it = prev.find(edge); it != prev.end())
        {
            seg.insert(1, 1, q, it->second, i - 1, edge);
            prev.erase(it);
        }
        else
        {
            prev[edge] = i;
        }
    }

    for (auto it = prev.begin(); it != prev.end(); ++it)
    {
        seg.insert(1, 1, q, it->second, q, it->first);
    }

    std::vector<bool> ans(q + 1);

    seg.dfs(1, 1, q, n, dsu, ans);

    for (int i = 1; i <= q; ++i)
    {
        if (ans[i])
        {
            std::cout << "YES\n";
        }
        else
        {
            std::cout << "NO\n";
        }
    }

    return 0;
}
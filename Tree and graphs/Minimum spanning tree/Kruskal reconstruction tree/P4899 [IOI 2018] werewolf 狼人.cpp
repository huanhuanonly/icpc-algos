/**
 * => P4899 [IOI 2018] werewolf 狼人 ( @c 省选/NOI- )
 *
 * -> https://www.luogu.com.cn/problem/P4899
 *
 * Submissions ~> https://www.luogu.com.cn/record/282776344 By huanhuanonly
 *
 * @b Kruskal-reconstruction-tree
 * @b Dfs on @a Trees
 * @b Dfs-order
 * @b Binary-lifting
 * @b Persistent-segment-tree
 *
 * ----June 23, 2026 [20h:52m:34s]----
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

#if defined(__SIZEOF_INT128__)
using int128 = __int128;
using uint128 = unsigned __int128;
#endif

using real32 = float;
using real64 = double;

#if defined(__SIZEOF_FLOAT80__)
using real80 = __float80;
#endif

#if defined(__SIZEOF_FLOAT128__)
using real128 = __float128;
#endif

inline namespace huanhuanonly {
    inline namespace data_structure
{
class DisjointSet
{
public:

    using size_type = int;

    explicit
    DisjointSet(size_type __n)
        : _M_parent(__n)
    { reset(); }

    [[nodiscard]] size_type
    find(size_type u)
    { return _M_parent[u] == u ? u : _M_parent[u] = find(_M_parent[u]); }

    bool
    unite(size_type u, size_type v)
    {
        const size_type fu = find(u);
        const size_type fv = find(v);

        if (fu != fv)
        {
            _M_parent[fv] = fu;
            return true;
        }
        else
        {
            return false;
        }
    }

    [[nodiscard]] bool
    connected(size_type u, size_type v)
    { return find(u) == find(v); }

    void
    expand(size_type __n)
    {
        const size_type size = static_cast<size_type>(_M_parent.size());
        _M_parent.resize(size + __n);
        std::iota(_M_parent.begin() + size, _M_parent.end(), size);
    }

    void
    reset()
    { std::iota(_M_parent.begin(), _M_parent.end(), 0); }

    [[nodiscard]] size_type
    size()
    { return static_cast<size_type>(_M_parent.size()); }

private:

    std::vector<size_type> _M_parent;
};
}} // namespace huanhuanonly::data_structure

class PersistentSegmentTree
{
public:

    struct node
    {
        int ls, rs;
        int value;
    };

    std::vector<node> tree;
    std::vector<int> roots;

    explicit PersistentSegmentTree(int n)
        : tree(1), roots(1)
    { tree.reserve(n * 20); }

    int copy_node(int u)
    {
        tree.push_back(tree[u]);
        return tree.size() - 1;
    }

    int copy_root()
    {
        roots.push_back(roots.back());
        return roots.size() - 1;
    }

    void push_up(int u)
    {
        tree[u].value = tree[tree[u].ls].value + tree[tree[u].rs].value;
    }

    int reduce(int u, int v, int l, int r, int x, int y)
    {
        if (x <= l and r <= y)
        {
            return tree[v].value - tree[u].value;
        }

        const int mid = l + r >> 1;

        int sum = 0;

        if (x <= mid)
        {
            sum = reduce(tree[u].ls, tree[v].ls, l, mid, x, y);
        }

        if (y > mid)
        {
            sum += reduce(tree[u].rs, tree[v].rs, mid + 1, r, x, y);
        }

        return sum;
    }

    void add(int& u, int l, int r, int i)
    {
        u = copy_node(u);

        if (l == r)
        {
            ++tree[u].value;
            return;
        }

        const int mid = l + r >> 1;

        if (i <= mid)
        {
            add(tree[u].ls, l, mid, i);
        }
        else
        {
            add(tree[u].rs, mid + 1, r, i);
        }

        push_up(u);
    }
};

int main(void)
{
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);

#ifdef __huanhuanonly_localhost
    ::freopen("in", "r", stdin);
    ::freopen("out", "w", stdout);
#endif

    int n, m, q;
    std::cin >> n >> m >> q;

    std::vector<std::pair<int, int>> e(m);

    for (auto& [u, v] : e)
    {
        std::cin >> u >> v;
        ++u, ++v;

        if (u > v)
        {
            std::swap(u, v);
        }
    }

    DisjointSet dsu1(n + m + 1), dsu2(n + m + 1);
    std::vector<int> weight1(n + m + 1), weight2(n + m + 1);

    std::vector<std::array<int, 2>> bt1(n + m + 1), bt2(n + m + 1);
    std::vector<int> depth1(n + m + 1), depth2(n + m + 1);
    std::vector<int> size1(n + m + 1), size2(n + m + 1);
    std::vector<int> dfn1(n + m + 1), dfn2(n + m + 1);

    PersistentSegmentTree pseg(n + m + 1);

    constexpr int laycnt = 20;
    std::vector<std::array<int, laycnt>> parent1(n + m + 1), parent2(n + m + 1);

    std::ranges::sort(e, std::ranges::greater{}, &std::pair<int, int>::first);

    for (int id = n; const auto& [u, v] : e)
    {
        if (not dsu1.connected(u, v))
        {
            ++id;

            weight1[id] = u - 1;
            bt1[id] = {dsu1.find(u), dsu1.find(v)};
            parent1[dsu1.find(u)][0] = parent1[dsu1.find(v)][0] = id;

            dsu1.unite(id, u);
            dsu1.unite(id, v);
        }
    }

    std::ranges::sort(e, {}, &std::pair<int, int>::second);

    for (int id = n; const auto& [u, v] : e)
    {
        if (not dsu2.connected(u, v))
        {
            ++id;

            weight2[id] = v - 1;
            bt2[id] = {dsu2.find(u), dsu2.find(v)};
            parent2[dsu2.find(u)][0] = parent2[dsu2.find(v)][0] = id;

            dsu2.unite(id, u);
            dsu2.unite(id, v);
        }
    }

    for (int i = 1; i < laycnt; ++i)
    {
        for (int u = 1; u <= n + m; ++u)
        {
            parent1[u][i] = parent1[parent1[u][i - 1]][i - 1];
            parent2[u][i] = parent2[parent2[u][i - 1]][i - 1];
        }
    }

    auto dfs1 = [&, id = 0](auto& self, int u) mutable -> void
    {
        dfn1[u] = ++id;
        size1[u] = 1;

        if (bt1[u][0])
        {
            for (int v : bt1[u])
            {
                depth1[v] = depth1[u] + 1;
                self(self, v);
                size1[u] += size1[v];
            }
        }
    };

    auto dfs2 = [&, id = 0](auto& self, int u) mutable -> void
    {
        dfn2[u] = ++id;
        size2[u] = 1;

        if (bt2[u][0])
        {
            for (int v : bt2[u])
            {
                depth2[v] = depth2[u] + 1;
                self(self, v);
                size2[u] += size2[v];
            }
        }
    };

    dfs1(dfs1, dsu1.find(1));
    dfs2(dfs2, dsu2.find(1));

    auto climb1 = [&](int u, int lower_limit) -> int
    {
        for (int i = laycnt; i--; )
        {
            if (parent1[u][i] and weight1[parent1[u][i]] >= lower_limit)
            {
                u = parent1[u][i];
            }
        }

        return u;
    };

    auto climb2 = [&](int u, int upper_limit) -> int
    {
        for (int i = laycnt; i--; )
        {
            if (parent2[u][i] and weight2[parent2[u][i]] <= upper_limit)
            {
                u = parent2[u][i];
            }
        }

        return u;
    };

    std::vector<std::pair<int, int>> coords(n);

    for (int i = 1; i <= n; ++i)
    {
        coords[i - 1] = {dfn1[i], dfn2[i]};
    }

    std::ranges::sort(coords);

    for (int i = 1, j = 0; i <= n + m; ++i)
    {
        pseg.copy_root();
        for (; j < n and coords[j].first == i; pseg.add(pseg.roots.back(), 1, n + m, coords[j].second), ++j);
    }

    while (q--)
    {
        int s, t, l, r;
        std::cin >> s >> t >> l >> r;

        ++s, ++t;

        s = climb1(s, l);
        t = climb2(t, r);

        if (pseg.reduce(pseg.roots[dfn1[s] - 1], pseg.roots[dfn1[s] + size1[s] - 1], 1, n + m, dfn2[t], dfn2[t] + size2[t] - 1))
        {
            std::cout << "1\n";
        }
        else
        {
            std::cout << "0\n";
        }
    }

    return 0;
}
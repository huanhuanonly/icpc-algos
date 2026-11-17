/**
 * => P3302 [SDOI2013] 森林 ( @c 省选/NOI- )
 *
 * -> https://www.luogu.com.cn/problem/P3302
 *
 * Submissions ~> https://www.luogu.com.cn/record/282869470 By huanhuanonly
 *
 * @b Disjoint-set
 * @b Dsu-on-tree
 * @b Dfs on @a Trees
 * @b LCA ( @a binary-lifting )
 * @b Tree-prefix-sum
 * @b Persistent-segment-tree
 *
 * ----June 24, 2026 [22h:29m:31s]----
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

    struct node
    {
        size_type parent;
        size_type size;
    };

    explicit
    DisjointSet(size_type __n)
        : _M_tree(__n)
    { reset(); }

    [[nodiscard]] size_type
    find(size_type u) const
    { return is_root(u) ? u : find(_M_tree[u].parent); }

    bool
    unite(size_type u, size_type v)
    {
        size_type fu = find(u);
        size_type fv = find(v);

        if (_M_tree[fu].size < _M_tree[fv].size)
        {
            std::swap(fu, fv);
        }

        if (fu != fv)
        {
            _M_tree[fv].parent = fu;
            _M_tree[fu].size += _M_tree[fv].size;
            return true;
        }
        else
        {
            return false;
        }
    }

    [[nodiscard]] bool
    is_root(size_type u) const
    { return _M_tree[u].parent == u; }

    [[nodiscard]] bool
    connected(size_type u, size_type v)
    { return find(u) == find(v); }

    void
    expand(size_type __n)
    {
        const size_type old_size = size();
        _M_tree.resize(old_size + __n);

        for (size_type i = old_size; i < old_size + __n; ++i)
        {
            _M_tree[i].parent = i;
            _M_tree[i].size = 1;
        }
    }

    void
    reset()
    {
        for (size_type i = 0; i < size(); ++i)
        {
            _M_tree[i].parent = i;
            _M_tree[i].size = 1;
        }
    }

    [[nodiscard]] size_type
    size()
    { return static_cast<size_type>(_M_tree.size()); }

    [[nodiscard]] size_type
    component_size(size_type u) const
    { return _M_tree[find(u)].size; }

private:

    std::vector<node> _M_tree;
};
}} // namespace huanhuanonly::data_structure

class PersistentSegmentTree
{
public:

    struct node
    {
        int ls, rs;
        int cnt;
    };

    static inline std::vector<node> tree = std::vector<node>(4e7);

    int root = 0;

    static int create_node()
    {
        static int pos = 0;
        return ++pos;
    }

    static int copy_node(int u)
    {
        const int i = create_node();
        tree[i] = tree[u];
        return i;
    }

    static void push_up(int u)
    {
        tree[u].cnt = tree[tree[u].ls].cnt + tree[tree[u].rs].cnt;
    }

    static void add(int& u, int l, int r, int i)
    {
        u = copy_node(u);

        if (l == r)
        {
            ++tree[u].cnt;
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

    static int reduce(int u, int v, int lca, int parent_lca, int l, int r, int k)
    {
        if (l == r)
        {
            return l;
        }

        const int mid = l + r >> 1;

        if (const int lcnt = tree[tree[u].ls].cnt + tree[tree[v].ls].cnt - tree[tree[lca].ls].cnt - tree[tree[parent_lca].ls].cnt; k <= lcnt)
        {
            return reduce(tree[u].ls, tree[v].ls, tree[lca].ls, tree[parent_lca].ls, l, mid, k);
        }
        else
        {
            return reduce(tree[u].rs, tree[v].rs, tree[lca].rs, tree[parent_lca].rs, mid + 1, r, k - lcnt);
        }
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

    int testcase;
    std::cin >> testcase;

    int n, m, t;
    std::cin >> n >> m >> t;

    std::vector<int> w(n + 1);

    for (int i = 1; i <= n; ++i)
    {
        std::cin >> w[i];
    }

    std::vector<std::vector<int>> e(n + 1);
    DisjointSet dsu(n + 1);

    for (int i = 0; i < m; ++i)
    {
        int u, v;
        std::cin >> u >> v;

        dsu.unite(u, v);

        e[u].push_back(v);
        e[v].push_back(u);
    }

    constexpr int maxw = 1e9;
    constexpr int laycnt = 18;

    std::vector<std::array<int, laycnt>> parent(n + 1);
    std::vector<int> depth(n + 1);
    std::vector<PersistentSegmentTree> psegs(n + 1);

    auto lca = [&](int u, int v) -> int
    {
        if (depth[u] < depth[v])
        {
            std::swap(u, v);
        }

        for (int i = laycnt, diff = depth[u] - depth[v]; i--; )
        {
            if (diff & 1 << i)
            {
                u = parent[u][i];
            }
        }

        if (u == v)
        {
            return u;
        }

        for (int i = laycnt; i--; )
        {
            if (parent[u][i] != parent[v][i])
            {
                u = parent[u][i];
                v = parent[v][i];
            }
        }

        return parent[u][0];
    };

    auto build = [&](const auto& self, int u) -> void
    {
        for (int i = 1; i < laycnt; ++i)
        {
            parent[u][i] = parent[parent[u][i - 1]][i - 1];
        }

        depth[u] = depth[parent[u][0]] + 1;

        psegs[u].root = psegs[parent[u][0]].root;
        PersistentSegmentTree::add(psegs[u].root, 1, maxw, w[u]);

        for (int v : e[u])
        {
            if (v != parent[u][0])
            {
                parent[v][0] = u;
                self(self, v);
            }
        }
    };

    for (int u :
        std::set(
            std::from_range,
            std::views::iota(1, n + 1) |
                std::views::transform([&](int i) -> int { return dsu.find(i); })))
    {
        build(build, u);
    }

    for (int lastans = 0; t--; )
    {
        char opt;
        std::cin >> opt;

        if (opt == 'Q')
        {
            int u, v, k;
            std::cin >> u >> v >> k;

            u ^= lastans;
            v ^= lastans;
            k ^= lastans;

            const int top = lca(u, v);

            lastans = PersistentSegmentTree::reduce(
                psegs[u].root,
                psegs[v].root,
                psegs[top].root,
                psegs[parent[top][0]].root,
                1, maxw,
                k);

            std::cout << lastans << '\n';
        }
        else
        {
            int u, v;
            std::cin >> u >> v;

            u ^= lastans;
            v ^= lastans;

            const int fu = dsu.find(u);

            if (dsu.unite(fu, v))
            {
                e[u].push_back(v);
                e[v].push_back(u);

                if (not dsu.is_root(fu))
                {
                    std::swap(u, v);
                }

                parent[v][0] = u;
                build(build, v);
            }
        }
    }

    return 0;
}
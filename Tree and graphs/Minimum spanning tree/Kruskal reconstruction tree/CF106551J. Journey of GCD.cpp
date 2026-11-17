/**
 * 2026 ICPC Nanchang Invitational and Jiangxi Provincial Collegiate Programming Contest
 *
 * => J. Journey of GCD
 *
 * -> https://codeforces.com/gym/106551/problem/J
 *
 * Submissions ~> https://codeforces.com/gym/106551/submission/389288628 By huanhuanonly
 *
 * @b Kruskal-reconstruction-tree
 * @b LCA ( @a heavy-light-decomposition )
 * @b Number-theory ( @a greatest-common-divisor )
 *
 * ----September 04, 2026 [00h:37m:30s]----
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
    DisjointSet(size_type __n = 0)
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

int main(void)
{
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);

#ifdef __huanhuanonly_localhost
    ::freopen("in", "r", stdin);
    ::freopen("out", "w", stdout);
#endif

    int n, q;
    std::cin >> n >> q;

    constexpr int maxv = 1e6;

    std::vector<int> head(maxv + 1);
    std::vector<int> next(n + 1);

    std::vector<int> w(n + n + 1);

    for (int i = 1; i <= n; ++i)
    {
        std::cin >> w[i];
        next[i] = std::exchange(head[w[i]], i);
    }

    DisjointSet dsu(n + n + 1);

    struct node
    {
        std::array<int, 2> e;

        int parent;
        int size;
        int depth;

        int wson;
        int head;
    };

    std::vector<node> tree(dsu.size());

    std::vector<int> set;
    set.reserve(n);

    for (int id = n, d = maxv; d >= 1; --d)
    {
        set.clear();

        for (int p = 1; d * p <= maxv; ++p)
        {
            for (int i = head[d * p]; i; i = next[i])
            {
                set.push_back(i);
            }
        }

        for (int i = 1; i < set.size(); ++i)
        {
            if (not dsu.connected(set[i - 1], set[i]))
            {
                w[++id] = d;

                tree[id].e = {dsu.find(set[i - 1]), dsu.find(set[i])};

                dsu.unite(id, set[i - 1]);
                dsu.unite(id, set[i]);
            }
        }
    }

    auto build = [&](const auto& self, int u) -> void
    {
        tree[u].size = 1;

        for (const auto& v : tree[u].e)
        {
            if (v)
            {
                tree[v].parent = u;
                tree[v].depth = tree[u].depth + 1;
                self(self, v);
                tree[u].size += tree[v].size;

                if (tree[v].size > tree[tree[u].wson].size)
                {
                    tree[u].wson = v;
                }
            }
        }
    };

    auto build_head = [&](const auto& self, int u, int head) -> void
    {
        tree[u].head = head;

        if (tree[u].wson)
        {
            self(self, tree[u].wson, head);

            for (const auto& v : tree[u].e)
            {
                if (v and v != tree[u].wson)
                {
                    self(self, v, v);
                }
            }
        }
    };

    const auto root = dsu.find(1);

    build(build, root);
    build_head(build_head, root, root);

    auto lca = [&](int u, int v) -> int
    {
        while (tree[u].head != tree[v].head)
        {
            if (tree[tree[u].head].depth > tree[tree[v].head].depth)
            {
                u = tree[tree[u].head].parent;
            }
            else
            {
                v = tree[tree[v].head].parent;
            }
        }

        return tree[u].depth < tree[v].depth ? u : v;
    };

    while (q--)
    {
        int u, v;
        std::cin >> u >> v;

        std::cout << w[lca(u, v)] << '\n';
    }

    return 0;
}
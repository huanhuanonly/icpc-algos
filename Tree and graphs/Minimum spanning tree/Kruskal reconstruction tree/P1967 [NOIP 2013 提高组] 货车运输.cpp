/**
 * => P1967 [NOIP 2013 提高组] 货车运输 ( @c 提高+/省选− )
 *
 * -> https://www.luogu.com.cn/problem/P1967
 *
 * Submissions ~> https://www.luogu.com.cn/record/282180679 By huanhuanonly
 *
 * @b Kruskal-reconstruction-tree
 * @b LCA ( @a binary-lifting )
 *
 * ----June 17, 2026 [22h:04m:27s]----
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

int main(void)
{
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);

#ifdef __huanhuanonly_localhost
    ::freopen("in", "r", stdin);
    ::freopen("out", "w", stdout);
#endif

    int n, m;
    std::cin >> n >> m;

    std::vector<std::tuple<int, int, int>> e(m);

    for (auto& [u, v, w] : e)
    {
        std::cin >> u >> v >> w;
    }

    std::ranges::sort(e, std::ranges::greater{}, [](const auto& t) { return std::get<2>(t); });

    std::vector<std::vector<int>> g(n + m + 1);
    std::vector<int> weight(n + m + 1);
    std::vector<int> depth(n + m + 1);

    DisjointSet dsu(n + m + 1);

    constexpr int laycnt = 15;
    std::vector<std::array<int, laycnt>> parent(dsu.size());

    for (int id = n; const auto& [u, v, w] : e)
    {
        if (not dsu.connected(u, v))
        {
            ++id;

            parent[dsu.find(u)][0] = parent[dsu.find(v)][0] = id;

            dsu.unite(id, u);
            dsu.unite(id, v);

            weight[id] = w;
        }
    }

    std::stack<int, std::vector<int>> stack;

    for (int i = 1; i <= n + m; ++i)
    {
        for (int u = i; u and not depth[u]; stack.push(u), u = parent[u][0]);
        for (; not stack.empty(); depth[stack.top()] = depth[parent[stack.top()][0]] + 1, stack.pop());
    }

    for (int i = 1; i < laycnt; ++i)
    {
        for (int u = 1; u <= n + m; ++u)
        {
            parent[u][i] = parent[parent[u][i - 1]][i - 1];
        }
    }

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

    int q;
    std::cin >> q;

    while (q--)
    {
        int u, v;
        std::cin >> u >> v;

        if (dsu.connected(u, v))
        {
            std::cout << weight[lca(u, v)] << '\n';
        }
        else
        {
            std::cout << "-1\n";
        }
    }

    return 0;
}
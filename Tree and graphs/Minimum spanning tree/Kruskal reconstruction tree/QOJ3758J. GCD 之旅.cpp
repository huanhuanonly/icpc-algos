/**
 * The 2026 ICPC Nanchang Invitational and Jiangxi Provincial Collegiate Programming Contest
 *
 * => J. GCD 之旅
 *
 * -> https://qoj.ac/contest/3758/problem/18281
 *
 * Submissions ~> https://qoj.ac/submission/2846037 By huanhuanonly
 *
 * @b Kruskal-reconstruction-tree
 * @b LCA ( @a binary-lifting )
 * @b Number-theory ( @a greatest-common-divisor )
 *
 * ----September 01, 2026 [11h:22m:49s]----
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

    std::vector<int> w(n + n + 1);

    for (int i = 1; i <= n; ++i)
    {
        std::cin >> w[i];
    }

    std::vector<std::vector<int>> sets(1e6 + 1);

    for (int i = 1; i <= n; ++i)
    {
        for (int d = 1, sq = std::sqrt(w[i]); d <= sq; ++d)
        {
            if (w[i] % d == 0)
            {
                sets[d].push_back(i);
                sets[w[i] / d].push_back(i);
            }
        }
    }

    DisjointSet dsu(n + n + 1);

    constexpr int laycnt = 21;
    std::vector<std::array<int, laycnt>> parent(dsu.size());

    std::vector<int> depth(dsu.size());

    for (int id = n; const auto& [d, set] : sets | std::views::enumerate | std::views::reverse)
    {
        for (int i = 1; i < set.size(); ++i)
        {
            if (not dsu.connected(set[i - 1], set[i]))
            {
                w[++id] = d;

                parent[dsu.find(set[i - 1])][0] = id;
                parent[dsu.find(set[i])][0] = id;

                dsu.unite(id, set[i - 1]);
                dsu.unite(id, set[i]);
            }
        }
    }

    {
        std::stack<int, std::vector<int>> stack;

        for (int i = 1; i <= n; ++i)
        {
            for (int u = i; u and not depth[u]; stack.push(u), u = parent[u][0]);
            for (; not stack.empty(); depth[stack.top()] = depth[parent[stack.top()][0]] + 1, stack.pop());
        }
    }

    for (int i = 1; i < laycnt; ++i)
    {
        for (int u = 1; u < parent.size(); ++u)
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

        for (int i = 0, diff = depth[u] - depth[v]; i < laycnt; ++i)
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

    while (q--)
    {
        int u, v;
        std::cin >> u >> v;

        std::cout << w[lca(u, v)] << '\n';
    }

    return 0;
}
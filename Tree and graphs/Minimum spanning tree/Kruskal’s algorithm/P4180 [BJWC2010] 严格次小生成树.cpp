/**
 * => P4180 [BJWC2010] 严格次小生成树 ( @c 提高+/省选− )
 *
 * -> https://www.luogu.com.cn/problem/P4180
 *
 * Submissions ~> https://www.luogu.com.cn/record/287932521 By huanhuanonly
 *
 * @b Kruskal’s-algorithm
 * @b Dfs on @a Trees
 * @b LCA ( @a binary-lifting )
 * @b Binary-lifting
 *
 * ----July 23, 2026 [02h:35m:36s]----
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

template<typename _Tp>
constexpr auto inf = std::numeric_limits<_Tp>::max() / 2;

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

    std::vector<std::tuple<int, int, int64>> e(m);

    for (auto& [u, v, w] : e)
    {
        std::cin >> u >> v >> w;
    }

    std::ranges::sort(e, {}, [](const auto& t) { return std::get<2>(t); });

    DisjointSet dsu(n + 1);
    std::vector<bool> used(m);

    std::vector<std::vector<std::pair<int, int>>> g(n + 1);

    int64 sum = 0;

    for (const auto& [i, ei] : e | std::views::enumerate)
    {
        const auto& [u, v, w] = ei;

        if (used[i] = dsu.unite(u, v))
        {
            sum += w;

            g[u].emplace_back(v, w);
            g[v].emplace_back(u, w);
        }
    }

    constexpr int laycnt = 20;

    std::vector<std::array<int, laycnt>> parent(n + 1);
    std::vector<std::array<std::pair<int, int>, laycnt>> maxval(n + 1);
    std::vector<int> depth(n + 1);

    static auto merge = [](const auto&... args) -> std::pair<int, int>
    {
        std::array a{(args.first)..., (args.second)...};
        std::ranges::sort(a, std::ranges::greater{});

        if (std::ranges::unique(a).begin() == a.begin() + 1)
        {
            return std::pair(a[0], -inf<int>);
        }
        else
        {
            return std::pair(a[0], a[1]);
        }
    };

    auto dfs = [&](const auto& self, int u) -> void
    {
        for (int i = 1; i < laycnt; ++i)
        {
            parent[u][i] = parent[parent[u][i - 1]][i - 1];
            maxval[u][i] = merge(maxval[u][i - 1], maxval[parent[u][i - 1]][i - 1]);
        }

        for (const auto& [v, w] : g[u])
        {
            if (v != parent[u][0])
            {
                parent[v][0] = u;
                maxval[v][0] = {w, -inf<int>};

                depth[v] = depth[u] + 1;
                self(self, v);
            }
        }
    };

    dfs(dfs, 1);

    auto lca = [&](int u, int v) -> std::pair<int, int>
    {
        if (depth[u] < depth[v])
        {
            std::swap(u, v);
        }

        std::pair<int, int> max{-inf<int>, -inf<int>};

        for (int i = laycnt, diff = depth[u] - depth[v]; i--; )
        {
            if (diff & 1 << i)
            {
                max = merge(max, maxval[u][i]);
                u = parent[u][i];
            }
        }

        if (u == v)
        {
            return max;
        }

        for (int i = 0; i < laycnt; ++i)
        {
            if (parent[u][i] != parent[v][i])
            {
                max = merge(max, maxval[u][i], maxval[v][i]);

                u = parent[u][i];
                v = parent[v][i];
            }
        }

        return merge(max, maxval[u][0], maxval[v][0]);
    };

    auto ans = inf<int64>;

    for (int i = 0; i < m; ++i)
    {
        if (used[i])
        {
            continue;
        }

        const auto& [u, v, w] = e[i];

        const auto max = lca(u, v);

        if (max.first != w)
        {
            ans = std::min(ans, sum + w - max.first);
        }
        else if (max.second != w)
        {
            ans = std::min(ans, sum + w - max.second);
        }
    }

    std::cout << ans << '\n';

    return 0;
}
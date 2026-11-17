/**
 * 牛客周赛 Round 166
 *
 * => E-小月的时差 ( @c 1400 )
 *
 * -> https://ac.nowcoder.com/acm/contest/141877/E
 *
 * Submissions ~> https://ac.nowcoder.com/acm/contest/view-submission?submissionId=85101832 By huanhuanonly
 *
 * @b Breadth-first-search
 * @b Kruskal’s-algorithm
 *
 * ----October 18, 2026 [20h:14m:53s]----
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

    int n, m, a, b, s, t;
    std::cin >> n >> m >> a >> b >> s >> t;

    std::vector<std::vector<int>> e(n + 1);

    for (int i = 0; i < m; ++i)
    {
        int u, v;
        std::cin >> u >> v;

        e[u].push_back(v);
        e[v].push_back(u);
    }

    constexpr int inf = std::numeric_limits<int>::max() / 2;

    std::queue<std::pair<int, int>> que;

    std::vector<int> da(n + 1, inf);
    que.emplace(a, 0);
    da[a] = 0;

    while (not que.empty())
    {
        const auto [u, d] = que.front();
        que.pop();

        for (const auto& v : e[u])
        {
            if (da[v] == inf)
            {
                da[v] = d + 1;
                que.emplace(v, d + 1);
            }
        }
    }

    std::vector<int> db(n + 1, inf);
    que.emplace(b, 0);
    db[b] = 0;

    while (not que.empty())
    {
        const auto [u, d] = que.front();
        que.pop();

        for (const auto& v : e[u])
        {
            if (db[v] == inf)
            {
                db[v] = d + 1;
                que.emplace(v, d + 1);
            }
        }
    }

    if (s == t)
    {
        std::cout << std::abs(da[s] - db[s]) << '\n';
    }
    else
    {
        auto $ = [&](int u, int v) -> int
        {
            return std::max(std::abs(da[u] - db[u]), std::abs(da[v] - db[v]));
        };

        std::map<int, std::vector<std::pair<int, int>>> sets;

        for (int u = 1; u <= n; ++u)
        {
            for (const auto& v : e[u])
            {
                sets[$(u, v)].emplace_back(u, v);
            }
        }

        DisjointSet dsu(n + 1);

        for (const auto& [key, values] : sets)
        {
            for (const auto& [u, v] : values)
            {
                dsu.unite(u, v);
            }

            if (dsu.connected(s, t))
            {
                std::cout << key << '\n';
                break;
            }
        }
    }

    return 0;
}
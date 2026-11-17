/**
 * => P4234 最小差值生成树 ( @c 省选/NOI- )
 *
 * -> https://www.luogu.com.cn/problem/P4234
 *
 * Submissions ~> https://www.luogu.com.cn/record/286797347 By huanhuanonly
 *
 * @b Kruskal’s-algorithm
 *
 * ----July 18, 2026 [01h:30m:56s]----
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

    int n, m;
    std::cin >> n >> m;

    constexpr int maxw = 1e4;
    std::vector<std::vector<std::pair<int, int>>> e(maxw + 1);

    for (int i = 0; i < m; ++i)
    {
        int u, v, w;
        std::cin >> u >> v >> w;

        e[w].emplace_back(u, v);
    }

    DisjointSet dsu(n + 1);

    int ans = std::numeric_limits<int>::max();

    for (int i = 1; i <= maxw; ++i)
    {
        int cnt = 0;

        for (int j = i; j <= maxw; ++j)
        {
            for (const auto& [u, v] : e[j])
            {
                cnt += dsu.unite(u, v);
            }

            if (cnt == n - 1)
            {
                ans = std::min(ans, j - i);
                break;
            }
        }

        if (cnt < n - 1)
        {
            break;
        }

        dsu.reset();
    }

    std::cout << ans << '\n';

    return 0;
}
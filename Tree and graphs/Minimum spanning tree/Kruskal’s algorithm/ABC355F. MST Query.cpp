/**
 * Tokio Marine & Nichido Fire Insurance Programming Contest 2024 (AtCoder Beginner Contest 355)
 *
 * => F - MST Query ( @c 550 )
 *
 * -> https://atcoder.jp/contests/abc355/tasks/abc355_f
 *
 * Submissions ~> https://atcoder.jp/contests/abc355/submissions/78482012 By huanhuanonly
 *
 * @b Kruskal’s-algorithm
 *
 * ----August 17, 2026 [12h:26m:05s]----
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

    std::vector dsus(10 + 1, DisjointSet(n + 1));

    std::vector<std::tuple<int, int, int>> e(n - 1);

    for (auto& [u, v, w] : e)
    {
        std::cin >> u >> v >> w;
    }

    std::ranges::sort(e, {}, [](const auto& t) -> int { return std::get<2>(t); });

    uint64 sum = 0;

    for (const auto& [u, v, w] : e)
    {
        if (dsus[w].unite(u, v))
        {
            sum += w;
            for (int i = w + 1; i < dsus.size() and dsus[i].unite(u, v); ++i);
        }
    }

    while (q--)
    {
        int u, v, w;
        std::cin >> u >> v >> w;

        for (; w < dsus.size() and dsus[w].unite(u, v); --sum, ++w);

        std::cout << sum << '\n';
    }

    return 0;
}
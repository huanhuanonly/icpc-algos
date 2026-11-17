/**
 * AtCoder Beginner Contest 469
 *
 * => F - GCD Maximum Spanning Tree ( @c 500 )
 *
 * -> https://atcoder.jp/contests/abc469/tasks/abc469_f
 *
 * Submissions ~> https://atcoder.jp/contests/abc469/submissions/78132081 By huanhuanonly
 *
 * @b Kruskal’s-algorithm
 * @b Number-theory ( @a greatest-common-divisor )
 *
 * ----August 05, 2026 [17h:31m:55s]----
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

    int n;
    std::cin >> n;

    std::vector<int> v(n);
    std::map<int, std::vector<int>, std::ranges::greater> sets;

    for (int i = 0; i < n; ++i)
    {
        std::cin >> v[i];

        const int sq = std::ceil(std::sqrt(v[i]));

        for (int d = 1; d < sq; ++d)
        {
            if (v[i] % d == 0)
            {
                sets[d].push_back(i);
                sets[v[i] / d].push_back(i);
            }
        }

        if (sq * sq == v[i])
        {
            sets[sq].push_back(i);
        }
    }

    DisjointSet dsu(n);
    uint64 sum = 0;

    for (const auto& [d, set] : sets)
    {
        for (int i = 1; i < set.size(); ++i)
        {
            if (dsu.unite(set[i - 1], set[i]))
            {
                sum += d;
            }
        }
    }

    std::cout << sum << '\n';

    return 0;
}
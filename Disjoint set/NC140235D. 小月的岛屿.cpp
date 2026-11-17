/**
 * 牛客周赛 Round 161
 *
 * => D-小月的岛屿 ( @c 1000 )
 *
 * -> https://ac.nowcoder.com/acm/contest/140235/D
 *
 * Submissions ~> https://ac.nowcoder.com/acm/contest/view-submission?submissionId=84711628 By huanhuanonly
 *
 * @b Graphs
 * @b Disjoint-set
 *
 * ----September 14, 2026 [10h:11m:41s]----
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

    std::vector<std::string> map(n);

    for (auto& i : map)
    {
        std::cin >> i;
    }

    auto $ = [&](int i, int j) -> int
    {
        return n * i + j;
    };

    DisjointSet dsu4(n * m), dsu8(n * m);

    const std::pair<int, int> d4[]{{1, 0}, {0, 1}, {-1, 0}, {0, -1}};
    const std::pair<int, int> d8[]{{1, 1}, {1, -1}, {-1, 1}, {-1, -1}};

    for (int i = 0; i < n; ++i)
    {
        for (int j = 0; j < m; ++j)
        {
            if (map[i][j] == '1')
            {
                for (const auto& [dx, dy] : d4)
                {
                    const int nx = i + dx, ny = j + dy;

                    if (0 <= nx and nx < n and 0 <= ny and ny < m and map[nx][ny] == '1')
                    {
                        dsu4.unite($(i, j), $(nx, ny));
                        dsu8.unite($(i, j), $(nx, ny));
                    }
                }

                for (const auto& [dx, dy] : d8)
                {
                    const int nx = i + dx, ny = j + dy;

                    if (0 <= nx and nx < n and 0 <= ny and ny < m and map[nx][ny] == '1')
                    {
                        dsu8.unite($(i, j), $(nx, ny));
                    }
                }
            }
        }
    }

    std::map<int, int> s4, s8;

    for (int i = 0; i < n; ++i)
    {
        for (int j = 0; j < m; ++j)
        {
            if (map[i][j] == '1')
            {
                ++s4[dsu4.find($(i, j))];
                ++s8[dsu8.find($(i, j))];
            }
        }
    }

    std::cout
        << s4.size() - s8.size() << ' '
        << (s4.empty() ? 0 : std::ranges::max(s4 | std::views::values)) << ' '
        << (s8.empty() ? 0 : std::ranges::max(s8 | std::views::values)) << '\n';

    return 0;
}
/**
 * Codeforces Round 1086 (Div. 2)
 * 
 * => D2. Tree Orientation (Hard Version) ( @c Rating )
 * 
 * -> https://codeforces.com/contest/2208/problem/D2
 * 
 * Submissions ~> https://codeforces.com/contest/2208/submission/366917990 By huanhuanonly
 * 
 * @b Constructive
 * @b Disjoint-set
 * @b Trees
 * 
 * ----March 16, 2026 [20h:20m:23s]----
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

    int _;
    std::cin >> _;

    while (_--)
    {
        int n;
        std::cin >> n;

        constexpr int maxn = 8000;

        std::vector<std::bitset<maxn>> map(n);
        std::vector<int> sizes(n);

        {
            std::string s;

            for (int i = 0; i < n; ++i)
            {
                std::cin >> s;
                std::ranges::reverse(s);

                map[i] = std::bitset<maxn>(s);
                sizes[i] = map[i].count();
            }
        }

        bool yes = true;

        auto mapp = map;

        for (int u = 0; u < n and yes; ++u)
        {
            if (mapp[u].test(u))
            {
                mapp[u].reset(u);
            }
            else
            {
                yes = false;
            }

            for (int v = mapp[u]._Find_first(); v < n; v = mapp[u]._Find_next(v))
            {
                if (mapp[v].test(u))
                {
                    yes = false;
                    break;
                }
            }
        }

        std::vector<std::pair<int, int>> ans;
        ans.reserve(n - 1);

        DisjointSet dsu(n);

        auto dfs = [&](const auto& self, int u) -> bool
        {
            while (true)
            {
                std::pair<int, int> max{-1, -1};

                for (int v = mapp[u]._Find_first(); v < n; v = mapp[u]._Find_next(v))
                {
                    max = std::max(max, {sizes[v], v});
                }

                if (max.first == -1)
                {
                    break;
                }

                if (max.first >= sizes[u] or not self(self, max.second))
                {
                    return false;
                }

                if (not dsu.unite(u, max.second))
                {
                    return false;
                }
                
                if ((mapp[u] & map[max.second]) != map[max.second])
                {
                    return false;
                }
                
                ans.emplace_back(u, max.second);
                mapp[u] ^= map[max.second];
            }

            return true;
        };

        std::bitset<maxn> set;

        for (int u = 0; u < n; ++u)
        {
            set |= mapp[u];
        }

        set.flip();

        for (int u = set._Find_first(); u < n; u = set._Find_next(u))
        {
            yes = yes and dfs(dfs, u);
        }

        if (yes and ans.size() == n - 1 and std::ranges::count(std::views::iota(0, n), dsu.find(0), [&](int i) -> int { return dsu.find(i); }) == n)
        {
            std::cout << "Yes\n";

            for (const auto& [x, y] : ans)
            {
                std::cout << x + 1 << ' ' << y + 1 << '\n';
            }
        }
        else
        {
            std::cout << "No\n";
        }
    }

    return 0;
}
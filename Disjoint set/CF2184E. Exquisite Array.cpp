/**
 * Codeforces Round 1072 (Div. 3)
 * 
 * => E. Exquisite Array ( @c 1800 )
 * 
 * -> https://codeforces.com/contest/2184/problem/E
 * 
 * Submissions ~> https://codeforces.com/contest/2184/submission/357600674 By huanhuanonly
 * 
 * @b Disjoint-set
 * 
 * ----January 13, 2026 [00h:38m:53s]----
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

#ifdef __GNUC__
using int128 = __int128;
using uint128 = unsigned __int128;
#endif

using real32 = float;
using real64 = double;
using real128 = long double;

class DisjointSet
{
public:
    std::vector<int> tree, sizes;

    explicit DisjointSet(std::size_t n)
        : tree(n), sizes(n, 1)
    {
        std::iota(tree.begin(), tree.end(), 0);
    }

    int find(int u)
    {
        return tree[u] == u ? u : tree[u] = find(tree[u]);
    }

    void merge(int u, int v)
    {
        const int fu = find(u), fv = find(v);
        
        sizes[fu] += sizes[fv];
        tree[fv] = fu;
    }
};

int main(void)
{
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr), std::cout.tie(nullptr);

#ifdef __huanhuanonly_localhost
    ::freopen("in", "r", stdin);
    ::freopen("out", "w", stdout);
#endif

    int _;
    std::cin >> _;

    while (_--)
    {
        int64 n;
        std::cin >> n;

        std::vector<int64> v(n);

        for (int64 i = 0; i < n; ++i)
        {
            std::cin >> v[i];
        }

        std::vector<std::pair<int64, int64>> items(n - 1);

        for (int64 i = 0; i < n - 1; ++i)
        {
            items[i] = {std::abs(v[i] - v[i + 1]), i};
        }

        std::ranges::sort(items, std::ranges::greater{});

        std::vector<int64> ans(n);

        DisjointSet dsu(n);

        static auto $ = [](int64 x) -> int64
        {
            return x * (x - 1) / 2;
        };

        int64 pos = 0;
        int64 sum = 0;

        for (int64 i = n - 1; i >= 1; --i)
        {
            for (; pos < items.size() and items[pos].first == i; ++pos)
            {
                const auto x = items[pos].second;
                const auto y = x + 1;

                if (dsu.find(x) != dsu.find(y))
                {
                    sum -= $(dsu.sizes[dsu.find(x)]);
                    sum -= $(dsu.sizes[dsu.find(y)]);
    
                    dsu.merge(x, y);
                    sum += $(dsu.sizes[dsu.find(x)]);
                }
            }

            ans[i] = sum;
        }

        for (int64 i = 1; i <= n - 1; ++i)
        {
            std::cout << ans[i] << ' ';
        }

        std::cout.put('\n');
    }

    return 0;
}
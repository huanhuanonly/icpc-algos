/**
 * Educational Codeforces Round 186 (Rated for Div. 2)
 * 
 * => E. New Year's Gifts ( @c 1800 )
 * 
 * -> https://codeforces.com/contest/2182/problem/E
 * 
 * Submissions ~> https://codeforces.com/contest/2182/submission/355898538 By huanhuanonly
 * 
 * @b Greedy
 * 
 * ----December 31, 2025 [00h:25m:24s]----
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
        uint64 n, m, k;
        std::cin >> n >> m >> k;

        std::vector<uint64> cnt(m + 1);

        for (uint64 i = 0, v; i < m; ++i)
        {
            std::cin >> v;
            ++cnt[v];
        }

        std::vector<std::pair<uint64, uint64>> v(n);

        for (uint64 i = 0, x, y, z; i < n; ++i)
        {
            std::cin >> x >> y >> z;
            v[i] = {x, z - y};

            k -= y;
        }

        std::ranges::sort(v);

        std::multiset<uint64> set;

        for (uint64 i = 1, cpos = 0; i <= m; ++i)
        {
            while (cpos < n and v[cpos].first == i)
            {
                set.insert(v[cpos].second);
                ++cpos;
            }

            while (cnt[i]-- and not set.empty())
            {
                set.erase(std::prev(set.end()));
            }
        }

        for (; not set.empty() and k >= *set.begin(); k -= set.extract(set.begin()).value());

        std::cout << n - set.size() << '\n';
    }

    return 0;
}
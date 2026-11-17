/**
 * Educational DP Contest
 * 
 * => U - Grouping ( @c 100 )
 * 
 * -> https://atcoder.jp/contests/dp/tasks/dp_u
 * 
 * Submissions ~> https://atcoder.jp/contests/dp/submissions/75124291 By huanhuanonly
 * 
 * @b Bitmask-DP
 * 
 * ----April 20, 2026 [13h:56m:14s]----
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

int main(void)
{
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);

#ifdef __huanhuanonly_localhost
    ::freopen("in", "r", stdin);
    ::freopen("out", "w", stdout);
#endif

    uint32 n;
    std::cin >> n;

    std::vector v(n, std::vector<int64>(n));

    for (uint32 i = 0; i < n; ++i)
    {
        for (uint32 j = 0; j < n; ++j)
        {
            std::cin >> v[i][j];
        }
    }

    std::vector<int64> cost(1U << n);

    for (uint32 mask = 1; mask < 1U << n; ++mask)
    {
        for (uint32 i = 0; i < n; ++i)
        {
            if (mask >> i & 1)
            {
                for (uint32 j = 0; j < i; ++j)
                {
                    if (mask >> j & 1)
                    {
                        cost[mask] += v[i][j];
                    }
                }
            }
        }
    }

    std::vector dp = cost;

    for (uint32 mask = 1; mask < 1U << n; ++mask)
    {
        for (uint32 pmask = mask; pmask; pmask = pmask - 1 & mask)
        {
            dp[mask] = std::max(dp[mask], dp[pmask] + cost[~pmask & mask]);
        }
    }

    std::cout << dp.back() << '\n';

    return 0;
}
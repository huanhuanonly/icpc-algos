/**
 * Educational DP Contest
 * 
 * => O - Matching ( @c 100 )
 * 
 * -> https://atcoder.jp/contests/dp/tasks/dp_o
 * 
 * Submissions ~> https://atcoder.jp/contests/dp/submissions/75003333 By huanhuanonly
 * 
 * @b Bitmask-DP
 * 
 * ----April 17, 2026 [00h:20m:31s]----
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

    std::vector v(n, std::vector<char>(n));

    for (uint32 i = 0; i < n; ++i)
    {
        for (uint32 j = 0; j < n; ++j)
        {
            std::cin >> v[i][j];
        }
    }

    constexpr uint64 mod = 1e9 + 7;
    
    std::vector dp(n + 1, std::vector(1 << n, uint64{}));
    dp[0][0] = 1;

    for (uint32 i = 0; i < n; ++i)
    {
        for (uint32 mark = 0; mark < 1U << n; ++mark)
        {
            if (std::popcount(mark) == i)
            {
                for (uint32 j = 0; j < n; ++j)
                {
                    if (v[i][j] == '1' and mark >> j & 1 ^ 1)
                    {
                        (dp[i + 1][mark | 1 << j] += dp[i][mark]) %= mod;
                    }
                }
            }
        }
    }

    std::cout << dp.back().back() << '\n';

    return 0;
}
/**
 * Educational Codeforces Round 183 (Rated for Div. 2)
 * 
 * => F. Long Journey ( @c 2500 )
 * 
 * -> https://codeforces.com/contest/2145/problem/F
 * 
 * Submissions ~> https://codeforces.com/contest/2145/submission/344957979 By huanhuanonly
 * 
 * @b Binary-lifting and @b Number-theory
 * 
 * ----October 21, 2025 [11h:41m:25s]----
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
        uint64 n, m;
        std::cin >> n >> m;

        std::vector<uint64> a(n), b(n);
        uint64 lcm = 1;

        for (uint64 i = 0; i < n; ++i)
        {
            std::cin >> a[i];
            lcm = std::lcm(lcm, a[i]);
        }

        for (uint64 i = 0; i < n; ++i)
        {
            std::cin >> b[i];
        }

        constexpr uint64 laycnt = 50;

        std::vector dp(n, std::vector(lcm, std::array<uint64, laycnt>{}));

        for (uint64 i = 0; i < n; ++i)
        {
            for (uint64 j = 0; j < lcm; ++j)
            {
                dp[i][j][0] = (j + 1) % lcm % a[i] != b[i];
            }
        }

        for (uint64 lay = 1; lay < laycnt; ++lay)
        {
            for (uint64 i = 0; i < n; ++i)
            {
                for (uint64 j = 0; j < lcm; ++j)
                {
                    dp[i][j][lay] = dp[i][j][lay - 1] + dp[(i + (1ULL << lay - 1)) % n][(j + dp[i][j][lay - 1]) % lcm][lay - 1];
                }
            }
        }

        uint64 i = 0, j = 0;

        for (uint64 lay = laycnt; lay--; )
        {
            if (j + dp[i % n][j % lcm][lay] < m)
            {
                j += dp[i % n][j % lcm][lay];
                i += 1ULL << lay;
            }
        }

        if (j + 1 == m and dp[i % n][j % lcm][0])
        {
            std::cout << i + 1 << '\n';
        }
        else
        {
            std::cout << -1 << '\n';
        }
    }

    return 0;
}
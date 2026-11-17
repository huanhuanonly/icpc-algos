/**
 * Codeforces Global Round 14
 *
 * => E. Phoenix and Computers ( @c 2200 )
 *
 * -> https://codeforces.com/contest/1515/problem/E
 *
 * Submissions ~> https://codeforces.com/contest/1515/submission/350740165 By huanhuanonly
 *
 * @b Connected-component-DP and @b Combinatorics
 *
 * ----November 26, 2025 [22h:04m:08s]----
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

    uint64 n, mod;
    std::cin >> n >> mod;

    std::vector dp(n + 4, std::vector(n + 2, uint64{}));

    dp[1][1] = 1;

    for (uint64 i = 1; i <= n; ++i)
    {
        for (uint64 j = 1; j <= i; ++j)
        {
            (dp[i + 1][j + 1] += dp[i][j] * (j + 1)) %= mod;
            (dp[i + 1][j] += dp[i][j] * (j * 2)) %= mod;
            (dp[i + 2][j] += dp[i][j] * (j * 2)) %= mod;
            (dp[i + 2][j - 1] += dp[i][j] * (j - 1) * 2) %= mod;
            (dp[i + 3][j - 1] += dp[i][j] * (j - 1)) %= mod;
        }
    }

    std::cout << dp[n][1];

    return 0;
}
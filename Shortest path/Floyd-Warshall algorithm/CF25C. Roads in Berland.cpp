/**
 * Codeforces Beta Round 25 (Div. 2 Only)
 *
 * => C. Roads in Berland ( @c 1900 )
 *
 * -> https://codeforces.com/contest/25/problem/C
 *
 * Submissions ~> https://codeforces.com/contest/25/submission/341217712 By huanhuanonly
 *
 * @b Floyd–Warshall-algorithm
 *
 * ----September 30, 2025 [23h:29m:52s]----
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

    int n;
    std::cin >> n;

    std::vector dp(n, std::vector(n, 0ULL));

    for (int i = 0; i < n; ++i)
    {
        for (int j = 0; j < n; ++j)
        {
            std::cin >> dp[i][j];
        }
    }

    for (int k = 0; k < n; ++k)
    {
        for (int i = 0; i < n; ++i)
        {
            for (int j = 0; j < n; ++j)
            {
                dp[i][j] = std::min(dp[i][j], dp[i][k] + dp[k][j]);
            }
        }
    }

    int q;
    std::cin >> q;

    while (q--)
    {
        int u, v;
        uint64 c;

        std::cin >> u >> v >> c;

        --u, --v;

        dp[u][v] = std::min(dp[u][v], c);
        dp[v][u] = std::min(dp[v][u], c);

        for (int k : {u, v})
        {
            for (int i = 0; i < n; ++i)
            {
                for (int j = 0; j < n; ++j)
                {
                    dp[i][j] = std::min(dp[i][j], dp[i][k] + dp[k][j]);
                }
            }
        }

        uint64 sum = 0;

        for (int i = 0; i < n; ++i)
        {
            for (int j = i + 1; j < n; ++j)
            {
                sum += dp[i][j];
            }
        }

        std::cout << sum << ' ';
    }

    return 0;
}
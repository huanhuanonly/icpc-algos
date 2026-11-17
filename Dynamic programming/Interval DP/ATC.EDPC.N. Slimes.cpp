/**
 * Educational DP Contest
 * 
 * => N - Slimes ( @c 100 )
 * 
 * -> https://atcoder.jp/contests/dp/tasks/dp_n
 * 
 * Submissions ~> https://atcoder.jp/contests/dp/submissions/75002888 By huanhuanonly
 * 
 * @b Interval-DP
 * 
 * ----April 16, 2026 [23h:35m:06s]----
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

    int n;
    std::cin >> n;

    std::vector<int64> v(n + 1);

    for (int i = 1; i <= n; ++i)
    {
        std::cin >> v[i];
    }

    constexpr auto inf = std::numeric_limits<int64>::max() / 2;

    std::vector dp(n + 1, std::vector(n + 1, inf));

    for (int i = 1; i <= n; ++i)
    {
        dp[i][i] = 0;
        v[i] += v[i - 1];
    }

    for (int m = 1; m < n; ++m)
    {
        for (int i = 1; i <= n; ++i)
        {
            if (const int j = i + m; j <= n)
            {
                for (int k = i; k < j; ++k)
                {
                    dp[i][j] = std::min(dp[i][j], dp[i][k] + dp[k + 1][j] + v[j] - v[i - 1]);
                }
            }
        }
    }

    std::cout << dp[1][n] << '\n';

    return 0;
}
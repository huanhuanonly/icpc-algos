/**
 * Educational DP Contest
 * 
 * => L - Deque ( @c 100 )
 * 
 * -> https://atcoder.jp/contests/dp/tasks/dp_l
 * 
 * Submissions ~> https://atcoder.jp/contests/dp/submissions/75000717 By huanhuanonly
 * 
 * @b Interval-DP and @b Game-theory
 * 
 * ----April 16, 2026 [21h:12m:19s]----
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

    std::vector<int64> v(n + 2);

    for (int i = 1; i <= n; ++i)
    {
        std::cin >> v[i];
    }

    std::vector dp(n + 2, std::vector(n + 1, int64{}));

    for (int m = 0; m < n; ++m)
    {
        for (int i = 1; i <= n; ++i)
        {
            if (const int j = i + m; j <= n)
            {
                if (n - m & 1)
                {
                    dp[i][j] = std::max(dp[i + 1][j] + v[i], dp[i][j - 1] + v[j]);
                }
                else
                {
                    dp[i][j] = std::min(dp[i + 1][j] - v[i], dp[i][j - 1] - v[j]);
                }
            }
        }
    }

    std::cout << dp[1][n] << '\n';

    return 0;
}
/**
 * 牛客周赛 Round 166
 *
 * => F-小月的订单 ( @c 1600 )
 *
 * -> https://ac.nowcoder.com/acm/contest/141877/F
 *
 * Submissions ~> https://ac.nowcoder.com/acm/contest/view-submission?submissionId=85104919 By huanhuanonly
 *
 * @b Linear-DP
 *
 * ----October 18, 2026 [20h:47m:12s]----
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

    uint64 n, s;
    std::cin >> n >> s;

    std::vector<uint64> a(n + 2), b(n + 2);

    for (uint64 i = 1; i <= n; ++i)
    {
        std::cin >> a[i];
    }

    for (uint64 i = 1; i <= n; ++i)
    {
        std::cin >> b[i];
    }

    constexpr auto inf = std::numeric_limits<uint64>::max() / 2;

    std::vector f(n + 2, std::vector(n + 1, inf));
    std::vector g(n + 2, std::vector(n + 1, inf));

    f.front()[0] = 0;
    g.back()[0] = 0;

    f[1][0] = 0;
    f[1][1] = a[1];

    for (uint64 i = 2; i <= n; ++i)
    {
        f[i][0] = 0;

        for (uint64 j = 1; j <= i; ++j)
        {
            f[i][j] = f[i - 1][j];

            if (i >= 2)
            {
                f[i][j] = std::min(f[i][j], f[i - 2][j - 1] + a[i]);
            }
        }
    }

    g[n][0] = 0;
    g[n][1] = b[n];

    for (uint64 i = n - 1; i >= 1; --i)
    {
        g[i][0] = 0;

        for (uint64 j = 1; j <= n - i + 1; ++j)
        {
            g[i][j] = g[i + 1][j];

            if (i + 2 <= n + 1)
            {
                g[i][j] = std::min(g[i][j], g[i + 2][j - 1] + b[i]);
            }
        }
    }

    uint64 k = 0;

    for (uint64 i = 1; i <= n; ++i)
    {
        for (uint64 j = 1; j < n; ++j)
        {
            if (f[i - 1][j] + g[i + 1][j] <= s)
            {
                k = std::max(k, j);
            }
        }
    }

    std::cout << k << '\n';

    return 0;
}
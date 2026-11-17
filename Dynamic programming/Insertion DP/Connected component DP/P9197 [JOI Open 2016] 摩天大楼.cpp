/**
 * => P9197 [JOI Open 2016] 摩天大楼 / Skyscraper ( @c 省选/NOI- )
 *
 * -> https://www.luogu.com.cn/problem/P9197
 *
 * Submissions ~> https://www.luogu.com.cn/record/252262764 By huanhuanonly
 *
 * @b Connected-component-DP and @b Combinatorics
 *
 * ----December 09, 2025 [11h:44m:21s]----
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

    int n, limit;
    std::cin >> n >> limit;

    constexpr uint64 mod = 1e9 + 7;

    std::vector<int> v(n + 1);

    for (int i = 1; i <= n; ++i)
    {
        std::cin >> v[i];
    }

    if (n == 1)
    {
        std::cout << 1;
        return 0;
    }

    std::ranges::sort(v | std::views::drop(1));

    v[0] = v[1];

    std::vector dp(n + 1, std::vector(n + 1, std::vector(limit + 1, std::array<uint64, 2 + 1>{})));
    dp[0][0][0][0] = 1;

    for (int i = 0; i < n; ++i)
    {
        for (int j = 0; j <= i; ++j)
        {
            for (int s = 0; s <= limit; ++s)
            {
                for (int c = 0; c <= 2; ++c)
                {
                    const int ns = s + (2 * j - c) * (v[i + 1] - v[i]);

                    if (not (0 <= ns and ns <= limit))
                    {
                        continue;
                    }

                    (dp[i + 1][j][ns][c] += dp[i][j][s][c] * (2 * j - c)) %= mod;

                    if (c < 2)
                    {
                        (dp[i + 1][j][ns][c + 1] += dp[i][j][s][c] * (1 + (c == 0))) %= mod;
                    }

                    (dp[i + 1][j + 1][ns][c] += dp[i][j][s][c] * (j + 1 - c)) %= mod;

                    if (c < 2)
                    {
                        (dp[i + 1][j + 1][ns][c + 1] += dp[i][j][s][c] * (1 + (c == 0))) %= mod;
                    }

                    if (j > 1)
                    {
                        (dp[i + 1][j - 1][ns][c] += dp[i][j][s][c] * (j - 1)) %= mod;
                    }
                }
            }
        }
    }

    uint64 sum = 0;

    for (int s = 0; s <= limit; ++s)
    {
        (sum += dp[n][1][s][2]) %= mod;
    }

    std::cout << sum;

    return 0;
}
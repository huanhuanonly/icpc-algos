/**
 * 牛客周赛 Round 156
 *
 * => F-小红的排列计数 ( @c 1800 )
 *
 * -> https://ac.nowcoder.com/acm/contest/138917/F
 *
 * Submissions ~> https://ac.nowcoder.com/acm/contest/view-submission?submissionId=84424988 By huanhuanonly
 *
 * @b Insertion-DP
 *
 * ----August 09, 2026 [20h:51m:19s]----
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

    int n, k;
    std::cin >> n >> k;

    constexpr uint64 mod = 998244353;

    std::vector dp(n + 1, std::vector(k + 1, uint64{}));
    dp[1][0] = 1;

    for (int i = 2; i <= n; ++i)
    {
        dp[i][0] = dp[i - 1][0] * 2 % mod;

        for (int j = 1; j <= k; ++j)
        {
            dp[i][j] = dp[i - 1][j] * (2 + j * 2) % mod;

            if (j * 2 <= i)
            {
                dp[i][j] += dp[i - 1][j - 1] * (i - (j * 2)) % mod;
                dp[i][j] %= mod;
            }
        }
    }

    std::cout << dp.back().back() << '\n';

    return 0;
}
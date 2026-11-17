/**
 * Educational DP Contest
 * 
 * => M - Candies ( @c 100 )
 * 
 * -> https://atcoder.jp/contests/dp/tasks/dp_m
 * 
 * Submissions ~> https://atcoder.jp/contests/dp/submissions/75002293 By huanhuanonly
 * 
 * @b Counting-DP and @b Prefix-sum
 * 
 * ----April 16, 2026 [23h:05m:46s]----
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

    std::vector<int> v(n + 1);

    for (int i = 1; i <= n; ++i)
    {
        std::cin >> v[i];
    }

    constexpr uint64 mod = 1e9 + 7;

    std::vector dp(n + 1, std::vector(k + 1, uint64{}));
    dp[0][0] = 1;

    for (int i = 1; i <= n; ++i)
    {
        std::partial_sum(dp[i - 1].begin(), dp[i - 1].end(), dp[i - 1].begin());

        for (int j = 0; j <= k; ++j)
        {
            dp[i][j] = dp[i - 1][j] % mod;

            if (j - v[i] - 1 >= 0)
            {
                (dp[i][j] += mod - dp[i - 1][j - v[i] - 1] % mod) %= mod;
            }
        }
    }

    std::cout << dp.back().back() << '\n';

    return 0;
}
/**
 * Educational DP Contest
 * 
 * => T - Permutation ( @c 100 )
 * 
 * -> https://atcoder.jp/contests/dp/tasks/dp_t
 * 
 * Submissions ~> https://atcoder.jp/contests/dp/submissions/75121530 By huanhuanonly
 * 
 * @b Counting-DP and @b Prefix-sum
 * 
 * ----April 20, 2026 [10h:57m:12s]----
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

    std::string s;
    std::cin >> s;

    constexpr uint64 mod = 1e9 + 7;

    std::vector dp(n, std::vector(n, uint64{}));

    std::ranges::fill(dp[0], 1ULL);

    for (int i = 1; i < n; ++i)
    {
        for (int j = 0; j <= i; ++j)
        {
            if (s[i - 1] == '<')
            {
                dp[i][j] = (dp[i - 1].back() + mod - (j ? dp[i - 1][j - 1] : 0)) % mod;
            }
            else if (j)
            {
                dp[i][j] = dp[i - 1][j - 1] % mod;
            }
        }

        std::partial_sum(dp[i].begin(), dp[i].end(), dp[i].begin());
    }

    std::cout << dp.back().back() % mod << '\n';

    return 0;
}
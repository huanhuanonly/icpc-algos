/**
 * Educational DP Contest
 * 
 * => I - Coins ( @c 100 )
 * 
 * -> https://atcoder.jp/contests/dp/tasks/dp_i
 * 
 * Submissions ~> https://atcoder.jp/contests/dp/submissions/74975669 By huanhuanonly
 * 
 * @b Probability-DP
 * 
 * ----April 15, 2026 [15h:33m:11s]----
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

    std::vector<real80> p(n + 1);

    for (int i = 1; i <= n; ++i)
    {
        std::cin >> p[i];
    }

    std::vector dp(n + 1, std::vector(n + 1, real80{}));
    dp[0][0] = 1;

    for (int i = 1; i <= n; ++i)
    {
        dp[i][0] = dp[i - 1][0] * (1.0L - p[i]);

        for (int j = 1; j <= n; ++j)
        {
            dp[i][j] = dp[i - 1][j - 1] * p[i] + dp[i - 1][j] * (1.0L - p[i]);
        }
    }

    std::cout << std::fixed << std::setprecision(12);
    std::cout << *std::ranges::fold_left_first(dp.back() | std::views::drop(1 + n / 2), std::plus{});

    return 0;
}
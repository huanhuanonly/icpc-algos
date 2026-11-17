/**
 * 2023 (ICPC) Jiangxi Provincial Contest -- Official Contest
 *
 * => D. Stack Out
 *
 * -> https://codeforces.com/gym/104385/problem/D
 *
 * Submissions ~> https://codeforces.com/gym/104385/submission/388266115 By huanhuanonly
 *
 * @b Counting-DP
 * @b Prefix-sum
 *
 * ----August 25, 2026 [00h:37m:43s]----
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

    std::vector dp(n + 1, std::vector(n + 1, std::array{uint64{}, uint64{}}));
    dp[0][0][0] = 1;

    std::vector<uint64> pre(n + 1);

    for (int i = 1; i <= n; ++i)
    {
        for (int j = n; j >= 1; --j)
        {
            (dp[i][j][0] += dp[i - 1][j - 1][0]) %= mod;
            (dp[i][j][1] += dp[i - 1][j - 1][1]) %= mod;
        }

        for (int j = 0; j + k <= n; ++j)
        {
            (dp[i][j][1] += dp[i][j + k][0]) %= mod;
        }

        {
            const auto view = dp[i] | std::views::keys;
            std::partial_sum(view.begin(), view.end(), pre.begin());
        }

        for (int j = 0; j <= n; ++j)
        {
            (dp[i][j][0] += (pre[std::min(j + k - 1, n)] - pre[j]) % mod) %= mod;
        }

        for (int j = n - 1; j >= 0; --j)
        {
            (dp[i][j][1] += dp[i][j + 1][1]) %= mod;
        }
    }

    std::cout << dp.back().front().back() << '\n';

    return 0;
}
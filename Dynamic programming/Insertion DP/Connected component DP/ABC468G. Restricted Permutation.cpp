/**
 * AtCoder Beginner Contest 468
 *
 * => G - Restricted Permutation ( @c 550 )
 *
 * -> https://atcoder.jp/contests/abc468/tasks/abc468_g
 *
 * Submissions ~> https://atcoder.jp/contests/abc468/submissions/78513456 By huanhuanonly
 *
 * @b Connected-component-DP
 *
 * ----August 18, 2026 [23h:14m:06s]----
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

    s.insert(s.begin(), ' ');

    constexpr uint64 mod = 998244353;

    std::vector dp(n + 1, std::vector(n + 2, uint64{}));
    dp[0][2] = 1;

    for (int i = 1; i <= n; ++i)
    {
        if (s[i] == 'o')
        {
            dp[i][1] = (dp[i - 1][1] * 2 + dp[i - 1][2]) % mod;
        }
        else for (int j = 2; j <= i; ++j)
        {
            dp[i][j] = (dp[i - 1][j - 1] * j + dp[i - 1][j] * 2 * j + dp[i - 1][j + 1] * j) % mod;
        }
    }

    std::cout << dp[n][1] << '\n';

    return 0;
}
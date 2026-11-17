/**
 * 2023 Jiangsu Collegiate Programming Contest, 2023 National Invitational of CCPC (Hunan), The 13th Xiangtan Collegiate Programming Contest
 *
 * => F. Timaeus
 *
 * -> https://codeforces.com/gym/104396/problem/F
 *
 * Submissions ~> https://codeforces.com/gym/104396/submission/389820052 By huanhuanonly
 *
 * @b Expectation-DP
 *
 * ----September 08, 2026 [09h:49m:51s]----
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

    do
    {
        int a, b, P, Q;
        std::cin >> a >> b >> P >> Q;

        const real80 p = P / 100.L;
        const real80 q = Q / 100.L;

        std::cout << std::fixed << std::setprecision(12);

        if (b > 1)
        {
            std::vector<real80> dp(a + 1);

            for (int i = b; i <= a; ++i)
            {
                dp[i] = std::max(
                    p * (dp[i - b] + 2) + (1 - p) * (dp[i - b] + 1),
                    q * (dp[i - b + 1] + 1) + (1 - q) * (dp[i - b] + 1));
            }

            std::cout << dp.back() << '\n';
        }
        else
        {
            std::vector<real80> f(a + 1), g(a + 1);

            for (int i = 1; i <= a; ++i)
            {
                f[i] = p * (f[i - 1] + 2) + (1 - p) * (f[i - 1] + 1);
                g[i] = ((1 - q) * (g[i - 1] + 1) + q) / (1 - q);
            }

            std::cout << std::max(f.back(), g.back()) << '\n';
        }
    } while (false);

    return 0;
}
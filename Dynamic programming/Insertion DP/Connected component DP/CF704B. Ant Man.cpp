/**
 * Codeforces Round 366 (Div. 1)
 *
 * => B. Ant Man ( @c 2500 )
 *
 * -> https://codeforces.com/contest/704/problem/B
 *
 * Submissions ~> https://codeforces.com/contest/704/submission/351066536 By huanhuanonly
 *
 * @b Connected-component-DP
 *
 * ----November 29, 2025 [01h:03m:37s]----
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

    int64 n, s, e;
    std::cin >> n >> s >> e;

    std::vector<int64> x(n + 1), a(n + 1), b(n + 1), c(n + 1), d(n + 1);

    std::istream_iterator<int64> iit(std::cin);

    iit = std::ranges::copy_n(iit, n, x.begin() + 1).in;
    iit = std::ranges::copy_n(iit, n, a.begin() + 1).in;
    iit = std::ranges::copy_n(iit, n, b.begin() + 1).in;
    iit = std::ranges::copy_n(iit, n, c.begin() + 1).in;
    iit = std::ranges::copy_n(iit, n, d.begin() + 1).in;

    for (int i = 1; i <= n; ++i)
    {
        a[i] += x[i];
        b[i] -= x[i];
        c[i] += x[i];
        d[i] -= x[i];
    }

    static auto chmin = [](auto& a, const auto& b) -> void
    {
        return b < a ? void(a = b) : void();
    };

    constexpr auto inf = std::numeric_limits<int64>::max() / 2;

    std::vector dp(n + 1, std::vector(n + 1, inf));

    dp[0][0] = 0;

    for (int i = 1; i <= n; ++i)
    {
        for (int j = 1; j <= i; ++j)
        {
            if (i == s)
            {
                chmin(dp[i][j], dp[i - 1][j] + c[i]);
                chmin(dp[i][j], dp[i - 1][j - 1] + d[i]);
            }
            else if (i == e)
            {
                chmin(dp[i][j], dp[i - 1][j - 1] + b[i]);
                chmin(dp[i][j], dp[i - 1][j] + a[i]);
            }
            else
            {
                if (i <= n - 2 and (j > (i > s) + (i > e)))
                {
                    chmin(dp[i][j], dp[i - 1][j - 1] + b[i] + d[i]);
                }

                if (i > 2 and i != j)
                {
                    chmin(dp[i][j], dp[i - 1][j + 1] + c[i] + a[i]);
                }

                if (i != 1 and i != n)
                {
                    if (not (j == 1 and i > e))
                    {
                        chmin(dp[i][j], dp[i - 1][j] + a[i] + d[i]);
                    }

                    if (not (j == 1 and i > s))
                    {
                        chmin(dp[i][j], dp[i - 1][j] + c[i] + b[i]);
                    }
                }
            }
        }
    }

    std::cout << dp[n][1];

    return 0;
}
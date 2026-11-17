/**
 * AtCoder Beginner Contest 338
 *
 * => F - Negative Traveling Salesman ( @c 500 )
 *
 * -> https://atcoder.jp/contests/abc338/tasks/abc338_f
 *
 * Submissions ~> https://atcoder.jp/contests/abc338/submissions/50900017 By huanhuanonly
 *
 * @b Floyd
 * @b Bitmask-DP
 *
 * ----March 04, 2024 [17h:50m:32s]----
*/

#include <bits/stdc++.h>

using uint    = unsigned int;
using llong   = long long int;
using ullong  = unsigned long long int;
using ldouble = long double;

int main(void)
{
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr), std::cout.tie(nullptr);

#ifdef __localhost
    ::freopen("Input.txt", "r", stdin);
    ::freopen("Output.txt", "w", stdout);
#endif

    int n, m;
    std::cin >> n >> m;

    constexpr const llong inf = LLONG_MAX / 2 - 1;

    std::vector<std::vector<llong>> dis(n, std::vector<llong>(n, inf));

    for (int i = 0; i < m; ++i)
    {
        llong u, v, w;
        std::cin >> u >> v >> w;

        --u, --v;

        dis[u][v] = std::min(dis[u][v], w);
    }

    for (int k = 0; k < n; ++k)
    {
        for (int i = 0; i < n; ++i)
        {
            for (int j = 0; j < n; ++j)
            {
                if (i == j)
                    dis[i][j] = 0;
                else
                    dis[i][j] = std::min(dis[i][j], dis[i][k] + dis[k][j]);
            }
        }
    }

    std::vector<std::vector<llong>> dp(n, std::vector<llong>(1 << n, inf));

    for (int i = 0; i < n; ++i)
        dp[i][1 << i] = 0;

    for (int state = 0; state < (1 << n); ++state)
    {
        /**
         *  @a From point i to point j
         */
        for (int i = 0; i < n; ++i)
        {
            if (((state & (1 << i)) == 0) or dp[i][state] == inf)
                continue;

            for (int j = 0; j < n; ++j)
            {
                if ((state & (1 << j)) or dis[i][j] == inf)
                    continue;

                dp[j][state | (1 << j)] = std::min(dp[j][state | (1 << j)], dp[i][state] + dis[i][j]);
            }
        }
    }

    llong ans = inf;

    for (int i = 0; i < n; ++i)
        ans = std::min(ans, dp[i][(1 << n) - 1]);

    if (ans ^ inf)
        std::cout << ans << '\n';
    else
        std::cout << "No" << '\n';

    return 0;
}
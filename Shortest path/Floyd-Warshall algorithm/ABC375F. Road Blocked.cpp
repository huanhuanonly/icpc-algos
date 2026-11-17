/**
 * Panasonic Programming Contest 2024（AtCoder Beginner Contest 375）
 *
 * => F - Road Blocked ( @c 550 )
 *
 * -> https://atcoder.jp/contests/abc375/tasks/abc375_f
 *
 * Submissions ~> https://atcoder.jp/contests/abc375/submissions/59313777 By huanhuanonly
 *
 * @b Floyd–Warshall-algorithm and @b Offline ( @a turn-back-time )
 *
 * ----November 01, 2024 [11h:38m:28s]----
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

#ifdef __localhost
    ::freopen("in", "r", stdin);
    ::freopen("out", "w", stdout);
#endif

    uint32 n, m, q;
    std::cin >> n >> m >> q;

    std::vector<std::tuple<uint32, uint32, uint64>> e(m + 1);

    for (auto& [u, v, w] : e | std::views::drop(1))
    {
        std::cin >> u >> v >> w;
    }

    // opt, x, y, ans
    std::vector<std::tuple<uint32, uint32, uint32, uint64>> query(q);
    std::vector<bool> closed(m + 1);

    for (auto& [opt, x, y, _] : query)
    {
        std::cin >> opt >> x;

        if (opt == 1)
            closed[x] = true;
        else
            std::cin >> y;
    }

    uint64 inf = std::numeric_limits<decltype(inf)>::max() / 2;

    std::vector<std::vector<uint64>> dp(n + 1, std::vector<uint64>(n + 1, inf));

    for (uint32 i = 1; i <= m; ++i)
    {
        if (not closed[i])
        {
            const auto& [u, v, w] = e[i];

            dp[u][v] = w;
            dp[v][u] = w;
        }
    }

    for (uint32 i = 1; i <= n; ++i)
    {
        dp[i][i] = 0;
    }

    for (uint32 k = 1; k <= n; ++k)
        for (uint32 i = 1; i <= n; ++i)
            for (uint32 j = 1; j <= n; ++j)
                dp[i][j] = std::min(dp[i][j], dp[i][k] + dp[k][j]);

    for (uint32 i = query.size(); i--; )
    {
        auto& [opt, x, y, ans] = query[i];

        if (opt == 1)
        {
            const auto& [u, v, w] = e[x];

            dp[u][v] = std::min(dp[u][v], w);
            dp[v][u] = std::min(dp[v][u], w);

            for (uint32 i = 1; i <= n; ++i)
                for (uint32 j = 1; j <= n; ++j)
                    dp[i][j] = std::min(dp[i][j], dp[i][u] + dp[u][j]);

            for (uint32 i = 1; i <= n; ++i)
                for (uint32 j = 1; j <= n; ++j)
                    dp[i][j] = std::min(dp[i][j], dp[i][v] + dp[v][j]);
        }
        else
        {
            ans = dp[x][y];
        }
    }

    for (const auto& [opt, x, y, ans] : query)
    {
        if (opt == 2)
        {
            if (ans != inf)
                std::cout << ans << '\n';
            else
                std::cout << "-1\n";
        }
    }

    return 0;
}
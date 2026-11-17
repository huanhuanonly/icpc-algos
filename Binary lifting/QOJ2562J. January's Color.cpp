/**
 * The 2025 ICPC Asia Xi'an Regional Contest
 *
 * => J. January's Color
 *
 * -> https://qoj.ac/contest/2562/problem/14690
 *
 * Submissions ~> https://qoj.ac/submission/2299454 By huanhuanonly
 *
 * @b Tree-DP
 * @b Binary-lifting
 *
 * ----April 29, 2026 [21h:22m:11s]----
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

    int _;
    std::cin >> _;

    while (_--)
    {
        int n, m;
        std::cin >> n >> m;

        std::vector<int64> c(n + 1);

        for (int i = 1; i <= n; ++i)
        {
            std::cin >> c[i];
        }

        std::vector<std::vector<int>> e(n + 1);

        for (int i = 0; i < n - 1; ++i)
        {
            int u, v;
            std::cin >> u >> v;

            e[u].push_back(v);
            e[v].push_back(u);
        }

        constexpr int bitcnt = 30;

        std::vector<std::array<int, bitcnt>> fa(n + 1);
        std::vector<std::array<int64, bitcnt>> dp(n + 1);

        std::vector<int> depth(n + 1);

        auto dfs = [&](const auto& self, int u) -> void
        {
            if (fa[u][0])
            {
                e[u].erase(std::ranges::find(e[u], fa[u][0]));
            }

            for (const auto& v : e[u])
            {
                fa[v][0] = u;
                depth[v] = depth[u] + 1;
                self(self, v);
            }

            if (not e[u].empty())
            {
                std::ranges::sort(e[u], {}, [&](const auto& i) -> int64 { return c[i]; });
                c[u] = std::min(c[u], c[e[u][0]] + c[e[u][1]]);
            }
        };

        depth[1] = 1;
        dfs(dfs, 1);

        for (int u = 2; u <= n; ++u)
        {
            dp[u][0] = c[e[fa[u][0]][e[fa[u][0]][0] == u]];
        }

        for (int i = 1; i < bitcnt; ++i)
        {
            for (int u = 1; u <= n; ++u)
            {
                fa[u][i] = fa[fa[u][i - 1]][i - 1];
                dp[u][i] = dp[u][i - 1] + dp[fa[u][i - 1]][i - 1];
            }
        }

        while (m--)
        {
            int x, y;
            std::cin >> x >> y;

            if (depth[x] < depth[y])
            {
                std::cout << -1 << '\n';
                continue;
            }

            int64 sum = 0;

            for (int i = bitcnt - 1; i >= 0; --i)
            {
                if (depth[fa[x][i]] >= depth[y])
                {
                    sum += dp[x][i];
                    x = fa[x][i];
                }
            }

            if (x == y)
            {
                std::cout << sum << '\n';
            }
            else
            {
                std::cout << -1 << '\n';
            }
        }
    }

    return 0;
}
/**
 * Codeforces Round 1122 (Div. 3)
 *
 * => G. Modular Tree ( @c 2200 )
 *
 * -> https://codeforces.com/contest/2266/problem/G
 *
 * Submissions ~> https://codeforces.com/contest/2266/submission/394344156 By huanhuanonly
 *
 * @b Number-theory ( @a greatest-common-divisor | @a modular-arithmetic )
 * @b Dfs on @a Trees
 *
 * ----October 13, 2026 [10h:50m:48s]----
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
        int n;
        std::cin >> n;

        std::vector<uint64> a(n + 1), b(n + 1);

        for (int i = 1; i <= n; ++i)
        {
            std::cin >> a[i];
        }

        for (int i = 1; i <= n; ++i)
        {
            std::cin >> b[i];
        }

        std::vector<std::vector<int>> e(n + 1);

        for (int i = 0; i < n - 1; ++i)
        {
            int u, v;
            std::cin >> u >> v;

            e[u].push_back(v);
            e[v].push_back(u);
        }

        std::vector<uint64> g(n + 1);

        auto dfs = [&](const auto& self, int u, int fa) -> void
        {
            uint64 s = 0;

            for (const auto& v : e[u])
            {
                if (v != fa)
                {
                    self(self, v, u);

                    g[u] = std::gcd(g[u], g[v] % b[u]);
                    s += a[v];
                }
            }

            g[u] = std::gcd(g[u], s % b[u]);
            g[u] = std::gcd(g[u], b[u]) % b[u];
        };

        dfs(dfs, 1, 0);

        uint64 sum = 0;

        for (int i = 1; i <= n; ++i)
        {
            const uint64 x = g[i] ? (b[i] - 1 - a[i]) / g[i] : 0;
            sum += a[i] + g[i] * x;
        }

        std::cout << sum << '\n';
    }

    return 0;
}
/**
 * 2026年码蹄杯 职业院校赛道 & 青少年挑战赛道入门组国赛
 *
 * => MC0545 王翦破蓟定北疆 ( @c 星耀 )
 *
 * -> https://www.matiji.net/exam/brushquestion/45/4777/C98C14523F069FECB0DEED64F00CEAB0
 *
 * Submissions ~> https://www.matiji.net/exam/oj/submit-detail/20552749/45/4777/C98C14523F069FECB0DEED64F00CEAB0 By huanhuanonly
 *
 * @b Binary-lifting
 * @b Dfs on @a Trees
 *
 * ----August 26, 2026 [23h:27m:02s]----
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

    int n, m;
    std::cin >> n >> m;

    constexpr int laycnt = 30;
    std::vector<std::array<int, laycnt>> p(n + 1);

    for (int i = 1; i <= n; ++i)
    {
        std::cin >> p[i][0];
    }

    std::vector<std::vector<int>> e(n + 1);

    for (int i = 0; i < n - 1; ++i)
    {
        int u, v;
        std::cin >> u >> v;

        e[u].push_back(v);
        e[v].push_back(u);
    }

    std::vector dis(n + 1, std::vector<int>(n + 1));

    auto dfs = [&](const auto& self, int u, int fa, int s, int d) -> void
    {
        dis[s][u] = d;

        for (const auto& v : e[u])
        {
            if (v != fa)
            {
                self(self, v, u, s, d + 1);
            }
        }
    };

    for (int u = 1; u <= n; ++u)
    {
        dfs(dfs, u, 0, u, 0);
    }

    for (int lay = 1; lay < laycnt; ++lay)
    {
        for (int i = 1; i <= n; ++i)
        {
            p[i][lay] = p[p[i][lay - 1]][lay - 1];
        }
    }

    constexpr uint64 mod = 998244353;
    std::vector dp(n + 1, std::vector(n + 1, std::array<uint64, laycnt>{}));

    for (int i = 1; i <= n; ++i)
    {
        for (int j = 1; j <= n; ++j)
        {
            dp[i][j][0] = p[i][0] + 1 == p[j][0];
        }
    }

    for (int lay = 1; lay < laycnt; ++lay)
    {
        for (int i = 1; i <= n; ++i)
        {
            for (int j = 1; j <= n; ++j)
            {
                dp[i][j][lay] = (dp[i][j][lay - 1] + dp[p[i][lay - 1]][p[j][lay - 1]][lay - 1]) % mod;
            }
        }
    }

    uint64 sum = 0;

    for (int i = 1; i <= n; ++i)
    {
        for (int j = 1; j <= n; ++j)
        {
            int x = i, y = j;

            for (int lay = 0; lay < laycnt; ++lay)
            {
                if (m & 1 << lay)
                {
                    (sum += dp[x][y][lay] * dis[i][j]) %= mod;

                    x = p[x][lay];
                    y = p[y][lay];
                }
            }
        }
    }

    std::cout << sum << '\n';

    return 0;
}
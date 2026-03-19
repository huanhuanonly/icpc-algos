/**
 * AtCoder Beginner Contest 441 (Promotion of Engineer Guild Fes)
 * 
 * => F - Must Buy ( @c 500 )
 * 
 * -> https://atcoder.jp/contests/abc441/tasks/abc441_f
 * 
 * Submissions ~> https://atcoder.jp/contests/abc441/submissions/72555386 By huanhuanonly
 * 
 * @b Knapsack-DP ( @a 0/1-knapsack-problem ) and @b Dfs
 * 
 * ----January 17, 2026 [21h:45m:07s]----
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

    int n, m;
    std::cin >> n >> m;

    std::vector<std::pair<int, int>> v(n + 1);

    for (int i = 1; i <= n; ++i)
    {
        std::cin >> v[i].first >> v[i].second;
    }

    std::vector dp(n + 1, std::vector(m + 1, uint64{}));

    for (int i = 1; i <= n; ++i)
    {
        for (int j = 1; j < v[i].first; ++j)
        {
            dp[i][j] = dp[i - 1][j];
        }

        for (int j = v[i].first; j <= m; ++j)
        {
            dp[i][j] = std::max(dp[i - 1][j], dp[i - 1][j - v[i].first] + v[i].second);
        }
    }

    std::vector<bool> vc(n + 1), vnc(n + 1);

    std::vector vis(n + 1, std::vector(m + 1, false));

    auto dfs = [&](const auto& self, int i, int j) -> void
    {
        if (i == 0)
        {
            return;
        }

        if (vis[i][j])
        {
            return;
        }

        vis[i][j] = true;

        if (dp[i][j] == dp[i - 1][j])
        {
            vnc[i] = true;
            self(self, i - 1, j);
        }

        if (j >= v[i].first and dp[i][j] == dp[i - 1][j - v[i].first] + v[i].second)
        {
            vc[i] = true;
            self(self, i - 1, j - v[i].first);
        }
    };

    const uint64 max = *std::ranges::max_element(dp[n]);

    for (int i = 1; i <= m; ++i)
    {
        if (dp[n][i] == max)
        {
            dfs(dfs, n, i);
        }
    }

    for (int i = 1; i <= n; ++i)
    {
        if (vc[i] and vnc[i])
        {
            std::cout.put('B');
        }
        else if (vc[i])
        {
            std::cout.put('A');
        }
        else
        {
            std::cout.put('C');
        }
    }

    return 0;
}
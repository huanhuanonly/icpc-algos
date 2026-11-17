/**
 * Educational DP Contest
 * 
 * => V - Subtree ( @c 100 )
 * 
 * -> https://atcoder.jp/contests/dp/tasks/dp_v
 * 
 * Submissions ~> https://atcoder.jp/contests/dp/submissions/75125643 By huanhuanonly
 * 
 * @b Tree-DP
 * 
 * ----April 20, 2026 [14h:55m:49s]----
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

    uint64 n, m;
    std::cin >> n >> m;

    std::vector<std::vector<int>> e(n + 1);

    for (int i = 0; i < n - 1; ++i)
    {
        int u, v;
        std::cin >> u >> v;

        e[u].push_back(v);
        e[v].push_back(u);
    }

    std::vector dp(n + 1, uint64{1});

    [&](this const auto& self, int u, int fa) -> void
    {
        for (const auto& i : e[u])
        {
            if (i == fa)
            {
                continue;
            }

            self(i, u);
            
            (dp[u] *= dp[i] + 1) %= m;
        }
    }(1, 0);

    std::vector<uint64> ans(n + 1);

    [&](this const auto& self, int u, int fa, uint64 s) -> void
    {
        std::vector<uint64> suf(e[u].size() + 1, 1);

        for (int i = e[u].size() - 1; i >= 0; --i)
        {
            if (e[u][i] == fa)
            {
                suf[i] = suf[i + 1];
            }
            else
            {
                suf[i] = suf[i + 1] * (dp[e[u][i]] + 1) % m;
            }
        }

        ans[u] = dp[u] * ++s % m;

        for (int i = 0; i < e[u].size(); ++i)
        {
            if (e[u][i] == fa)
            {
                continue;
            }

            self(e[u][i], u, s * suf[i + 1] % m);
            
            (s *= dp[e[u][i]] + 1) %= m;
        }
    }(1, 0, 0);

    for (int i = 1; i <= n; ++i)
    {
        std::cout << ans[i] << '\n';
    }

    return 0;
}
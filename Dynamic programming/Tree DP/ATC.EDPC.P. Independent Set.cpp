/**
 * Educational DP Contest
 * 
 * => P - Independent Set ( @c 100 )
 * 
 * -> https://atcoder.jp/contests/dp/tasks/dp_p
 * 
 * Submissions ~> https://atcoder.jp/contests/dp/submissions/75003510 By huanhuanonly
 * 
 * @b Tree-DP
 * 
 * ----April 17, 2026 [00h:41m:15s]----
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

    std::vector<std::vector<int>> e(n + 1);

    for (int i = 0; i < n - 1; ++i)
    {
        int u, v;
        std::cin >> u >> v;

        e[u].push_back(v);
        e[v].push_back(u);
    }

    constexpr uint64 mod = 1e9 + 7;

    std::vector dp(n + 1, std::array<uint64, 2>{1, 1});

    auto dfs = [&](const auto& self, int u, int fa) -> void
    {
        for (const auto& i : e[u])
        {
            if (i == fa)
            {
                continue;
            }

            self(self, i, u);

            (dp[u][0] *= dp[i][0] + dp[i][1]) %= mod;
            (dp[u][1] *= dp[i][0]) %= mod;
        }
    };

    dfs(dfs, 1, 0);

    std::cout << (dp[1][0] + dp[1][1]) % mod << '\n';

    return 0;
}
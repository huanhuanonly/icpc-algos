/**
 * Next DP Contest
 *
 * => B - DAG ( @c 2 )
 *
 * -> https://atcoder.jp/contests/ndpc/tasks/ndpc2026_b
 *
 * Submissions ~> https://atcoder.jp/contests/ndpc/submissions/78552236 By huanhuanonly
 *
 * @b Topological-DP
 * @b Dfs on @a Graphs
 *
 * ----August 21, 2026 [02h:31m:24s]----
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

        std::vector<std::vector<int>> e(n + 1);
        std::vector<int> indeg(n + 1);

        for (int i = 0; i < m; ++i)
        {
            int u, v;
            std::cin >> u >> v;

            e[u].push_back(v);
        }

        std::vector<bool> vis(n + 1);
        std::vector<bool> reachable(n + 1);

        auto dfs = [&](const auto& self, int u) -> void
        {
            if (vis[u])
            {
                return;
            }

            vis[u] = true;

            if (u == n)
            {
                reachable[u] = true;
            }

            for (const int& v : e[u])
            {
                self(self, v);
                reachable[u] = reachable[u] or reachable[v];
            }
        };

        dfs(dfs, 1);

        for (int u = 1; u <= n; ++u)
        {
            if (reachable[u])
            {
                for (const int& v : e[u])
                {
                    ++indeg[v];
                }
            }
        }

        constexpr uint64 mod = 998244353;

        std::vector<uint64> dp(n + 1);
        dp[1] = 1;

        std::queue<int> que;
        que.push(1);

        while (not que.empty())
        {
            const int u = que.front();
            que.pop();

            for (const int& v : e[u])
            {
                (dp[v] += dp[u]) %= mod;

                if (not --indeg[v])
                {
                    que.push(v);
                }
            }
        }

        std::cout << dp.back() << '\n';
    }

    return 0;
}
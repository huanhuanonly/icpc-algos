/**
 * Codeforces Round 733 (Div. 1 + Div. 2, based on VK Cup 2021 - Elimination (Engine))
 *
 * => D. Secret Santa ( @c 1600 )
 *
 * -> https://codeforces.com/contest/1530/problem/D
 *
 * Submissions ~> https://codeforces.com/contest/1530/submission/328244799 By huanhuanonly
 *
 * @b Bipartite-graph
 * @b Hungarian-algorithm
 *
 * ----July 09, 2025 [22h:31m:17s]----
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

    int _;
    std::cin >> _;

    while (_--)
    {
        int n;
        std::cin >> n;

        std::vector<int> a(n + 1);

        for (int i = 1; i <= n; ++i)
        {
            std::cin >> a[i];
        }

        std::vector<int>  num(n + 1);
        std::vector<bool> vis(n + 1);

        auto iota_view = std::views::iota(1, n + 1);
        std::set<int> remain(iota_view.begin(), iota_view.end());

        auto dfs = [&](const auto& self, int u) -> bool
        {
            if (vis[u])
            {
                return false;
            }

            vis[u] = true;

            if (num[a[u]] == 0 or self(self, num[a[u]]))
            {
                num[a[u]] = u;
                remain.erase(a[u]);
                return true;
            }

            for (int i : remain)
            {
                if (i == a[u] or i == u)
                {
                    continue;
                }

                if (num[i] == 0 or self(self, num[i]))
                {
                    num[i] = u;
                    remain.erase(i);
                    return true;
                }
            }

            return false;
        };

        for (int i = 1; i <= n; ++i)
        {
            dfs(dfs, i);
            vis.assign(vis.size(), false);
        }

        int k = 0;
        std::vector<int> ans(n + 1);

        for (int i = 1; i <= n; ++i)
        {
            ans[num[i]] = i;
            k += ans[num[i]] == a[num[i]];
        }

        std::cout << k << '\n';

        for (int i = 1; i <= n; ++i)
        {
            std::cout << ans[i] << " \n"[i == n];
        }
    }

    return 0;
}
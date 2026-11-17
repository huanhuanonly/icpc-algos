/**
 * Codeforces Round 346 (Div. 2)
 *
 * => E. New Reform ( @c 1600 )
 *
 * -> https://codeforces.com/contest/659/problem/E
 *
 * Submissions ~> https://codeforces.com/contest/659/submission/387596421 By huanhuanonly
 *
 * @b Dfs on @a Graphs
 *
 * ----August 19, 2026 [01h:32m:12s]----
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

    std::vector<std::vector<int>> e(n + 1);

    for (int i = 0; i < m; ++i)
    {
        int u, v;
        std::cin >> u >> v;

        e[u].push_back(v);
        e[v].push_back(u);
    }

    std::vector<bool> vis(n + 1);

    auto dfs = [&](const auto& self, int u, int fa) -> bool
    {
        if (vis[u])
        {
            return true;
        }

        vis[u] = true;

        bool found = false;

        for (const int& v : e[u])
        {
            if (v != fa)
            {
                found = self(self, v, u) or found;
            }
        }

        return found;
    };

    int cnt = 0;

    for (int i = 1; i <= n; ++i)
    {
        if (not vis[i])
        {
            cnt += not dfs(dfs, i, 0);
        }
    }

    std::cout << cnt << '\n';

    return 0;
}
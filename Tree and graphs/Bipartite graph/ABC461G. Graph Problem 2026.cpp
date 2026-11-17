/**
 * AtCoder Beginner Contest 461
 *
 * => G - Graph Problem 2026 ( @c 625 )
 *
 * -> https://atcoder.jp/contests/abc461/tasks/abc461_g
 *
 * Submissions ~> https://atcoder.jp/contests/abc461/submissions/77530689 By huanhuanonly
 *
 * @b Bipartite-graph ( @a maximum-independent-set )
 * @b Hungarian-algorithm
 *
 * ----July 17, 2026 [03h:01m:32s]----
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
    std::vector<int> record(n + 1);

    auto dfs = [&](const auto& self, int u) -> bool
    {
        if (vis[u])
        {
            return false;
        }

        vis[u] = true;

        for (const int& v : e[u])
        {
            if (not record[v] or self(self, record[v]))
            {
                record[v] = u;
                return true;
            }
        }

        return false;
    };

    int cnt = 0;

    for (int i = 1; i <= n; ++i)
    {
        vis.assign(vis.size(), false);
        cnt += dfs(dfs, i);
    }

    std::cout << (n + n - cnt) * 1013 << '\n';

    return 0;
}
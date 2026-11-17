/**
 * => P6062 [USACO05JAN] Muddy Fields G ( @c 提高+/省选− )
 *
 * -> https://www.luogu.com.cn/problem/P6062
 *
 * Submissions ~> https://www.luogu.com.cn/record/293537688 By huanhuanonly
 *
 * @b Bipartite-graph ( @a minimum-vertex-cover )
 * @b Hungarian-algorithm
 *
 * ----August 17, 2026 [18h:05m:38s]----
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

    int r, c;
    std::cin >> r >> c;

    std::vector<std::string> map(r);

    for (auto& s : map)
    {
        std::cin >> s;
    }

    std::vector lid(r, std::vector<int>(c)), rid(r, std::vector<int>(c));
    int lcnt = 0, rcnt = 0;

    for (int i = 0; i < r; ++i)
    {
        for (int j = 0; j < c; )
        {
            if (map[i][j] == '*')
            {
                for (; j < c and map[i][j] == '*'; lid[i][j] = lcnt, ++j);
                ++lcnt;
            }
            else
            {
                ++j;
            }
        }
    }

    for (int j = 0; j < c; ++j)
    {
        for (int i = 0; i < r; )
        {
            if (map[i][j] == '*')
            {
                for (; i < r and map[i][j] == '*'; rid[i][j] = rcnt, ++i);
                ++rcnt;
            }
            else
            {
                ++i;
            }
        }
    }

    std::vector<std::vector<int>> e(lcnt + rcnt);

    for (int i = 0; i < r; ++i)
    {
        for (int j = 0; j < c; ++j)
        {
            if (map[i][j] == '*')
            {
                e[lid[i][j]].push_back(lcnt + rid[i][j]);
                e[lcnt + rid[i][j]].push_back(lid[i][j]);
            }
        }
    }

    std::vector<int> record(e.size(), ~0);
    std::vector<bool> vis(e.size());

    auto dfs = [&](const auto& self, int u) -> bool
    {
        if (vis[u])
        {
            return false;
        }

        vis[u] = true;

        for (const auto& v : e[u])
        {
            if (not ~record[v] or self(self, record[v]))
            {
                record[v] = u;
                return true;
            }
        }

        return false;
    };

    int cnt = 0;

    for (int i = 0; i < lcnt; ++i)
    {
        vis.assign(vis.size(), false);
        cnt += dfs(dfs, i);
    }

    std::cout << cnt << '\n';

    return 0;
}
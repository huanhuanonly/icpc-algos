/**
 * AtCoder Beginner Contest 463
 *
 * => E - Roads and Gates ( @c 450 )
 *
 * -> https://atcoder.jp/contests/abc463/tasks/abc463_e
 *
 * Submissions ~> https://atcoder.jp/contests/abc463/submissions/76845701 By huanhuanonly
 *
 * @b Dijkstra
 *
 * ----June 20, 2026 [21h:43m:30s]----
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

    int64 n, m, y;
    std::cin >> n >> m >> y;

    std::vector<std::vector<std::pair<int64, int64>>> e(n + 1);

    for (int64 i = 0; i < m; ++i)
    {
        int64 u, v, w;
        std::cin >> u >> v >> w;

        e[u].emplace_back(v, w);
        e[v].emplace_back(u, w);
    }

    std::vector<int64> x(n + 1);

    for (int64 i = 1; i <= n; ++i)
    {
        std::cin >> x[i];
    }

    struct item
    {
        int64 to, w;

        bool operator<(const item& rhs) const
        {
            return w > rhs.w;
        }
    };

    std::priority_queue<item> que;
    que.emplace(1, 0);

    std::vector<int64> dis(n + 1);
    int64 min = x[1] + y;

    for (int64 i = 2; i <= n; ++i)
    {
        dis[i] = x[1] + y + x[i];
        min = std::min(min, dis[i] + x[i] + y);
        que.emplace(i, dis[i]);
    }

    std::vector<bool> vis(n + 1);


    while (not que.empty())
    {
        auto cur = que.top();
        que.pop();

        if (vis[cur.to])
        {
            continue;
        }

        vis[cur.to] = true;

        dis[cur.to] = std::min(dis[cur.to], min + x[cur.to]);
        min = std::min(min, dis[cur.to] + x[cur.to] + y);

        for (const auto& [v, w] : e[cur.to])
        {
            const int64 ndis = std::min(dis[cur.to] + w, min + x[v]);

            if (ndis < dis[v])
            {
                dis[v] = ndis;
                que.emplace(v, dis[v]);
            }
        }
    }

    for (int64 i = 2; i <= n; ++i)
    {
        std::cout << dis[i] << ' ';
    }

    return 0;
}
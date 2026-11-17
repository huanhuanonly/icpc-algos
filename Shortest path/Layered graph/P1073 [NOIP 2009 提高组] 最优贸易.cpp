/**
 * => P1073 [NOIP 2009 提高组] 最优贸易 ( @c 提高+/省选− )
 *
 * -> https://www.luogu.com.cn/problem/P1073
 *
 * Submissions ~> https://www.luogu.com.cn/record/217774010 By huanhuanonly
 *
 * @b Bfs based on @b Layered-graph
 *
 * ----May 19, 2025 [18h:51m:39s]----
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

    std::vector<int> v(n + 1);

    for (int i = 1; i <= n; ++i)
    {
        std::cin >> v[i];
    }

    using bset = std::bitset<101>;

    struct edge
    {
        int point;
        bset bs;
    };

    std::vector<std::vector<edge>> e(n + 1);

    for (int i = 1; i <= m; ++i)
    {
        int x, y, z;
        std::cin >> x >> y >> z;

        e[x].push_back(edge{y, {}});

        if (z == 2)
        {
            e[y].push_back(edge{x, {}});
        }
    }

    std::vector<bool> deleted(n + 1, true);

    {
        std::vector<std::vector<int>> re(n + 1);

        for (int u = 1; u < e.size(); ++u)
        {
            for (const auto& [v, bs] : e[u])
            {
                re[v].push_back(u);
            }
        }

        std::queue<int> que;
        que.push(n);
        deleted[n] = false;

        while (not que.empty())
        {
            int cur = que.front();
            que.pop();

            for (int i : re[cur])
            {
                if (deleted[i])
                {
                    deleted[i] = false;
                    que.push(i);
                }
            }
        }
    }

    std::vector<bset> vis(n + 1);

    int ans = 0;

    auto bfs = [&]() -> void
    {
        std::queue<edge> que;
        que.push({1, bset{}.set(v[1])});
        vis[1].set(v[1]);

        while (not que.empty())
        {
            auto cur = que.front();
            que.pop();

            for (const auto& i : e[cur.point])
            {
                if (deleted[i.point])
                {
                    continue;
                }

                auto next = cur.bs;
                next.set(v[i.point]);

                if ((vis[i.point] & next) == next)
                {
                    continue;
                }

                vis[i.point] |= next;

                if (auto f = vis[cur.point]._Find_first(); f != vis[cur.point].size())
                {
                    ans = std::max(ans, v[i.point] - static_cast<int>(f));
                }

                que.push({i.point, next});
            }
        }
    };

    bfs();

    std::cout << ans;

    return 0;
}
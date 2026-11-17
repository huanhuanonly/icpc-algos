/**
 * Codeforces Round 703 (Div. 2)
 *
 * => E. Paired Payment ( @c 2200 )
 *
 * -> https://codeforces.com/contest/1486/problem/E
 *
 * Submissions ~> https://codeforces.com/contest/1486/submission/262220999 By huanhuanonly
 *
 * @b Dijkstra based on @b Layered-graph
 *
 * ----May 23, 2024 [19h:21m:36s]----
*/

#include <bits/stdc++.h>

using uint    = unsigned int;
using llong   = long long int;
using ullong  = unsigned long long int;
using ldouble = long double;

int main(void)
{
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr), std::cout.tie(nullptr);

#ifdef __localhost
    ::freopen("in", "r", stdin);
    ::freopen("out", "w", stdout);
#endif

    int n, m;
    std::cin >> n >> m;

    struct edge
    {
        int to, w;

        bool operator<(const edge& nd) const
        {
            return this->w > nd.w;
        }
    };

    std::vector<std::vector<edge>> e(n + 1);

    for (int i = 0; i < m; ++i)
    {
        int u, v, w;
        std::cin >> u >> v >> w;

        e[u].push_back({v, w});
        e[v].push_back({u, w});
    }

    constexpr int inf = INT_MAX / 2;

    std::vector<std::vector<int>> dis(n + 1, std::vector<int>(50 + 1, inf));
    std::vector<std::vector<bool>> vis(n + 1, std::vector<bool>(50 + 1));

    auto bfs = [&]() -> void
    {
        struct node
        {
            int to, w, dp;

            bool operator<(const node& nd) const
            {
                return this->w > nd.w;
            }
        };

        std::priority_queue<node> que;
        que.push({1, 0, 0});
        dis[1][0] = 0;

        while (not que.empty())
        {
            auto [to, w, dp] = que.top();
            que.pop();

            if (vis[to][dp])
                continue;

            vis[to][dp] = true;

            if (dp)
                for (const auto& i : e[to])
                {
                    if (dis[to][dp] + std::pow(dp + i.w, 2) < dis[i.to][0])
                    {
                        dis[i.to][0] = dis[to][dp] + std::pow(dp + i.w, 2);
                        que.push({i.to, dis[i.to][0], 0});
                    }
                }
            else
                for (const auto& i : e[to])
                {
                    if (dis[to][dp] < dis[i.to][i.w])
                    {
                        dis[i.to][i.w] = dis[to][dp];
                        que.push({i.to, dis[i.to][i.w], i.w});
                    }
                }
        }
    };

    bfs();

    for (int i = 1; i <= n; ++i)
    {
        std::cout << (dis[i][0] != inf ? dis[i][0] : -1) << ' ';
    }

    return 0;
}
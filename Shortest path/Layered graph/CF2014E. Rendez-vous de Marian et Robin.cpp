/**
 * Codeforces Round 974 (Div. 3)
 *
 * => E. Rendez-vous de Marian et Robin ( @c 1800 )
 *
 * -> https://codeforces.com/contest/2014/problem/E
 *
 * Submissions ~> https://codeforces.com/contest/2014/submission/282709567 By huanhuanonly
 *
 * @b Dijkstra based on @b Layered-graph
 *
 * ----September 24, 2024 [22h:21m:50s]----
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

    int _;
    std::cin >> _;

    while (_--)
    {
        int n, m, h;
        std::cin >> n >> m >> h;

        std::vector<int> ha(h);

        for (int i = 0; i < h; ++i)
        {
            std::cin >> ha[i];
        }

        std::sort(ha.begin(), ha.end());

        struct edge
        {
            llong to, w;
        };

        std::vector<std::vector<edge>> e(n + 1);

        for (int i = 0; i < m; ++i)
        {
            llong u, v, w;
            std::cin >> u >> v >> w;

            e[u].push_back({v, w});
            e[v].push_back({u, w});
        }

        constexpr llong inf = LLONG_MAX / 2;

        std::vector<std::vector<llong>> disMarian(n + 1, std::vector<llong>(2, inf)), disRobin(n + 1, std::vector<llong>(2, inf));

        auto bfs = [&](llong start, decltype(disMarian)& dis) -> void
        {
            std::vector<std::vector<bool>> vis(n + 1, std::vector<bool>(2));

            struct node
            {
                llong point;
                llong step;
                llong layer;

                bool operator<(const node& nd) const
                {
                    return this->step > nd.step;
                }
            };

            std::priority_queue<node> que;

            llong startLayer = std::binary_search(ha.begin(), ha.end(), start);

            que.push({start, 0, startLayer});
            dis[start][startLayer] = 0;

            while (not que.empty())
            {
                node ct = que.top();
                que.pop();

                if (vis[ct.point][ct.layer])
                    continue;
                else
                    vis[ct.point][ct.layer] = true;

                for (const auto& i : e[ct.point])
                {
                    llong nextLayer = ct.layer or std::binary_search(ha.begin(), ha.end(), i.to);

                    if (dis[ct.point][ct.layer] + i.w / (ct.layer + 1) < dis[i.to][nextLayer])
                    {
                        dis[i.to][nextLayer] = dis[ct.point][ct.layer] + i.w / (ct.layer + 1);
                        que.push({i.to, dis[i.to][nextLayer], nextLayer});
                    }
                }
            }

            return;
        };


        bfs(1, disMarian);
        bfs(n, disRobin);

        if (disRobin[1][0] == inf and disRobin[1][1] == inf)
        {
            std::cout << -1 << '\n';
        }
        else
        {
            llong ans = LLONG_MAX;
            for (int i = 1; i <= n; ++i)
            {
                ans = std::min(ans, std::max(std::min(disMarian[i][0], disMarian[i][1]), std::min(disRobin[i][0], disRobin[i][1])));
            }

            std::cout << ans << '\n';
        }
    }

    return 0;
}
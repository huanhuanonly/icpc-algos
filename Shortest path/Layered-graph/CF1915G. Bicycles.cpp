/**
 * Codeforces Round 918 (Div. 4)
 *
 * => G. Bicycles ( @c 1800 )
 *
 * -> https://codeforces.com/contest/1915/problem/G
 *
 * Submissions ~> https://codeforces.com/contest/1915/submission/243079368 By huanhuanonly
 *
 * @b Dijkstra based on @b Layered-graph
 *
 * ----January 24, 2024 [12h:53m:27s]----
*/

#include <bits/stdc++.h>

using llong = long long;
using ullong = unsigned long long;

int main(void)
{
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr), std::cout.tie(nullptr);

#ifdef __localhost
    ::freopen("Input.txt", "r", stdin);
    ::freopen("Output.txt", "w", stdout);
#endif

    int _;
    std::cin >> _;

    while (_--)
    {
        int n, m;
        std::cin >> n >> m;

        constexpr const int N = 1001;

        struct edge { int to, w; };

        std::vector<edge> e[N];

        for (int i = 0; i < m; ++i)
        {
            int u, v, w;
            std::cin >> u >> v >> w;

            e[u].push_back({v, w});
            e[v].push_back({u, w});
        }

        std::vector<int> v(n + 1);
        for (int i = 1; i <= n; ++i) std::cin >> v[i];

        std::vector<std::vector<bool>> vis(n + 1, std::vector<bool>(N));
        std::vector<std::vector<llong>> dis(n + 1, std::vector<llong>(N, 0x3f3f3f3f3f3f3f3f));

        std::function<llong(int)> bfs = [&](int start) -> llong
        {
            struct node
            {
                int pos, speed;

                llong dis;

                bool operator()(const node& l, const node& r)
                {
                    return l.dis > r.dis;
                }
            };

            std::priority_queue<node, std::vector<node>, node> que;

            que.push({start, v[start], 0});
            dis[start][v[start]] = 0;

            while (not que.empty())
            {
                node ct = que.top();
                que.pop();

                if (vis[ct.pos][ct.speed]) continue;
                vis[ct.pos][ct.speed] = true;

                for (const auto& [to, w] : e[ct.pos])
                {
                    int speed = std::min(ct.speed, v[to]);

                    if (dis[ct.pos][ct.speed] + w * ct.speed < dis[to][speed])
                    {
                        dis[to][speed] = dis[ct.pos][ct.speed] + w * ct.speed;
                        que.push({to, speed, dis[to][speed]});
                    }
                }
            }

            llong ans = std::numeric_limits<decltype(ans)>::max();
            for (int i = 0; i < N; ++i) ans = std::min<decltype(ans)>(ans, dis[n][i]);
            return ans;
        };

        std::cout << bfs(1) << '\n';
    }

    return 0;
}
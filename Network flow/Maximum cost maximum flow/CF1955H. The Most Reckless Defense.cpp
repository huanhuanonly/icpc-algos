/**
 * Codeforces Round 938 (Div. 3)
 *
 * => H. The Most Reckless Defense ( @c 2300 )
 *
 * -> https://codeforces.com/contest/1955/problem/H
 *
 * Submissions ~> https://codeforces.com/contest/1955/submission/261784503 By huanhuanonly
 *
 * @b SPFA-Dinic for @a Maximum-cost-maximum-flow ( @a maximum-weighted-matching-for-bipartite-graphs )
 *
 * @see https://zhuanlan.zhihu.com/p/691549381
 *
 * ----May 20, 2024 [21h:15m:08s]----
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
        int n, m, k;
        std::cin >> n >> m >> k;

        std::vector<std::string> mp(n);

        for (int i = 0; i < n; ++i)
            std::cin >> mp[i];

        struct edge
        {
            int to, w, cost, rid;
        };

        constexpr int rlimit = 12;

        // [0] + {the number of towers} + {the maximum value of r} + s point + t point
        std::vector<std::vector<edge>> e(1 + k + rlimit + 2);

        auto add_edge = [&](int u, int v, int w, int c) -> void
        {
            e[u].push_back({v, w, c, int(e[v].size())});
            e[v].push_back({u, 0, -c, int(e[u].size() - 1)});
        };

        int s = k + rlimit + 1;
        int t = k + rlimit + 2;

        for (int kk = 1; kk <= k; ++kk)
        {
            int x, y, p;
            std::cin >> x >> y >> p;

            for (int r = 1, rpow = 3; r <= rlimit; ++r, rpow *= 3)
            {
                int sum = 0;

                for (int i = 1; i <= n; ++i)
                {
                    for (int j = 1; j <= m; ++j)
                    {
                        if (mp[i - 1][j - 1] == '#' and (x - i) * (x - i) + (y - j) * (y - j) <= r * r)
                        {
                            sum += p;
                        }
                    }
                }

                /**
                 * Here, this edge should be connected even when there is no contribution.
                 * Although its cost is zero, its flow is one.
                */
                add_edge(kk, k + r, 1, std::max(sum - rpow, 0));
            }

            add_edge(s, kk, 1, 0);
        }

        for (int i = 1; i <= rlimit; ++i)
            add_edge(k + i, t, 1, 0);

        constexpr int inf = INT_MAX / 2;

        std::vector<int> dis(e.size(), -inf), cur(e.size());
        std::vector<bool> vis(e.size());

        auto bfs = [&]() -> bool
        {
            std::fill(dis.begin(), dis.end(), -inf);
            std::fill(cur.begin(), cur.end(), 0);

            std::queue<int> que;

            que.push(s);
            dis[s] = 0;
            vis[s] = true;

            while (not que.empty())
            {
                int u = que.front();
                que.pop();

                vis[u] = false;

                for (const auto& i : e[u])
                {
                    if (i.w == 0)
                        continue;

                    if (dis[u] + i.cost > dis[i.to])
                    {
                        dis[i.to] = dis[u] + i.cost;

                        if (vis[i.to] == false)
                        {
                            vis[i.to] = true;
                            que.push(i.to);
                        }
                    }
                }
            }

            return dis[t] != -inf;
        };

        int cost = 0;

        std::function<int(int, int)> dfs = [&](int u, int limit) -> int
        {
            if (u == t)
                return limit;

            for (int c = cur[u]; c < e[u].size(); ++c)
            {
                cur[u] = c;

                auto& i = e[u][c];

                if (i.w == 0 or dis[u] + i.cost != dis[i.to] or vis[i.to])
                    continue;

                vis[i.to] = true;

                if (int flow = dfs(i.to, std::min(i.w, limit)); flow)
                {
                    i.w -= flow;
                    e[i.to][i.rid].w += flow;

                    cost += i.cost * flow;
                    return flow;
                }
                else
                {
                    dis[i.to] = -inf;
                }
            }

            return 0;
        };

        while (bfs())
        {
            while (dfs(s, inf))
            {
                vis.assign(e.size(), false);
            }
            vis.assign(e.size(), false);
        }

        std::cout << cost << '\n';
    }

    return 0;
}
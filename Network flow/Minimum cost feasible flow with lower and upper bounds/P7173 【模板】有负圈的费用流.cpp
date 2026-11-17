/**
 * => P7173 【模板】有负圈的费用流 ( @c 省选/NOI- )
 *
 * -> https://www.luogu.com.cn/problem/P7173
 *
 * Submissions ~> https://www.luogu.com.cn/record/160451873 By huanhuanonly
 *
 * @b SPFA-Dinic for @a Minimum-cost-feasible-flow-with-lower-and-upper-bounds ( @a with-a-source-and-sink )
 *
 * @see https://www.acwing.com/solution/content/147628
 *
 * ----May 27, 2024 [16h:44m:45s]----
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

    int n, m, s, t;
    std::cin >> n >> m >> s >> t;

    struct edge
    {
        int to, w, cost, rid;
    };

    std::vector<std::vector<edge>> e(n + 2 + 1);
    std::vector<int> inout(n + 1);

    int ss = e.size() - 1, tt = ss - 1;

    int maxflow = 0, cost = 0;

    constexpr int inf = INT_MAX / 2;

    auto add_edge = [&](int u, int v, int w, int cost) -> void
    {
        e[u].push_back({v, w, cost, int(e[v].size())});
        e[v].push_back({u, 0, -cost, int(e[u].size() - 1)});
    };

    for (int i = 1; i <= m; ++i)
    {
        int u, v, w, c;
        std::cin >> u >> v >> w >> c;

        if (c >= 0)
        {
            add_edge(u, v, w, c);
        }
        else
        {
            add_edge(v, u, w, -c);

            inout[u] -= w;
            inout[v] += w;

            cost += w * c;
        }
    }

    for (int i = 1; i <= n; ++i)
    {
        if (inout[i] > 0)
            add_edge(ss, i, inout[i], 0);
        else if (inout[i] < 0)
            add_edge(i, tt, -inout[i], 0);
    }

    std::vector<int> dis(e.size(), inf), cur(e.size());
    std::vector<bool> vis(e.size());

    int cs, ct;

    auto bfs = [&]() -> bool
    {
        std::fill(dis.begin(), dis.end(), inf);
        std::fill(cur.begin(), cur.end(), 0);

        std::queue<int> que;
        que.push(cs);
        dis[cs] = 0;

        while (not que.empty())
        {
            int u = que.front();
            que.pop();

            vis[u] = false;

            for (const auto& i : e[u])
            {
                if (i.w == 0)
                    continue;

                if (dis[u] + i.cost < dis[i.to])
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

        return dis[ct] != inf;
    };

    std::function<int(int, int)> dfs = [&](int u, int limit) -> int
    {
        if (u == ct)
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
                cost += flow * i.cost;
                return flow;
            }
            else
            {
                dis[i.to] = inf;
            }
        }

        return 0;
    };

    cs = ss, ct = tt;
    while (bfs())
    {
        while (dfs(cs, inf))
        {
            vis.assign(vis.size(), false);
        }
        vis.assign(vis.size(), false);
    }

    int flow;

    cs = s, ct = t;
    while (bfs())
    {
        while (flow = dfs(cs, inf))
        {
            maxflow += flow;
            vis.assign(vis.size(), false);
        }
        vis.assign(vis.size(), false);
    }

    std::cout << maxflow << ' ' << cost;

    return 0;
}
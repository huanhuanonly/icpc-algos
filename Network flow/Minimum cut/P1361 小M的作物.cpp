/**
 * => P1361 小M的作物 ( @c 省选/NOI- )
 *
 * -> https://www.luogu.com.cn/problem/P1361
 *
 * Submissions ~> https://www.luogu.com.cn/record/159180198 By huanhuanonly
 *
 * @b Dinic for @a Min-cut ( @a maximum-weight-closure-of-a-graph )
 *
 * @see https://zhuanlan.zhihu.com/p/553454908
 *
 * ----May 16, 2024 [19h:50m:28s]----
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

    int n;
    std::cin >> n;

    struct edge
    {
        int to, w, rid;
    };

    int sum = 0;

    std::vector<int> a(n + 1), b(n + 1);

    for (int i = 1; i <= n; ++i)
    {
        std::cin >> a[i];
        sum += a[i];
    }

    for (int i = 1; i <= n; ++i)
    {
        std::cin >> b[i];
        sum += b[i];
    }

    int m;
    std::cin >> m;

    std::vector<std::vector<edge>> e(n + m + m + 2 + 1);

    int s = n + m + m + 1, t = n + m + m + 2;

    for (int i = 1; i <= n; ++i)
    {
        e[s].push_back({i, a[i], int(e[i].size())});
        e[i].push_back({s, 0, int(e[s].size() - 1)});

        e[i].push_back({t, b[i], int(e[t].size())});
        e[t].push_back({i, 0, int(e[i].size() - 1)});
    }

    constexpr int inf = INT_MAX / 2;

    for (int i = 1; i <= m; ++i)
    {
        int k;
        std::cin >> k;

        int c1, c2;
        std::cin >> c1 >> c2;

        sum += c1 + c2;

        e[s].push_back({i + n, c1, int(e[i + n].size())});
        e[i + n].push_back({s, 0, int(e[s].size() - 1)});

        e[i + n + m].push_back({t, c2, int(e[t].size())});
        e[t].push_back({i + n + m, 0, int(e[i + n + m].size())});

        for (int j = 1; j <= k; ++j)
        {
            int c;
            std::cin >> c;

            e[i + n].push_back({c, inf, int(e[c].size())});
            e[c].push_back({i + n, 0, int(e[i + n].size() - 1)});

            e[c].push_back({i + n + m, inf, int(e[i + n + m].size())});
            e[i + n + m].push_back({c, 0, int(e[c].size() - 1)});
        }
    }

    std::vector<int> layer(e.size()), current(e.size());

    auto bfs = [&]() -> bool
    {
        std::fill(layer.begin(), layer.end(), 0);
        std::fill(current.begin(), current.end(), 0);

        std::queue<int> que;
        que.push(s);
        layer[s] = 1;

        while (not que.empty())
        {
            int u = que.front();
            que.pop();

            for (const auto& i : e[u])
            {
                if (i.w == 0 or layer[i.to])
                    continue;

                layer[i.to] = layer[u] + 1;
                que.push(i.to);
            }
        }

        return layer[t];
    };

    std::function<int(int, int)> dfs = [&](int u, int limit) -> int
    {
        if (u == t)
            return limit;

        for (int i = current[u]; i < e[u].size(); ++i)
        {
            current[u] = i;

            auto& eg = e[u][i];

            if (eg.w == 0 or layer[eg.to] != layer[u] + 1)
                continue;

            if (int flow = dfs(eg.to, std::min(eg.w, limit)); flow)
            {
                eg.w -= flow;
                e[eg.to][eg.rid].w += flow;
                return flow;
            }
            else
            {
                layer[eg.to] = 0;
            }
        }

        return 0;
    };

    int maxflow = 0, flow;

    while (bfs())
    {
        while (flow = dfs(s, inf))
        {
            maxflow += flow;
        }
    }

    std::cout << sum - maxflow;

    return 0;
}
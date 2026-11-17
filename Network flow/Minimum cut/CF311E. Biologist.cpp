/**
 * Codeforces Round 185 (Div. 1)
 *
 * => E. Biologist ( @c 2300 )
 *
 * -> https://codeforces.com/contest/311/problem/E
 *
 * Submissions ~> https://codeforces.com/contest/311/submission/261169633 By huanhuanonly
 *
 * @b Dinic for @a Min-cut ( @a maximum-weight-closure-of-a-graph )
 *
 * @see https://zhuanlan.zhihu.com/p/553454908
 *
 * ----May 16, 2024 [17h:05m:00s]----
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

    int n, m, g;
    std::cin >> n >> m >> g;

    std::vector<int> flag(n + 1);

    for (int i = 1; i <= n; ++i)
        std::cin >> flag[i];

    std::vector<int> v(n + 1);

    for (int i = 1; i <= n; ++i)
        std::cin >> v[i];

    int sum = 0;

    struct edge
    {
        int to, w, rid;
    };

    std::vector<std::vector<edge>> e(n + m + 2 + 1);

    int s = n + m + 1, t = n + m + 2;

    for (int i = 1; i <= n; ++i)
    {
        if (flag[i] == 0)
        {
            e[s].push_back({i, v[i], int(e[i].size())});
            e[i].push_back({s, 0, int(e[s].size() - 1)});
        }
        else
        {
            e[i].push_back({t, v[i], int(e[t].size())});
            e[t].push_back({i, 0, int(e[i].size() - 1)});
        }
    }

    constexpr int inf = INT_MAX / 2;

    for (int i = 1; i <= m; ++i)
    {
        int fg;
        std::cin >> fg;

        int w, k;
        std::cin >> w >> k;

        sum += w;

        std::vector<int> st(k);

        for (int& c : st)
            std::cin >> c;

        bool is_friend;
        std::cin >> is_friend;

        if (fg == 0)
        {
            e[s].push_back({n + i, w + (is_friend ? g : 0), int(e[n + i].size())});
            e[n + i].push_back({s, 0, int(e[s].size() - 1)});

            for (int j = 0; j < k; ++j)
            {
                const int& x = st[j];

                e[n + i].push_back({x, inf, int(e[x].size())});
                e[x].push_back({n + i, 0, int(e[n + i].size() - 1)});
            }
        }
        else
        {
            e[n + i].push_back({t, w + (is_friend ? g : 0), int(e[t].size())});
            e[t].push_back({n + i, 0, int(e[n + i].size() - 1)});

            for (int j = 0; j < k; ++j)
            {
                const int& x = st[j];

                e[x].push_back({n + i, inf, int(e[n + i].size())});
                e[n + i].push_back({x, 0, int(e[x].size() - 1)});
            }
        }
    }

    std::vector<int> layer(e.size());
    std::vector<int> current(e.size());

    auto bfs = [&]() -> bool
    {
        ::memset(layer.data(), 0, layer.size() * sizeof(decltype(layer)::value_type));
        ::memset(current.data(), 0, current.size() * sizeof(decltype(layer)::value_type));

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

        for (int cur = current[u]; cur < e[u].size(); ++cur)
        {
            current[u] = cur;
            auto& i = e[u][cur];

            if (i.w == 0 or layer[i.to] != layer[u] + 1)
                continue;

            if (int flow = dfs(i.to, std::min(i.w, limit)); flow)
            {
                i.w -= flow;
                e[i.to][i.rid].w += flow;
                return flow;
            }
            else
            {
                layer[i.to] = 0;
            }
        }

        return 0;
    };

    int maxflow = 0;
    int flow;

    while (bfs())
    {
        while (flow = dfs(s, inf))
            maxflow += flow;
    }

    std::cout << sum - maxflow << '\n';

    return 0;
}
/**
 * => P2762 太空飞行计划问题 ( @c 省选/NOI- )
 *
 * -> https://www.luogu.com.cn/problem/P2762
 *
 * Submissions ~> https://www.luogu.com.cn/record/159238224 By huanhuanonly
 *
 * @b Dinic for @a Min-cut ( @a maximum-weight-closure-of-a-graph )
 *
 * @see https://zhuanlan.zhihu.com/p/553454908
 *
 * ----May 17, 2024 [15h:04m:04s]----
*/

#include <bits/stdc++.h>

using uint    = unsigned int;
using llong   = long long int;
using ullong  = unsigned long long int;
using ldouble = long double;

void add_edge(auto& e, int from, int to, int w)
{
    e[from].push_back({to, w, int(e[to].size())});
    e[to].push_back({from, 0, int(e[from].size() - 1)});
}

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
        int to, w, rid;
    };

    std::vector<std::vector<edge>> e(n + m + 2 + 1);

    constexpr int inf = INT_MAX / 2;

    int sum = 0;

    int s = n + m + 1, t = n + m + 2;

    std::vector<std::pair<int, std::vector<int>>> data(n + 1);

    std::string str;

    for (int i = 1; i <= n; ++i)
    {
        std::cin >> data[i].first;
        std::cin.get();

        sum += data[i].first;

        std::getline(std::cin, str);

        while (str.back() == '\r')
            str.pop_back();

        std::stringstream ss;
        ss << str;

        int x;
        while (ss >> x)
        {
            data[i].second.push_back(x);
        }
    }

    std::vector<int> v(m + 1);

    for (int i = 1; i <= m; ++i)
    {
        std::cin >> v[i];
        add_edge(e, n + i, t, v[i]);
    }

    for (int i = 1; i <= n; ++i)
    {
        add_edge(e, s, i, data[i].first);

        for (int x : data[i].second)
        {
            add_edge(e, i, n + x, inf);
        }
    }

    std::vector<int> layer(e.size()), current(e.size());

    auto bfs = [&]() -> bool
    {
        ::memset(layer.data(), 0, layer.size() * sizeof(decltype(layer)::value_type));
        ::memset(current.data(), 0, current.size() * sizeof(decltype(current)::value_type));

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

    for (int i = 1; i <= n; ++i)
    {
        if (layer[i])
        {
            std::cout << i << ' ';
        }
    }

    std::cout.put('\n');

    for (int i = n + 1; i <= n + m; ++i)
    {
        if (layer[i])
        {
            std::cout << i - n << ' ';
        }
    }

    std::cout.put('\n');

    std::cout << sum - maxflow;

    return 0;
}
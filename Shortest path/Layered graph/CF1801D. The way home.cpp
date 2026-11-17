/**
 * Codeforces Round 857 (Div. 1)
 *
 * => D. The way home ( @c 2100 )
 *
 * -> https://codeforces.com/contest/1801/problem/D
 *
 * Submissions ~> https://codeforces.com/contest/1801/submission/250479926 By huanhuanonly
 *
 * @b Dijkstra based on @b Layered-graph
 *
 * ----March 10, 2024 [16h:49m:46s]----
*/

#include <bits/stdc++.h>

using uint = unsigned int;
using llong = long long int;
using ullong = unsigned long long int;
using ldouble = long double;

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
        ullong n, m, p;
        std::cin >> n >> m >> p;

        std::vector<ullong> w(n + 1);
        std::for_each(w.begin() + 1, w.end(), [](ullong& i) -> void { std::cin >> i; });

        struct edge
        {
            ullong to, s;
        };

        std::vector<std::vector<edge>> e(n + 1);

        for (int i = 0; i < m; ++i)
        {
            ullong u, v, s;
            std::cin >> u >> v >> s;

            e[u].push_back({v, s});
        }

        constexpr const ullong inf = ULLONG_MAX / 2 - 1;

        // [the current city number][the city number with the maximum profit]
        std::vector<std::vector<ullong>> dp_cnt(n + 1, std::vector<ullong>(n + 1, inf));

        // Records maximum money
        std::vector<std::vector<ullong>> dp_money(n + 1, std::vector<ullong>(n + 1));

        std::vector<std::vector<ullong>> vis(n + 1, std::vector<ullong>(n + 1));

        auto bfs = [&](ullong start) -> llong
        {
            struct node
            {
                ullong point, cnt, money;

                ullong state;

                bool operator<(const node& rv) const
                {
                    if (this->cnt != rv.cnt)
                        return this->cnt > rv.cnt;
                    else
                        return this->money < rv.money;
                };
            };

            std::priority_queue<node> que;
            que.push({start, 0, p, start});
            dp_cnt[start][start] = 0;
            dp_money[start][start] = p;

            while (not que.empty())
            {
                node ct = que.top();
                que.pop();

                if (vis[ct.point][ct.state])
                    continue;

                vis[ct.point][ct.state] = true;

                for (const auto& [to, s] : e[ct.point])
                {
                    ullong cnt = dp_cnt[ct.point][ct.state];
                    ullong money = ct.money;

                    if (s > ct.money)
                    {
                        cnt += ullong(std::ceil(double(s - ct.money) / w[ct.state]));
                        money += ullong(std::ceil(double(s - ct.money) / w[ct.state])) * w[ct.state];
                    }

                    money -= s;

                    ullong state = ct.state;

                    if (w[to] > w[state])
                        state = to;

                    if (cnt < dp_cnt[to][state])
                    {
                        dp_cnt[to][state] = cnt;
                        dp_money[to][state] = money;
                        que.push({to, cnt, money, state});
                    }
                    if (cnt == dp_cnt[to][state] and money > dp_money[to][state])
                    {
                        vis[to][state] = false;
                        dp_money[to][state] = money;
                        que.push({to, cnt, money, state});
                    }
                }
            }

            llong ans = inf;

            for (int i = 1; i <= n; ++i)
                ans = std::min(ans, llong(dp_cnt[n][i]));

            return ans != inf ? ans : -1;
        };

        std::cout << bfs(1) << '\n';
    }

    return 0;
}
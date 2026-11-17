/**
 * Toyota Programming Contest 2024#3（AtCoder Beginner Contest 344）
 *
 * => F - Earn to Advance ( @c 550 )
 *
 * -> https://atcoder.jp/contests/abc344/tasks/abc344_f
 *
 * Submissions ~> https://atcoder.jp/contests/abc344/submissions/51126743 By huanhuanonly
 *
 * @b Dijkstra based on @b Layered-graph
 *
 * ----March 10, 2024 [19h:58m:50s]----
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

    int n;
    std::cin >> n;

    std::array<std::vector<std::vector<llong>>, 3> mp
        {
            std::vector<std::vector<llong>>(n, std::vector<llong>(n)),
            std::vector<std::vector<llong>>(n, std::vector<llong>(n)),
            std::vector<std::vector<llong>>(n, std::vector<llong>(n))
        };

    const std::pair<int, int> d[] = {{0, 0}, {0, 1}, {1, 0}};

    for (int k = 0; k < mp.size(); ++k)
    {
        for (int i = 0; i < n - (k == 2); ++i)
        {
            for (int j = 0; j < n - (k == 1); ++j)
            {
                std::cin >> mp[k][i][j];
            }
        }
    }


    auto bfs = [&]() -> llong
    {
        constexpr const llong inf = 0x3f3f3f3f3f3f3f3fll;

        llong dp_cnt[n][n][n][n];
        ::memset(dp_cnt, 0x3f, sizeof(dp_cnt));

        llong dp_money[n][n][n][n];
        ::memset(dp_money, 0, sizeof(dp_money));

        bool vis[n][n][n][n];
        ::memset(vis, false, sizeof(vis));

        struct node
        {
            int x, y;
            llong cnt, money;

            std::pair<int, int> state;

            bool operator<(const node& rv) const
            {
                if (this->cnt != rv.cnt)
                    return this->cnt > rv.cnt;
                else
                    return this->money < rv.money;
            }
        };

        std::priority_queue<node> que;
        que.push({0, 0, 0, 0, {0, 0}});
        dp_cnt[0][0][0][0] = 0;
        dp_money[0][0][0][0] = 0;

        while (not que.empty())
        {
            node ct = que.top();
            que.pop();

            if (vis[ct.x][ct.y][ct.state.first][ct.state.second])
                continue;

            vis[ct.x][ct.y][ct.state.first][ct.state.second] = true;

            for (int i = 1; i < 3; ++i)
            {
                int x = ct.x + d[i].first, y = ct.y + d[i].second;

                if (x < 0 or x >= n or y < 0 or y >= n)
                    continue;

                int sx = ct.state.first, sy = ct.state.second;

                if (mp[0][x][y] > mp[0][sx][sy])
                {
                    sx = x, sy = y;
                }

                llong cnt = dp_cnt[ct.x][ct.y][ct.state.first][ct.state.second];
                llong money = ct.money;

                if (money < mp[i][ct.x][ct.y])
                {
                    cnt += llong(std::ceil(double(mp[i][ct.x][ct.y] - money) / mp[0][ct.state.first][ct.state.second]));
                    money += llong(std::ceil(double(mp[i][ct.x][ct.y] - money) / mp[0][ct.state.first][ct.state.second])) * mp[0][ct.state.first][ct.state.second];
                }

                money -= mp[i][ct.x][ct.y];

                if (cnt + 1 < dp_cnt[x][y][sx][sy])
                {
                    dp_money[x][y][sx][sy] = money;
                    dp_cnt[x][y][sx][sy] = cnt + 1;
                    que.push({x, y, cnt + 1, money, {sx, sy}});
                }
                else if (cnt + 1 == dp_cnt[x][y][sx][sy] and money > dp_money[x][y][sx][sy])
                {
                    dp_money[x][y][sx][sy] = money;

                    vis[x][y][sx][sy] = false;

                    que.push({x, y, cnt + 1, money, {sx, sy}});
                }
            }
        }

        llong ans = inf;

        for (int i = 0; i < n; ++i)
            for (int j = 0; j < n; ++j)
                ans = std::min(ans, dp_cnt[n - 1][n - 1][i][j]);

        return ans != inf ? ans : -1;
    };

    std::cout << bfs();

    return 0;
}
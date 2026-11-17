/**
 * Codeforces Round 221 (Div. 1)
 *
 * => C. Circling Round Treasures ( @c 2600 )
 *
 * -> https://codeforces.com/contest/375/problem/C
 *
 * Submissions ~> https://codeforces.com/contest/375/submission/250065038 By huanhuanonly
 *
 * @b Bfs based on @b Layered-graph
 * @b Geometry ( @a ray-method )
 *
 * ----March 07, 2024 [19h:43m:32s]----
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

    int n, m;
    std::cin >> n >> m;

    std::pair<int, int> start;

    std::vector<std::pair<int, int>> goods(8), bads;

    int t = 0;

    std::vector<std::vector<char>> mp(n, std::vector<char>(m));
    for (int i = 0; i < n; ++i)
        for (int j = 0; j < m; ++j)
        {
            std::cin >> mp[i][j];

            if (mp[i][j] == 'S')
                start = std::make_pair(i, j);

            else if (std::isdigit(mp[i][j]))
                goods[mp[i][j] - '0' - 1] = std::make_pair(i, j),
                t = std::max(t, mp[i][j] - '0');

            else if (mp[i][j] == 'B')
                bads.push_back({i, j});
        }

    goods.resize(t);
    goods.insert(goods.end(), bads.begin(), bads.end());

    std::vector<int> v(t);
    for (int i = 0; i < v.size(); ++i)
        std::cin >> v[i];

    auto check = [&](int x, int y, int sx, int sy, int tx, int ty) -> bool
    {
        return y <= ty and ((sx < tx and x == sx) or (sx > tx and x == tx));
    };

    std::vector<std::vector<std::vector<int>>>  dis(n, std::vector<std::vector<int>>(m, std::vector<int>(1 << goods.size(), 0x3f3f3f3f)));
    std::vector<std::vector<std::vector<bool>>> vis(n, std::vector<std::vector<bool>>(m, std::vector<bool>(1 << goods.size())));

    auto bfs = [&]() -> void
    {
        struct node
        {
            int x, y, dp;
        };

        std::queue<node> que;

        que.push({start.first, start.second, 0});
        dis[start.first][start.second][0] = 0;
        vis[start.first][start.second][0] = true;

        while (not que.empty())
        {
            node ct = que.front();
            que.pop();

            const std::pair<int, int> d[] = {{1, 0}, {0, 1}, {-1, 0}, {0, -1}};

            for (const auto& [dx, dy] : d)
            {
                int x = ct.x + dx, y = ct.y + dy, dp = ct.dp;

                if (x < 0 or x >= n or y < 0 or y >= m)
                    continue;

                if (mp[x][y] != 'S' and mp[x][y] != '.')
                    continue;

                if (dx)
                {
                    for (int i = 0; i < goods.size(); ++i)
                        if (check(goods[i].first, goods[i].second, ct.x, ct.y, x, y))
                            dp ^= 1 << i;
                }

                if (vis[x][y][dp])
                    continue;

                vis[x][y][dp] = true;

                dis[x][y][dp] = dis[ct.x][ct.y][ct.dp] + 1;
                que.push({x, y, dp});
            }
        }

        return;
    };

    bfs();

    int ans = 0;

    for (int i = 0; i < (1 << t); ++i)
    {
        int sum = 0;
        for (int j = 0; j < t; ++j)
        {
            if (i & (1 << j))
            {
                sum += v[j];
            }
        }

        ans = std::max(ans, sum - dis[start.first][start.second][i]);
    }

    std::cout << ans << '\n';

    return 0;
}
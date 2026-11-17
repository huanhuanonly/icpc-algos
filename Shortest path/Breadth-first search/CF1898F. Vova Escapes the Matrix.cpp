/**
 * Codeforces Round 910 (Div. 2)
 *
 * => F. Vova Escapes the Matrix ( @c 2600 )
 *
 * -> https://codeforces.com/contest/1898/problem/F
 *
 * Submissions ~> https://codeforces.com/contest/1898/submission/317338546 By huanhuanonly
 *
 * @b Breadth-first-search
 *
 * ----April 26, 2025 [21h:19m:28s]----
*/

/// @brief This is an @c interesting problem!

#include <bits/stdc++.h>

using int8 = signed char;
using int16 = short;
using int32 = int;
using int64 = long long;

using uint8 = unsigned char;
using uint16 = unsigned short;
using uint32 = unsigned int;
using uint64 = unsigned long long;

#ifdef __GNUC__
using int128 = __int128;
using uint128 = unsigned __int128;
#endif

using real32 = float;
using real64 = double;
using real128 = long double;

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
        int n, m;
        std::cin >> n >> m;

        std::vector<std::string> mp(n, std::string(m, ' '));

        int cnt = 0;
        std::pair<int, int> start;

        for (int i = 0; i < n; ++i)
        {
            for (int j = 0; j < m; ++j)
            {
                std::cin >> mp[i][j];
                cnt += (mp[i][j] == '.');

                if (mp[i][j] == 'V')
                {
                    start = {i, j};
                }
            }
        }

        auto zip = [&](int x, int y) -> int
        {
            return x * m + y + 1;
        };

        std::vector<std::vector<std::pair<int, int>>> dis(n, std::vector<std::pair<int, int>>(m));

        constexpr std::pair<int, int> d[] = {{1, 0}, {0, 1}, {-1, 0}, {0, -1}};


        auto bfs = [&](const std::vector<std::pair<int, int>>& starts) -> void
        {
            std::vector<std::vector<int>> vis(n, std::vector<int>(m));
            std::queue<std::tuple<int, int, int, int>> que;

            for (const auto& [sx, sy] : starts)
            {
                if (mp[sx][sy] != '#')
                {
                    que.push({sx, sy, 0, zip(sx, sy)});
                    vis[sx][sy] = zip(sx, sy);
                }
            }

            while (not que.empty())
            {
                auto [cx, cy, cw, tag] = que.front();
                que.pop();

                ++cw;

                for (const auto& [dx, dy] : d)
                {
                    int nx = cx + dx, ny = cy + dy;

                    if (nx >= 0 and nx < n and ny >= 0 and ny < m and ~vis[nx][ny] and vis[nx][ny] != tag and mp[nx][ny] != '#')
                    {
                        if (vis[nx][ny])
                            vis[nx][ny] = ~0;
                        else
                            vis[nx][ny] = tag;

                        if (dis[nx][ny].first == 0)
                            dis[nx][ny].first = cw;
                        else if (cw < dis[nx][ny].first)
                            dis[nx][ny].second = std::exchange(dis[nx][ny].first, cw);
                        else if (dis[nx][ny].second == 0 or cw < dis[nx][ny].second)
                            dis[nx][ny].second = cw;
                        else
                            continue;

                        que.push({nx, ny, cw, tag});
                    }
                }
            }
        };

        std::vector<std::pair<int, int>> starts;

        for (int i = 0; i < n; ++i)
        {
            starts.push_back({i, 0});
            starts.push_back({i, m - 1});
        }

        for (int i = 0; i < m; ++i)
        {
            starts.push_back({0, i});
            starts.push_back({n - 1, i});
        }

        bfs(starts);

        int min = std::numeric_limits<int>::max();

        auto bfs_from_startingpoint = [&]() -> std::pair<int, int>
        {
            // {endpoint count, shortest distance}
            std::pair<int, int> res{0, std::numeric_limits<int>::max()};

            std::queue<std::tuple<int, int, int>> que;
            std::vector<std::vector<bool>> vis(n, std::vector<bool>(m));

            que.push({start.first, start.second, 0});
            vis[start.first][start.second] = true;

            while (not que.empty())
            {
                auto [cx, cy, cdis] = que.front();
                que.pop();

                if (cx == 0 or cx == n - 1 or cy == 0 or cy == m - 1)
                {
                    ++res.first;
                    res.second = std::min(res.second, cdis);

                    min = std::min(min, dis[cx][cy].first + cdis);
                }
                else
                {
                    min = std::min(min, dis[cx][cy].first + dis[cx][cy].second + cdis);
                }

                for (const auto& [dx, dy] : d)
                {
                    int nx = cx + dx, ny = cy + dy;

                    if (nx >= 0 and nx < n and ny >= 0 and ny < m and not vis[nx][ny] and mp[nx][ny] != '#')
                    {
                        que.push({nx, ny, cdis + 1});
                        vis[nx][ny] = true;
                    }
                }
            }

            return res;
        };

        switch (auto [endcnt, dist] = bfs_from_startingpoint(); endcnt)
        {
        case 0:
            std::cout << cnt << '\n';
            break;

        case 1:
            std::cout << cnt - dist << '\n';
            break;

        default:
            std::cout << cnt - min << '\n';
            break;
        }
    }

    return 0;
}
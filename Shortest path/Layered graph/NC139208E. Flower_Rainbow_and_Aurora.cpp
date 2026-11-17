/**
 * 牛客小白月赛136
 *
 * => E-Flower_Rainbow_and_Aurora ( @c 1700 )
 *
 * -> https://ac.nowcoder.com/acm/contest/139208/E
 *
 * Submissions ~> https://ac.nowcoder.com/acm/contest/view-submission?submissionId=84602982 By huanhuanonly
 *
 * @b Bfs based on @b Layered-graph
 *
 * ----August 26, 2026 [00h:54m:14s]----
*/

#include <bits/stdc++.h>

using int8 = signed char;
using int16 = short;
using int32 = int;
using int64 = long long;

using uint8 = unsigned char;
using uint16 = unsigned short;
using uint32 = unsigned int;
using uint64 = unsigned long long;

#if defined(__SIZEOF_INT128__)
using int128 = __int128;
using uint128 = unsigned __int128;
#endif

using real32 = float;
using real64 = double;

#if defined(__SIZEOF_FLOAT80__)
using real80 = __float80;
#endif

#if defined(__SIZEOF_FLOAT128__)
using real128 = __float128;
#endif

int main(void)
{
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);

#ifdef __huanhuanonly_localhost
    ::freopen("in", "r", stdin);
    ::freopen("out", "w", stdout);
#endif

    int _;
    std::cin >> _;

    while (_--)
    {
        int n, m;
        std::cin >> n >> m;

        std::string s;
        std::cin >> s;

        std::vector<std::string> map(n);

        for (auto& i : map)
        {
            std::cin >> i;
        }

        constexpr auto inf = std::numeric_limits<int>::max() / 2;

        std::vector vis(n, std::vector(m, std::array<bool, 3>{}));
        std::vector dis(n, std::vector(m, std::array{inf, inf, inf}));
        dis.back().back().fill(0);

        std::queue<std::tuple<int, int, int>> que;
        que.emplace(n - 1, m - 1, 0);
        que.emplace(n - 1, m - 1, 1);
        que.emplace(n - 1, m - 1, 2);

        while (not que.empty())
        {
            const auto [x, y, p] = que.front();
            que.pop();

            if (vis[x][y][p])
            {
                continue;
            }

            vis[x][y][p] = true;

            for (const auto& [dx, dy] : {std::pair{0, 1}, {1, 0}, {0, -1}, {-1, 0}})
            {
                for (int k = 1; k <= 3; ++k)
                {
                    const int nx = x + dx * k, ny = y + dy * k, np = (p + 3 - 1) % 3;

                    if (nx >= 0 and nx < n and ny >= 0 and ny < m and map[x][y] == s[(np + k - 1) % 3] and dis[x][y][p] + 1 < dis[nx][ny][np])
                    {
                        que.emplace(nx, ny, np);
                        dis[nx][ny][np] = dis[x][y][p] + 1;
                    }
                }
            }
        }

        for (int i = 0; i < n; ++i)
        {
            for (int j = 0; j < m; ++j)
            {
                if (dis[i][j][0] != inf)
                {
                    std::cout << dis[i][j][0] << " \n"[j + 1 == m];
                }
                else
                {
                    std::cout << "-1" << " \n"[j + 1 == m];
                }
            }
        }
    }

    return 0;
}
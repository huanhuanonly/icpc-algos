/**
 * 2025 National Invitational of CCPC (Zhengzhou), 2025 CCPC Henan Provincial Collegiate Programming Contest
 *
 * => F. 幻形之路
 *
 * -> https://codeforces.com/gym/105941/problem/F
 *
 * Submissions ~> https://codeforces.com/gym/105941/submission/391018442 By huanhuanonly
 *
 * @b Breadth-first-search
 *
 * ----September 17, 2026 [19h:42m:15s]----
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

        std::vector<std::string> map(n);

        for (auto& i : map)
        {
            std::cin >> i;
        }

        const std::pair<int, int> d[]{{0, 1}, {1, 0}, {0, -1}, {-1, 0}};

        std::queue<std::tuple<int, int, int>> que;

        std::vector vis(n, std::vector<bool>(m));
        std::vector end(n, std::vector<bool>(m));

        auto dfs1 = [&](const auto& self, int x, int y) -> void
        {
            if (not (0 <= x and x < n and 0 <= y and y < m and map[x][y] == '.') or vis[x][y])
            {
                return;
            }

            vis[x][y] = true;
            que.emplace(x, y, 0);

            for (const auto& [dx, dy] : d)
            {
                self(self, x + dx, y + dy);
            }
        };

        auto dfs2 = [&](const auto& self, int x, int y) -> void
        {
            if (not (0 <= x and x < n and 0 <= y and y < m and map[x][y] == '.') or end[x][y])
            {
                return;
            }

            end[x][y] = true;

            for (const auto& [dx, dy] : d)
            {
                self(self, x + dx, y + dy);
            }
        };

        dfs1(dfs1, 0, 0);
        dfs2(dfs2, n - 1, m - 1);

        int ans = std::numeric_limits<int>::max() / 2;

        while (not que.empty())
        {
            const auto [x, y, dis] = que.front();
            que.pop();

            if (end[x][y])
            {
                ans = dis;
                break;
            }

            for (const auto& [dx, dy] : d)
            {
                const int nx = x + dx, ny = y + dy;

                if (0 <= nx and nx < n and 0 <= ny and ny < m and not vis[nx][ny])
                {
                    vis[nx][ny] = true;
                    que.emplace(nx, ny, dis + 1);
                }
            }
        }

        std::cout << std::max(ans - 1, 0) << '\n';
    }

    return 0;
}
/**
 * AtCoder Beginner Contest 472
 *
 * => D - Bomber Mad ( @c 400 )
 *
 * -> https://atcoder.jp/contests/abc472/tasks/abc472_d
 *
 * Submissions ~> https://atcoder.jp/contests/abc472/submissions/78612958 By huanhuanonly
 *
 * @b Breadth-first-search ( @a multiple-source )
 *
 * ----August 22, 2026 [20h:32m:14s]----
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

    int h, w, k;
    std::cin >> h >> w >> k;

    std::vector<std::string> map(h);

    std::vector<bool> row(h), col(w);

    for (int i = 0; i < h; ++i)
    {
        std::cin >> map[i];

        for (int j = 0; j < w; ++j)
        {
            if (map[i][j] == '#')
            {
                row[i] = col[j] = true;
            }
        }
    }

    std::vector vis(h, std::vector<bool>(w));
    std::queue<std::tuple<int, int, int>> que;

    for (int i = 0; i < h; ++i)
    {
        if (not row[i])
        {
            for (int j = 0; j < w; ++j)
            {
                if (not col[j])
                {
                    que.emplace(i, j, 0);
                }
            }
        }
    }

    while (not que.empty())
    {
        const auto [x, y, c] = que.front();
        que.pop();

        if (c > k or vis[x][y])
        {
            continue;
        }

        vis[x][y] = true;

        for (const auto& [dx, dy] : {std::pair{1, 0}, {0, 1}, {-1, 0}, {0, -1}})
        {
            const int nx = x + dx, ny = y + dy;

            if (nx >= 0 and nx < h and ny >= 0 and ny < w and map[nx][ny] == '.')
            {
                que.emplace(nx, ny, c + 1);
            }
        }
    }

    int cnt = 0;

    for (int i = 0; i < h; ++i)
    {
        for (int j = 0; j < w; ++j)
        {
            if (vis[i][j])
            {
                ++cnt;
            }
        }
    }

    std::cout << cnt << '\n';

    return 0;
}
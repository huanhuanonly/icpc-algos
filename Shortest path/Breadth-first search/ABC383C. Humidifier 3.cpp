/**
 * Daiwa Securities Co. Ltd. Programming Contest 2024（AtCoder Beginner Contest 383）
 *
 * => C - Humidifier 3 ( @c 350 )
 *
 * -> https://atcoder.jp/contests/abc383/tasks/abc383_c
 *
 * Submissions ~> https://atcoder.jp/contests/abc383/submissions/60525459 By huanhuanonly
 *
 * @b Breadth-first-search
 *
 * ----December 08, 2024 [11h:19m:19s]----
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

    uint32 h, w, D;
    std::cin >> h >> w >> D;

    std::vector<std::string> mp(h);

    std::vector<std::pair<uint32, uint32>> log;
    log.reserve(h * w);

    for (uint32 i = 0; i < h; ++i)
    {
        std::cin >> mp[i];

        for (int j = 0; j < w; ++j)
        {
            if (mp[i][j] == 'H')
            {
                log.push_back(std::make_pair(i, j));
            }
        }
    }

    std::vector<std::vector<bool>> vis(h, std::vector<bool>(w));

    auto dis = [](int32 x0, int32 y0, int32 x1, int32 y1) -> uint32
    {
        return std::abs(x0 - x1) + std::abs(y0 - y1);
    };

    auto bfs = [&]() -> uint32
    {
        uint32 ans = 0;

        struct node
        {
            uint32 x, y, w;
        };

        std::queue<node> que;

        for (const auto& [x, y] : log)
        {
            que.push({x, y, 0});
            vis[x][y] = true;
            ++ans;
        }

        const std::pair<uint32, uint32> d[] = {{1, 0}, {0, 1}, {-1, 0}, {0, -1}};

        while (not que.empty())
        {
            auto cur = que.front();
            que.pop();

            for (const auto& [dx, dy] : d)
            {
                uint32 cx = cur.x + dx, cy = cur.y + dy;

                if (cx >= 0 and cx < h and cy >= 0 and cy < w)
                if (mp[cx][cy] == '.' and vis[cx][cy] == false and cur.w + 1 <= D)
                {
                    que.push({cx, cy, cur.w + 1});
                    vis[cx][cy] = true;
                    ++ans;
                }
            }
        }

        return ans;
    };

    std::cout << bfs();

    return 0;
}
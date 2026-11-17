/**
 * Tinkoff Challenge - Elimination Round
 *
 * => B. Igor and his way to work ( @c 1600 )
 *
 * -> https://codeforces.com/contest/793/problem/B
 *
 * Submissions ~> https://codeforces.com/contest/793/submission/345381821 By huanhuanonly
 *
 * @b Dijkstra based on @b Layered-graph
 *
 * ----October 24, 2025 [00h:21m:11s]----
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

#ifdef __huanhuanonly_localhost
    ::freopen("in", "r", stdin);
    ::freopen("out", "w", stdout);
#endif

    int n, m;
    std::cin >> n >> m;

    int sx, sy;
    int tx, ty;

    std::vector mp(n, std::vector<char>(m));

    for (int i = 0; i < n; ++i)
    {
        for (int j = 0; j < m; ++j)
        {
            std::cin >> mp[i][j];

            if (mp[i][j] == 'S')
            {
                sx = i, sy = j;
            }
            else if (mp[i][j] == 'T')
            {
                tx = i, ty = j;
            }
        }
    }

    std::vector dis(4, std::vector(n, std::vector(m, 3)));
    std::vector vis(4, std::vector(n, std::vector(m, false)));

    const std::pair<int, int> d[]{
        {0, 1}, {1, 0},
        {0, -1}, {-1, 0}
    };

    struct item
    {
        int x, y;
        int layer, dis;

        bool operator<(const item& other) const noexcept
        {
            return dis > other.dis;
        }
    };

    std::priority_queue<item> que;

    for (int i = 0; i < 4; ++i)
    {
        que.push({sx, sy, i, 0});
        dis[i][sx][sy] = 0;
    }

    while (not que.empty())
    {
        auto cur = que.top();
        que.pop();

        if (vis[cur.layer][cur.x][cur.y])
        {
            continue;
        }

        vis[cur.layer][cur.x][cur.y] = true;

        for (int i = 0; i < 4; ++i)
        {
            const int nx = cur.x + d[i].first, ny = cur.y + d[i].second;

            if (not (nx >= 0 and nx < n and ny >= 0 and ny < m))
            {
                continue;
            }

            if (mp[nx][ny] == '*')
            {
                continue;
            }

            if (const int ndis = dis[cur.layer][cur.x][cur.y] + (cur.layer != i); ndis < dis[i][nx][ny])
            {
                dis[i][nx][ny] = ndis;
                que.push({nx, ny, i, ndis});
            }
        }
    }

    bool yes = false;

    for (int i = 0; i < 4; ++i)
    {
        yes = yes or dis[i][tx][ty] <= 2;
    }

    if (yes)
    {
        std::cout << "YES";
    }
    else
    {
        std::cout << "NO";
    }

    return 0;
}
/**
 * 2026牛客寒假算法基础集训营6
 * 
 * => D-小L的扩展 ( @c 1700 )
 * 
 * -> https://ac.nowcoder.com/acm/contest/120566/D
 * 
 * Submissions ~> https://ac.nowcoder.com/acm/contest/view-submission?submissionId=82423095 By huanhuanonly
 * 
 * @b Dijkstra ( @a multiple-source )
 * 
 * ----February 13, 2026 [17h:24m:36s]----
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

    int n, m, a, b;
    std::cin >> n >> m >> a >> b;

    constexpr uint64 inf = std::numeric_limits<uint64>::max() / 2;

    std::vector dis(n, std::vector(m, inf));
    std::vector vis(n, std::vector(m, false));

    std::vector map(n, std::vector(m, uint64{}));

    struct item
    {
        int x, y;
        uint64 dis;

        bool operator<(const item& other) const
        {
            return dis > other.dis;
        }
    };

    std::priority_queue<item> que;

    for (int i = 0; i < a; ++i)
    {
        int x, y;
        std::cin >> x >> y;

        --x, --y;

        que.emplace(x, y, 0);
        dis[x][y] = 0;
    }

    for (int i = 0; i < b; ++i)
    {
        int x, y, t;
        std::cin >> x >> y >> t;

        --x, --y;

        map[x][y] = t;
    }

    constexpr std::pair<int, int> d[]{
        {1, 0}, {0, 1}, {-1, 0}, {0, -1}
    };

    while (not que.empty())
    {
        auto cur = que.top();
        que.pop();

        if (vis[cur.x][cur.y])
        {
            continue;
        }

        vis[cur.x][cur.y] = true;

        for (const auto& [dx, dy] : d)
        {
            const int nx = cur.x + dx, ny = cur.y + dy;

            if (nx >= 0 and nx < n and ny >= 0 and ny < m)
            {
                const int ndis = std::max(dis[cur.x][cur.y] + 1, map[nx][ny]);

                if (ndis < dis[nx][ny])
                {
                    dis[nx][ny] = ndis;
                    que.emplace(nx, ny, ndis);
                }
            }
        }
    }

    uint64 max = 0;

    for (int i = 0; i < n; ++i)
    {
        for (int j = 0; j < m; ++j)
        {
            max = std::max(max, dis[i][j]);
        }
    }

    std::cout << max;

    return 0;
}
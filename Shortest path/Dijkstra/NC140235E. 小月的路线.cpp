/**
 * 牛客周赛 Round 161
 *
 * => E-小月的路线 ( @c 1200 )
 *
 * -> https://ac.nowcoder.com/acm/contest/140235/E
 *
 * Submissions ~> https://ac.nowcoder.com/acm/contest/view-submission?submissionId=84711679 By huanhuanonly
 *
 * @b Dijkstra
 *
 * ----September 14, 2026 [10h:26m:16s]----
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

    int n, m;
    std::cin >> n >> m;

    struct edge
    {
        int to;
        int64 d, r;
    };

    std::vector<std::vector<edge>> e(n + 1);

    for (int i = 0; i < m; ++i)
    {
        int u, v, d, r;
        std::cin >> u >> v >> d >> r;

        e[u].emplace_back(v, d, r);
    }

    struct item
    {
        int u;
        int64 d, r;

        bool operator<(const item& rhs) const noexcept
        {
            return std::pair(d, r) > std::pair(rhs.d, rhs.r);
        }
    };

    constexpr int64 inf = std::numeric_limits<int64>::max() / 2;
    std::vector<std::pair<int64, int64>> dis(n + 1, {inf, inf});

    std::vector<bool> vis(n + 1);
    std::priority_queue<item> que;

    que.emplace(1, 0, 0);
    dis[1] = {0, 0};

    while (not que.empty())
    {
        const auto [u, d, r] = que.top();
        que.pop();

        if (vis[u])
        {
            continue;
        }

        vis[u] = true;

        for (const auto& i : e[u])
        {
            if (std::pair(d + i.d, r + i.r) < dis[i.to])
            {
                dis[i.to] = std::pair(d + i.d, r + i.r);
                que.emplace(i.to, d + i.d, r + i.r);
            }
        }
    }

    if (dis[n].first == inf)
    {
        std::cout << "-1 -1\n";
    }
    else
    {
        std::cout << dis[n].first << ' ' << dis[n].second << '\n';
    }

    return 0;
}
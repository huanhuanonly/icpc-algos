/**
 * 2026牛客寒假算法基础集训营2
 * 
 * => J-终于再见 ( @c 1900 )
 * 
 * -> https://ac.nowcoder.com/acm/contest/120562/J
 * 
 * Submissions ~> https://ac.nowcoder.com/acm/contest/view-submission?submissionId=82078727 By huanhuanonly
 * 
 * @b Breadth-first-search ( @a multiple-source )
 * 
 * ----February 05, 2026 [17h:57m:07s]----
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

    std::vector<std::vector<int>> e(n + 1);

    for (int i = 0; i < m; ++i)
    {
        int u, v;
        std::cin >> u >> v;

        e[u].push_back(v);
        e[v].push_back(u);
    }

    std::map<int, std::vector<int>, std::ranges::greater> sets;

    for (int i = 1; i <= n; ++i)
    {
        sets[e[i].size()].push_back(i);
    }

    constexpr auto inf = std::numeric_limits<int>::max() / 2;

    std::vector<int> dis(n + 1, inf);

    auto bfs = [&](int sid) -> void
    {
        std::queue<std::pair<int, int>> que;

        for (const auto& i : sets[sid])
        {
            que.emplace(i, 0);
        }

        while (not que.empty())
        {
            auto cur = que.front();
            que.pop();

            for (const auto& i : e[cur.first])
            {
                if (e[i].size() < sid and cur.second + 1 < dis[i])
                {
                    dis[i] = cur.second + 1;
                    que.emplace(i, dis[i]);
                }
            }
        }
    };

    for (const auto& [k, set] : sets)
    {
        bfs(k);
    }

    for (int i = 1; i <= n; ++i)
    {
        if (dis[i] != inf)
        {
            std::cout << dis[i] << ' ';
        }
        else
        {
            std::cout << -1 << ' ';
        }
    }

    return 0;
}
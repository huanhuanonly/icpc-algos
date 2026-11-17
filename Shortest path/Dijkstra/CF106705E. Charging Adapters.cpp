/**
 * The 2026 ICPC China Guizhou Provincial Contest
 *
 * => E. Charging Adapters
 *
 * -> https://codeforces.com/gym/106705/problem/E
 *
 * Submissions ~> https://codeforces.com/gym/106705/submission/390939888 By huanhuanonly
 *
 * @b Dijkstra
 *
 * ----September 16, 2026 [23h:48m:53s]----
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
        int n, k, s, t;
        std::cin >> n >> k >> s >> t;

        --s, --t;

        std::vector<int64> x(n);

        for (int i = 0; i < n; ++i)
        {
            std::cin >> x[i];
        }

        struct item
        {
            int u;
            int64 w;

            bool operator<(const item& rhs) const noexcept
            {
                return w > rhs.w;
            }
        };

        std::vector<std::vector<std::pair<int, int>>> pos(k + 1);

        std::vector<std::pair<int, int>> set;

        for (int i = 0; i < n; ++i)
        {
            int m;
            std::cin >> m;

            set.emplace_back(0, i);

            for (int j = 0; j < m; ++j)
            {
                int c, w;
                std::cin >> c >> w;

                pos[c].emplace_back(i, w);
                set.emplace_back(c, i);
            }
        }

        std::ranges::sort(set);
        set.erase(std::ranges::unique(set).begin(), set.end());

        auto $ = [&](int c, int u) -> int
        {
            return std::ranges::lower_bound(set, std::pair(c, u)) - set.begin();
        };

        std::vector<std::vector<item>> e(set.size());

        for (int c = 1; c <= k; ++c)
        {
            for (int i = 1; i < pos[c].size(); ++i)
            {
                e[$(c, pos[c][i - 1].first)].emplace_back($(c, pos[c][i].first), x[pos[c][i].first] - x[pos[c][i - 1].first]);
                e[$(c, pos[c][i].first)].emplace_back($(c, pos[c][i - 1].first), x[pos[c][i].first] - x[pos[c][i - 1].first]);
            }

            for (int i = 0; i < pos[c].size(); ++i)
            {
                e[$(c, pos[c][i].first)].emplace_back($(0, pos[c][i].first), 0);
                e[$(0, pos[c][i].first)].emplace_back($(c, pos[c][i].first), pos[c][i].second);
            }
        }

        constexpr int64 inf = std::numeric_limits<int64>::max() / 2;

        std::vector<int64> dis(set.size(), inf);
        std::vector<bool> vis(set.size());

        std::priority_queue<item> que;
        que.emplace($(0, s), 0);
        dis[$(0, s)] = 0;

        while (not que.empty())
        {
            const auto cur = que.top();
            que.pop();

            if (vis[cur.u])
            {
                continue;
            }

            vis[cur.u] = true;

            for (const auto& [u, w] : e[cur.u])
            {
                if (dis[cur.u] + w < dis[u])
                {
                    que.emplace(u, dis[u] = dis[cur.u] + w);
                }
            }
        }

        int64 ans = inf;

        for (int i = 0; i < set.size(); ++i)
        {
            if (set[i].second == t)
            {
                ans = std::min(ans, dis[i]);
            }
        }

        if (ans != inf)
        {
            std::cout << ans << '\n';
        }
        else
        {
            std::cout << "-1\n";
        }
    }

    return 0;
}
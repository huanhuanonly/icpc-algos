/**
 * Codeforces Round 1043 (Div. 3)
 *
 * => F. Rada and the Chamomile Valley ( @c 2100 )
 *
 * -> https://codeforces.com/contest/2132/problem/F
 *
 * Submissions ~> https://codeforces.com/contest/2132/submission/336664318 By huanhuanonly
 *
 * @b Tarjan's-algorithm ( @a bridge-finding )
 * @b Dijkstra
 *
 * ----September 03, 2025 [01h:23m:58s]----
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

    int _;
    std::cin >> _;

    while (_--)
    {
        int n, m;
        std::cin >> n >> m;

        std::vector<std::vector<std::pair<int, int>>> e(n + 1);

        for (int i = 1; i <= m; ++i)
        {
            int u, v;
            std::cin >> u >> v;

            e[u].push_back({v, i});
            e[v].push_back({u, i});
        }

        std::vector<std::pair<int, int>> dfn(n + 1);

        std::map<int, int> cut;

        auto dfs = [&, num = 0](auto& self, int u, int fa) mutable -> bool
        {
            dfn[u].first = dfn[u].second = ++num;

            bool can = false;

            for (const auto& [i, id] : e[u])
            {
                if (dfn[i].first == 0)
                {
                    bool ncan = self(self, i, u);
                    dfn[u].second = std::min(dfn[u].second, dfn[i].second);

                    if (dfn[i].second > dfn[u].first and ncan)
                    {
                        auto& t1 = cut[u];
                        t1 = (t1 == 0 ? id : std::min(t1, id));

                        auto& t2 = cut[i];
                        t2 = (t2 == 0 ? id : std::min(t2, id));
                    }

                    can = can or ncan;
                }
                else if (i != fa)
                {
                    dfn[u].second = std::min(dfn[u].second, dfn[i].first);
                }
            }

            return can or u == n;
        };

        dfs(dfs, 1, 0);

        constexpr int inf = std::numeric_limits<int>::max() / 2;
        std::vector<std::pair<int, int>> dis(n + 1, {inf, inf});

        auto bfs = [&]() -> void
        {
            struct item
            {
                int point, dis, id;

                bool operator<(const item& other) const noexcept
                {
                    if (dis != other.dis)
                    {
                        return dis > other.dis;
                    }
                    else
                    {
                        return id > other.id;
                    }
                }
            };

            std::priority_queue<item> que;
            std::vector<bool> vis(n + 1);

            for (auto it = cut.begin(); it != cut.end(); ++it)
            {
                que.push({it->first, 0, it->second});
                dis[it->first] = {0, it->second};
            }

            while (not que.empty())
            {
                auto cur = que.top();
                que.pop();

                if (vis[cur.point])
                {
                    continue;
                }

                vis[cur.point] = true;

                for (int i : e[cur.point] | std::views::keys)
                {
                    int ndis = dis[cur.point].first + 1;

                    if (ndis < dis[i].first or (ndis == dis[i].first and cur.id < dis[i].second))
                    {
                        dis[i] = {ndis, cur.id};
                        que.push({i, ndis, cur.id});
                    }
                }
            }
        };

        bfs();

        int q;
        std::cin >> q;

        while (q--)
        {
            int c;
            std::cin >> c;

            if (dis[c].second != inf)
            {
                std::cout << dis[c].second << ' ';
            }
            else
            {
                std::cout << -1 << ' ';
            }
        }

        std::cout.put('\n');
    }

    return 0;
}
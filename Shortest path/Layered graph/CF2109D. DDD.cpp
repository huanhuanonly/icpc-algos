/**
 * Codeforces Round 1025 (Div. 2)
 *
 * => D. D/D/D ( @c 1900 )
 *
 * -> https://codeforces.com/contest/2109/problem/D
 *
 * Submissions ~> https://codeforces.com/contest/2109/submission/326776413 By huanhuanonly
 *
 * @b Bfs based on @b Layered-graph
 * @b Classification-discussion
 *
 * ----July 01, 2025 [17h:48m:52s]----
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
        int n, m, ell;
        std::cin >> n >> m >> ell;

        int even_sum = 0, odd_cnt = 0, odd_min = std::numeric_limits<int>::max();

        for (int i = 0, v; i < ell; ++i)
        {
            std::cin >> v;

            if (v & 1)
            {
                even_sum += v - 1;
                ++odd_cnt;

                odd_min = std::min(odd_min, v);
            }
            else
            {
                even_sum += v;
            }
        }

        const int even = even_sum + odd_cnt - (odd_cnt & 1 ? odd_min : 0);
        const int odd  = (odd_cnt ? even_sum + odd_cnt - (odd_cnt & 1 ? 0 : odd_min) : 0);

        std::vector<std::vector<int>> e(n + 1);

        for (int i = 0; i < m; ++i)
        {
            int u, v;
            std::cin >> u >> v;

            e[u].push_back(v);
            e[v].push_back(u);
        }

        constexpr int inf = std::numeric_limits<int>::max();
        std::array<std::vector<int>, 2> dis{std::vector<int>(n + 1, inf), std::vector<int>(n + 1, inf)};

        auto bfs = [&]() -> void
        {
            struct item
            {
                int point, dis;
            };

            std::queue<item> que;
            que.push({1, 0});

            while (not que.empty())
            {
                item cur = que.front();
                que.pop();

                if (dis[cur.dis & 1][cur.point] != inf)
                {
                    continue;
                }

                dis[cur.dis & 1][cur.point] = cur.dis;

                for (int i : e[cur.point])
                {
                    que.push({i, cur.dis + 1});
                }
            }
        };

        bfs();

        for (int i = 1; i <= n; ++i)
        {
            bool accessible = false;

            accessible = accessible or (dis[0][i] != inf and even >= dis[0][i]);
            accessible = accessible or (dis[1][i] != inf and odd  >= dis[1][i]);

            std::cout << accessible;
        }

        std::cout.put('\n');
    }

    return 0;
}
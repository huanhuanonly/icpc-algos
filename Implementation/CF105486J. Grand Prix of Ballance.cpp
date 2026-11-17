/**
 * 2024 ICPC Asia Chengdu Regional Contest (The 3rd Universal Cup. Stage 15: Chengdu)
 *
 * => J. Grand Prix of Ballance
 *
 * -> https://codeforces.com/gym/105486/problem/J
 *
 * Submissions ~> https://codeforces.com/gym/105486/submission/389198567 By huanhuanonly
 *
 * @b Implementation
 *
 * ----September 02, 2026 [22h:42m:56s]----
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
        int64 n, m, q;
        std::cin >> n >> m >> q;

        std::vector<bool> vis(n + 1);

        std::vector<std::set<int64>> map(n + 1);
        std::vector<std::set<int64>> givedup(n + 1);

        std::vector<std::pair<int64, int64>> ans(m + 1);
        std::ranges::iota(ans | std::views::keys, 0);

        int clevel = 0;

        while (q--)
        {
            int op;
            std::cin >> op;

            if (op == 1)
            {
                int64 x;
                std::cin >> x;

                clevel = x;
                vis[x] = true;
            }
            else if (op == 2)
            {
                int64 id, x;
                std::cin >> id >> x;

                if (vis[x] and clevel == x)
                {
                    if (not map[x].contains(id) and not givedup[x].contains(id))
                    {
                        ans[id].second += m - map[x].size();
                        map[x].insert(id);
                    }
                }
            }
            else
            {
                int64 id, x;
                std::cin >> id >> x;

                if (vis[x] and clevel == x)
                {
                    if (not map[x].contains(id) and not givedup[x].contains(id))
                    {
                        givedup[x].insert(id);
                    }
                }
            }
        }

        std::ranges::sort(
            ans | std::views::drop(1),
            {},
            [](const auto& p)
            {
                return std::pair(-p.second, p.first);
            });

        for (int64 i = 1; i <= m; ++i)
        {
            std::cout << ans[i].first << ' ' << ans[i].second << '\n';
        }
    }

    return 0;
}
/**
 * Codeforces Round 151 (Div. 2)
 *
 * => D. Colorful Graph ( @c 1600 )
 *
 * -> https://codeforces.com/contest/246/problem/D
 *
 * Submissions ~> https://codeforces.com/contest/246/submission/387582968 By huanhuanonly
 *
 * @b Graphs
 *
 * ----August 18, 2026 [23h:43m:43s]----
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

    std::vector<int> color(n + 1);

    for (int i = 1; i <= n; ++i)
    {
        std::cin >> color[i];
    }

    std::vector<std::vector<int>> e(n + 1);

    for (int i = 0; i < m; ++i)
    {
        int u, v;
        std::cin >> u >> v;

        e[u].push_back(v);
        e[v].push_back(u);
    }

    std::vector<std::vector<int>> sets(1e5 + 1);

    for (int u = 1; u <= n; ++u)
    {
        for (const int& v : e[u])
        {
            if (color[u] != color[v])
            {
                sets[color[u]].push_back(color[v]);
            }
        }
    }

    std::pair<int, int> min{std::ranges::min(color | std::views::drop(1)), 0};

    for (int i = 1; i < sets.size(); ++i)
    {
        std::ranges::sort(sets[i]);

        if (const int cnt = std::ranges::unique(sets[i]).begin() - sets[i].begin(); cnt > min.second)
        {
            min = {i, cnt};
        }
    }

    std::cout << min.first << '\n';

    return 0;
}
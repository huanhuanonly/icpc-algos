/**
 * Dasha Code Championship - SPb Finals Round (only for onsite-finalists)
 *
 * => A. Anadi and Domino ( @c 1700 )
 *
 * -> https://codeforces.com/contest/1210/problem/A
 *
 * Submissions ~> https://codeforces.com/contest/1210/submission/388029372 By huanhuanonly
 *
 * @b Classification-discussion
 * @b Graphs
 *
 * ----August 23, 2026 [01h:07m:04s]----
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

    std::vector<std::bitset<8>> e(n + 1);

    for (int i = 0; i < m; ++i)
    {
        int u, v;
        std::cin >> u >> v;

        e[u].set(v);
        e[v].set(u);
    }

    if (n <= 6)
    {
        std::cout << m << '\n';
    }
    else
    {
        int max = 0;

        for (int u = 1; u <= n; ++u)
        {
            for (int v = 1; v <= n; ++v)
            {
                max = std::max(max, m - static_cast<int>((e[u] & e[v]).count()));
            }
        }

        std::cout << max << '\n';
    }

    return 0;
}
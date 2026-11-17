/**
 * Codeforces Round 216 (Div. 2)
 *
 * => C. Valera and Elections ( @c 1600 )
 *
 * -> https://codeforces.com/contest/369/problem/C
 *
 * Submissions ~> https://codeforces.com/contest/369/submission/387589865 By huanhuanonly
 *
 * @b Dfs on @a Trees
 *
 * ----August 19, 2026 [00h:39m:38s]----
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

    int n;
    std::cin >> n;

    std::vector<std::vector<std::pair<int, int>>> e(n + 1);

    for (int i = 0; i < n - 1; ++i)
    {
        int u, v, b;
        std::cin >> u >> v >> b;

        --b;

        e[u].emplace_back(v, b);
        e[v].emplace_back(u, b);
    }

    std::vector<int> que;
    que.reserve(n);

    auto dfs = [&](const auto& self, int u, int fa) -> bool
    {
        int res = 0;

        for (const auto& [v, b] : e[u])
        {
            if (v != fa)
            {
                if (self(self, v, u))
                {
                    res = true;
                }
                else if (b)
                {
                    res = true;
                    que.push_back(v);
                }
            }
        }

        return res;
    };

    dfs(dfs, 1, 0);

    std::cout << que.size() << '\n';

    for (const int& u : que)
    {
        std::cout << u << ' ';
    }

    return 0;
}
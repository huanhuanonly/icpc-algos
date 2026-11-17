/**
 * AtCoder Beginner Contest 479
 *
 * => E - Cut and Add ( @c 450 )
 *
 * -> https://atcoder.jp/contests/abc479/tasks/abc479_e
 *
 * Submissions ~> https://atcoder.jp/contests/abc479/submissions/80022085 By huanhuanonly
 *
 * @b Tree-difference-array
 * @b Dfs on @a Trees
 *
 * ----October 13, 2026 [23h:54m:28s]----
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

    for (int i = 1; i <= n - 1; ++i)
    {
        int u, v;
        std::cin >> u >> v;

        e[u].emplace_back(v, i);
        e[v].emplace_back(u, i);
    }

    std::vector<int> size(n + 1);
    std::vector<int64> x(n + 1);

    auto dfs = [&](const auto& self, int u, int fa) -> void
    {
        size[u] = 1;

        for (const auto& [v, eid] : e[u])
        {
            if (v != fa)
            {
                self(self, v, u);
                size[u] += size[v];

                if (size[v] > n - size[v])
                {
                    x[v] += eid;
                }
                else
                {
                    x[1] += eid;
                    x[v] -= eid;
                }
            }
        }
    };

    auto calc = [&](const auto& self, int u, int fa) -> void
    {
        for (const auto& [v, eid] : e[u])
        {
            if (v != fa)
            {
                x[v] += x[u];
                self(self, v, u);
            }
        }
    };

    dfs(dfs, 1, 0);
    calc(calc, 1, 0);

    for (int i = 1; i <= n; ++i)
    {
        std::cout << x[i] << ' ';
    }

    return 0;
}
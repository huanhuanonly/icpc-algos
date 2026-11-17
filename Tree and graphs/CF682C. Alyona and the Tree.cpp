/**
 * Codeforces Round 358 (Div. 2)
 *
 * => C. Alyona and the Tree ( @c 1600 )
 *
 * -> https://codeforces.com/contest/682/problem/C
 *
 * Submissions ~> https://codeforces.com/contest/682/submission/387594142 By huanhuanonly
 *
 * @b Dfs on @a Trees
 *
 * ----August 19, 2026 [01h:13m:48s]----
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

    std::vector<int64> w(n + 1);

    for (int i = 1; i <= n; ++i)
    {
        std::cin >> w[i];
    }

    std::vector<std::vector<std::pair<int, int>>> e(n + 1);

    for (int u = 2; u <= n; ++u)
    {
        int v, c;
        std::cin >> v >> c;

        e[u].emplace_back(v, c);
        e[v].emplace_back(u, c);
    }

    std::vector<int> cnt(n + 1, 1);

    auto build = [&](const auto& self, int u, int fa) -> void
    {
        for (const auto& [v, c] : e[u])
        {
            if (v != fa)
            {
                self(self, v, u);
                cnt[u] += cnt[v];
            }
        }
    };

    build(build, 1, 0);

    auto dfs = [&](const auto& self, int u, int fa, int64 sum) -> int
    {
        if (sum > w[u])
        {
            return cnt[u];
        }

        int res = 0;

        for (const auto& [v, c] : e[u])
        {
            if (v != fa)
            {
                res += self(self, v, u, std::max(sum + c, int64{}));
            }
        }

        return res;
    };

    std::cout << dfs(dfs, 1, 0, 0) << '\n';

    return 0;
}
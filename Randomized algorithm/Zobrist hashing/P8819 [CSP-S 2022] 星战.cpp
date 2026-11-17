/**
 * CSP-S 2022 自测
 *
 * => P8819 [CSP-S 2022] 星战 ( @c 省选/NOI- )
 *
 * -> https://www.luogu.com.cn/problem/P8819
 *
 * Submissions ~> https://www.luogu.com.cn/record/279540987 By huanhuanonly
 *
 * @b Graphs
 * @b Pseudo-tree
 * @b Zobrist-hashing
 *
 * ----May 27, 2026 [14h:31m:03s]----
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

    std::mt19937 rng(std::chrono::system_clock::now().time_since_epoch().count());
    const auto $ = std::views::repeat(0, n + 1) | std::views::transform([&](int) { return rng(); }) | std::ranges::to<std::vector>();

    std::vector<uint64> sum(n + 1);

    for (int i = 0; i < m; ++i)
    {
        int u, v;
        std::cin >> u >> v;

        sum[v] += $[u];
    }

    auto total = *std::ranges::fold_left_first(sum, std::plus{});

    const auto backup_sum = sum;
    const auto target = *std::ranges::fold_left_first($ | std::views::drop(1), std::plus{});

    int q;
    std::cin >> q;

    while (q--)
    {
        int opt;
        std::cin >> opt;

        if (opt == 1)
        {
            int u, v;
            std::cin >> u >> v;

            total -= $[u];
            sum[v] -= $[u];
        }
        else if (opt == 2)
        {
            int u;
            std::cin >> u;

            total -= sum[u];
            sum[u] = 0;
        }
        else if (opt == 3)
        {
            int u, v;
            std::cin >> u >> v;

            total += $[u];
            sum[v] += $[u];
        }
        else
        {
            int u;
            std::cin >> u;

            total += backup_sum[u] - sum[u];
            sum[u] = backup_sum[u];
        }

        if (total == target)
        {
            std::cout << "YES\n";
        }
        else
        {
            std::cout << "NO\n";
        }
    }

    return 0;
}
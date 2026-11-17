/**
 * NEC Programming Contest 2022 (AtCoder Beginner Contest 267)
 *
 * => F - Exactly K Steps ( @c 500 )
 *
 * -> https://atcoder.jp/contests/abc267/tasks/abc267_f
 *
 * Submissions ~> https://atcoder.jp/contests/abc267/submissions/77464451 By huanhuanonly
 *
 * @b Tree-diameter
 * @b Binary-lifting
 *
 * ----July 13, 2026 [19h:04m:14s]----
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

    std::vector<std::vector<int>> e(n + 1);

    for (int i = 0; i < n - 1; ++i)
    {
        int u, v;
        std::cin >> u >> v;

        e[u].push_back(v);
        e[v].push_back(u);
    }

    auto farthest = [&](const auto& self, int u, int fa, int d) -> std::pair<int, int>
    {
        std::pair max{d, u};

        for (const int& v : e[u])
        {
            if (v != fa)
            {
                max = std::max(max, self(self, v, u, d + 1));
            }
        }

        return max;
    };

    const int root1 = farthest(farthest, 1, 0, 0).second;
    const int root2 = farthest(farthest, root1, 0, 0).second;

    constexpr int laycnt = 20;

    std::vector<std::array<int, laycnt>> parent1(n + 1), parent2(n + 1);

    auto build = [&](const auto& self, auto& parent, int u) -> void
    {
        for (int i = 1; i < laycnt; ++i)
        {
            parent[u][i] = parent[parent[u][i - 1]][i - 1];
        }

        for (const int& v : e[u])
        {
            if (v != parent[u][0])
            {
                parent[v][0] = u;

                self(self, parent, v);
            }
        }
    };

    build(build, parent1, root1);
    build(build, parent2, root2);

    auto climb = [&](const auto& parent, int u, int k) -> int
    {
        for (int i = 0; i < laycnt; ++i)
        {
            if (k & 1 << i)
            {
                u = parent[u][i];
            }
        }

        return u;
    };

    int q;
    std::cin >> q;

    while (q--)
    {
        int u, k;
        std::cin >> u >> k;

        if (int v = climb(parent1, u, k))
        {
            std::cout << v << '\n';
        }
        else if (v = climb(parent2, u, k))
        {
            std::cout << v << '\n';
        }
        else
        {
            std::cout << "-1\n";
        }
    }

    return 0;
}
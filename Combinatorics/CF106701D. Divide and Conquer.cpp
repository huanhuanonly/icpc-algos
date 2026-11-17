/**
 * The 2026 ICPC Asia EC Regionals Online Contest (II)
 *
 * => D. Divide and Conquer
 *
 * -> https://codeforces.com/gym/106701/problem/D
 *
 * Submissions ~> https://codeforces.com/gym/106701/submission/390739813 By huanhuanonly
 *
 * @b Combinatorics
 * @b Greedy
 *
 * ----September 14, 2026 [23h:43m:10s]----
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

    int n, q;
    std::cin >> n >> q;

    constexpr uint64 mod = 998244353;
    uint64 ans = 1;

    std::vector<int> maxlim(1 << n + 1);
    maxlim[1] = 1 << n;

    for (int i = 0; i < q; ++i)
    {
        int u, x;
        std::cin >> u >> x;

        if (maxlim[u] and maxlim[u] != x)
        {
            ans = 0;
        }

        maxlim[u] = x;
    }

    std::vector<int> depth(1 << n + 1);

    for (int u = 2; u < depth.size(); ++u)
    {
        depth[u] = depth[u >> 1] + 1;
    }

    auto ancestor = [&](int u, int v) -> int
    {
        if (depth[u] < depth[v])
        {
            return (v >> depth[v] - depth[u]) == u ? u : 0;
        }
        else
        {
            return (u >> depth[u] - depth[v]) == v ? v : 0;
        }
    };

    auto climb = [&](int u) -> int
    {
        for (u >>= 1; not maxlim[u]; u >>= 1);
        return u;
    };

    auto leaf_count = [&](int u) -> int
    {
        return 1 << n - depth[u];
    };

    std::vector<int> cap(1 << n + 1);
    std::vector<int> deepest((1 << n) + 1);

    std::vector<std::vector<int>> sets((1 << n) + 1);

    for (int u = 1; u < maxlim.size(); ++u)
    {
        if (not maxlim[u])
        {
            continue;
        }

        cap[u] = leaf_count(u);
        sets[maxlim[u]].push_back(u);

        if (u == 1)
        {
            continue;
        }

        const int fa = climb(u);

        if (maxlim[fa] < maxlim[u])
        {
            ans = 0;
            break;
        }

        cap[fa] -= leaf_count(u);

        if (deepest[maxlim[u]])
        {
            if (const auto a = ancestor(u, deepest[maxlim[u]]); a)
            {
                if (a != u)
                {
                    deepest[maxlim[u]] = u;
                }
            }
            else
            {
                ans = 0;
                break;
            }
        }
        else
        {
            deepest[maxlim[u]] = u;
        }
    }

    for (int x = 1 << n, pool = 0; x >= 1; --x)
    {
        for (const auto& u : sets[x])
        {
            pool += cap[u];
        }

        if (const int u = deepest[x])
        {
            if (cap[u] <= 0)
            {
                ans = 0;
                break;
            }

            (ans *= cap[u]) %= mod;

            --cap[u];
            --pool;
        }
        else
        {
            if (pool <= 0)
            {
                ans = 0;
                break;
            }

            (ans *= pool) %= mod;
            --pool;
        }
    }

    std::cout << ans << '\n';

    return 0;
}
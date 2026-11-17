/**
 * Keysight Technologies Programming Contest（AtCoder Beginner Contest 454）
 *
 * => G - Mode in the Subtree ( @c 625 )
 *
 * -> https://atcoder.jp/contests/abc454/tasks/abc454_g
 *
 * Submissions ~> https://atcoder.jp/contests/abc454/submissions/75782366 By huanhuanonly
 *
 * @b Dsu-on-tree
 *
 * ----May 14, 2026 [15h:53m:26s]----
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

    uint64 n, seed, m, f;
    std::cin >> n >> seed >> m >> f;

    std::vector<uint64> q(m + 1), d(m + 1);

    for (uint64 i = 2; i <= m; ++i)
    {
        std::cin >> q[i];
    }

    for (uint64 i = 1; i <= m; ++i)
    {
        std::cin >> d[i];
    }

    std::vector<uint64> parent(n + 1), color(n + 1);

    for (uint64 i = 2; i <= n; ++i)
    {
        if (i <= m)
        {
            parent[i] = q[i];
        }
        else
        {
            parent[i] = seed % (i - 1) + 1;
            seed = (seed * 1103515245 + 12345) % (1ULL << 31);
        }
    }

    for (uint64 i = 1; i <= n; ++i)
    {
        if (i <= m)
        {
            color[i] = d[i];
        }
        else
        {
            color[i] = seed % f + 1;
            seed = (seed * 1103515245 + 12345) % (1ULL << 31);
        }
    }

    std::vector<std::vector<int>> e(n + 1);

    for (uint64 i = 2; i <= n; ++i)
    {
        e[parent[i]].push_back(static_cast<int>(i));
    }

    struct node
    {
        int size;
        int wson;
    };

    std::vector<node> tree(n + 1);

    auto build = [&](const auto& self, int u) -> void
    {
        tree[u].size = 1;

        for (const auto& v : e[u])
        {
            self(self, v);
            tree[u].size += tree[v].size;

            if (tree[v].size > tree[tree[u].wson].size)
            {
                tree[u].wson = v;
            }
        }
    };

    build(build, 1);

    std::vector<int> record(n + 1);
    int max = 0, cnt = 0;

    constexpr uint64 mod = 998244353;
    uint64 ans = 0;

    auto add = [&](const auto& self, int u, int except) -> void
    {
        ++record[color[u]];

        if (record[color[u]] > max)
        {
            max = record[color[u]];
            cnt = 1;
        }
        else if (record[color[u]] == max)
        {
            ++cnt;
        }

        for (const auto& v : e[u])
        {
            if (v != except)
            {
                self(self, v, except);
            }
        }
    };

    auto remove = [&](const auto& self, int u) -> void
    {
        --record[color[u]];

        for (const auto& v : e[u])
        {
            self(self, v);
        }
    };

    auto calc = [&](int i) -> void
    {
        ans += uint64(max ^ i) * (cnt ^ i);
        ans %= mod;
    };

    auto dfs = [&](const auto& self, int u, bool clear = false) -> void
    {
        if (tree[u].wson)
        {
            for (const auto& v : e[u])
            {
                if (v != tree[u].wson)
                {
                    self(self, v, true);
                }
            }

            self(self, tree[u].wson, false);
        }

        add(add, u, tree[u].wson);
        calc(u);

        if (clear)
        {
            remove(remove, u);
            max = 0, cnt = 0;
        }
    };

    dfs(dfs, 1);

    std::cout << ans << '\n';

    return 0;
}
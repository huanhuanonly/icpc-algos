/**
 * 牛客周赛 Round 156
 *
 * => E-小红的树染色 ( @c 1500 )
 *
 * -> https://ac.nowcoder.com/acm/contest/138917/E
 *
 * Submissions ~> https://ac.nowcoder.com/acm/contest/view-submission?submissionId=84422407 By huanhuanonly
 *
 * @b Dfs on @a Trees
 * @b LCA ( @a binary-lifting )
 * @b Tree-diameter
 *
 * ----August 09, 2026 [19h:57m:17s]----
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

    std::string s;
    std::cin >> s;
    s.insert(s.begin(), ' ');

    std::vector<std::vector<int>> e(n + 1);

    for (int i = 0; i < n - 1; ++i)
    {
        int u, v;
        std::cin >> u >> v;

        e[u].push_back(v);
        e[v].push_back(u);
    }

    constexpr int bitcnt = 20;

    std::vector<std::array<int, bitcnt>> parent(n + 1);
    std::vector<int> depth(n + 1);

    auto find = [&](const auto& self, int u) -> int
    {
        int max = s[u] == '1' ? u : 0;

        for (const auto& v : e[u])
        {
            if (v != parent[u][0])
            {
                parent[v][0] = u;
                depth[v] = depth[u] + 1;

                if (const int res = self(self, v); depth[res] > depth[max])
                {
                    max = res;
                }
            }
        }

        return max;
    };

    auto lca = [&](int u, int v) -> int
    {
        if (depth[u] < depth[v])
        {
            std::swap(u, v);
        }

        for (int i = 0, diff = depth[u] - depth[v]; i < bitcnt; ++i)
        {
            if (diff & 1 << i)
            {
                u = parent[u][i];
            }
        }

        if (u == v)
        {
            return u;
        }

        for (int i = bitcnt; i--; )
        {
            if (parent[u][i] != parent[v][i])
            {
                u = parent[u][i];
                v = parent[v][i];
            }
        }

        return parent[u][0];
    };

    auto dist = [&](int u, int v) -> int
    {
        return depth[u] + depth[v] - depth[lca(u, v)] * 2;
    };

    const int p1 = find(find, s.find_first_of('1'));

    parent[p1][0] = 0;
    depth[p1] = 0;

    const int p2 = find(find, p1);

    for (int i = 1; i < bitcnt; ++i)
    {
        for (int u = 1; u <= n; ++u)
        {
            parent[u][i] = parent[parent[u][i - 1]][i - 1];
        }
    }

    const int maxdist = dist(p1, p2);

    for (int i = 1; i <= n; ++i)
    {
        std::cout << std::max({maxdist, dist(p1, i), dist(p2, i)}) << '\n';
    }

    return 0;
}
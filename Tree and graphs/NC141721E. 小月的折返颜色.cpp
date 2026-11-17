/**
 * 牛客周赛 Round 165
 *
 * => E-小月的折返颜色 ( @c 1600 )
 *
 * -> https://ac.nowcoder.com/acm/contest/141721/E
 *
 * Submissions ~> https://ac.nowcoder.com/acm/contest/view-submission?submissionId=84982013 By huanhuanonly
 *
 * @b Dfs on @a Trees
 * @b Combinatorics
 *
 * ----October 11, 2026 [20h:01m:28s]----
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

    std::vector<int> c(n + 1);

    for (int i = 1; i <= n; ++i)
    {
        std::cin >> c[i];
    }

    std::vector<std::vector<int>> e(n + 1);

    for (int i = 0; i < n - 1; ++i)
    {
        int u, v;
        std::cin >> u >> v;

        e[u].push_back(v);
        e[v].push_back(u);
    }

    std::vector<int> cid(n + 1);
    std::vector<int> col(n + 1);

    auto dfs = [&](const auto& self, int u, int id) -> void
    {
        cid[u] = id;

        for (const auto& v : e[u])
        {
            if (not cid[v] and c[u] == c[v])
            {
                self(self, v, id);
            }
        }
    };

    for (int i = 1, id = 0; i <= n; ++i)
    {
        if (not cid[i])
        {
            dfs(dfs, i, ++id);
            col[id] = c[i];
        }
    }

    std::vector<std::vector<int>> ne(n + 1);
    std::vector<int> cnt(n + 1);

    for (int u = 1; u <= n; ++u)
    {
        ++cnt[cid[u]];

        for (const auto& v : e[u])
        {
            if (cid[u] != cid[v])
            {
                ne[cid[u]].push_back(cid[v]);
            }
        }
    }

    uint64 ans = 0;
    std::map<int, std::vector<int>> map;

    for (int u = 1; u <= n; ++u)
    {
        for (const auto& v : ne[u])
        {
            map[col[v]].push_back(cnt[v]);
        }

        for (const auto& [color, count] : map)
        {
            uint64 sum = std::reduce(count.begin(), count.end());

            for (const auto& i : count)
            {
                ans += i * (sum -= i);
            }
        }

        map.clear();
    }

    std::cout << ans << '\n';

    return 0;
}
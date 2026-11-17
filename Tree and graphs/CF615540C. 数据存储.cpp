/**
 * 2025-2026 国际大学生程序设计竞赛贵州省赛
 *
 * => C. 数据存储
 *
 * -> https://codeforces.com/gym/615540/problem/C
 *
 * Submissions ~> https://codeforces.com/gym/615540/submission/385444430 By huanhuanonly
 *
 * @b Dfs on @a Trees
 *
 * ----August 04, 2026 [01h:19m:10s]----
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

    std::vector<std::array<int, 2>> e(n + 1);
    std::map<std::pair<int, int>, std::pair<int, int>> que{{{1, n}, {0, 0}}};

    for (int i = 0, v; i < n; ++i)
    {
        std::cin >> v;

        auto nd = que.extract(std::prev(que.upper_bound({v, n + 1})));

        e[nd.mapped().first][nd.mapped().second] = v;

        if (nd.key().first <= v - 1)
        {
            que.emplace(std::pair(nd.key().first, v - 1), std::pair(v, 0));
        }

        if (v + 1 <= nd.key().second)
        {
            que.emplace(std::pair(v + 1, nd.key().second), std::pair(v, 1));
        }
    }

    int ans = 0;

    auto dfs = [&](const auto& self, int u) -> int
    {
        std::vector<int> set{0, 0};

        for (const int& v : e[u])
        {
            if (v)
            {
                set.push_back(self(self, v) + 1);
            }
        }

        std::ranges::partial_sort(set, set.begin() + 2, std::ranges::greater{});

        ans = std::max(ans, set[0] + set[1]);
        return set.front();
    };

    dfs(dfs, e[0][0]);

    std::cout << ans << '\n';

    return 0;
}
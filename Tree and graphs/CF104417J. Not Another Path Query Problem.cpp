/**
 * The 13th Shandong ICPC Provincial Collegiate Programming Contest
 * 
 * => J. Not Another Path Query Problem
 * 
 * -> https://codeforces.com/gym/104417/problem/J
 * 
 * Submissions ~> https://codeforces.com/gym/104417/submission/361020984 By huanhuanonly
 * 
 * @b Bitwise-AND
 * @b Longest-common-prefix
 * @b Bfs on @a Graphs
 * @b Offline
 * 
 * ----February 02, 2026 [00h:05m:40s]----
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

    uint64 n, m, q, V;
    std::cin >> n >> m >> q >> V;

    std::vector<std::vector<std::pair<uint64, uint64>>> e(n + 1);

    for (uint64 i = 0; i < m; ++i)
    {
        uint64 u, v, w;
        std::cin >> u >> v >> w;

        if (w >= V)
        {
            e[u].emplace_back(v, w);
            e[v].emplace_back(u, w);
        }
    }

    auto bfs = [&](std::vector<uint64>& map, uint64 start, uint64 mark) -> void
    {
        std::queue<uint64> que;
        que.push(start);

        while (not que.empty())
        {
            const uint64 cur = que.front();
            que.pop();

            if (map[cur])
            {
                continue;
            }

            map[cur] = start;

            for (const auto& i : e[cur])
            {
                if ((i.second & mark) == mark)
                {
                    que.push(i.first);
                }
            }
        }
    };

    std::vector<std::pair<uint64, uint64>> queries(q);

    for (auto& [u, v] : queries)
    {
        std::cin >> u >> v;
    }

    std::vector<bool> ans(q);

    auto answer = [&](uint64 mark)
    {
        std::vector<uint64> map(n + 1);

        for (uint64 i = 1; i <= n; ++i)
        {
            if (not map[i])
            {
                bfs(map, i, mark);
            }
        }

        for (uint64 i = 0; i < q; ++i)
        {
            if (map[queries[i].first] == map[queries[i].second])
            {
                ans[i] = true;
            }
        }
    };

    if (V)
    {
        static auto lowbit = [](uint64 x) -> uint64
        {
            return x & -x;
        };

        for (uint64 mark = V; mark < (1ULL << 60); mark += lowbit(mark))
        {
            answer(mark);
        }
    }
    else
    {
        answer(0);
    }

    for (const bool yes : ans)
    {
        if (yes)
        {
            std::cout << "Yes\n";
        }
        else
        {
            std::cout << "No\n";
        }
    }

    return 0;
}
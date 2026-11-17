/**
 * The 2026 ICPC Asia East Continent Online Contest (I)
 *
 * => C. Permutation Inversions
 *
 * -> https://qoj.ac/contest/4071/problem/20018
 *
 * Submissions ~> https://qoj.ac/submission/2962401 By huanhuanonly
 *
 * @b Topological-sorting
 *
 * ----September 15, 2026 [11h:08m:05s]----
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

    int _;
    std::cin >> _;

    while (_--)
    {
        int n, m;
        std::cin >> n >> m;

        std::vector<std::vector<int>> e(n + 1);
        std::vector<int> out(n + 1);

        for (int i = 0; i < m; ++i)
        {
            int l, r;
            std::cin >> l >> r;

            int last;
            std::cin >> last;

            for (int j = 1, v; j < r - l + 1; ++j)
            {
                std::cin >> v;
                e[v].push_back(last);

                last = v;
            }
        }

        for (int i = 1; i <= n; ++i)
        {
            std::ranges::sort(e[i]);
            e[i].erase(std::ranges::unique(e[i]).begin(), e[i].end());

            for (int v : e[i])
            {
                ++out[v];
            }
        }

        std::vector<int> log;

        auto bfs = [&]() -> void
        {
            std::vector<bool> vis(n + 1);
            std::priority_queue<int> que;

            for (int u = 1; u <= n; ++u)
            {
                if (not out[u])
                {
                    que.push(u);
                }
            }

            while (not que.empty())
            {
                const int u = que.top();
                que.pop();

                if (vis[u])
                {
                    continue;
                }

                log.push_back(u);
                vis[u] = true;

                for (const auto& v : e[u])
                {
                    if (--out[v] == 0)
                    {
                        que.push(v);
                    }
                }
            }

            std::ranges::reverse(log);
        };

        bfs();

        if (log.size() < n)
        {
            std::cout << "-1\n";
            continue;
        }

        std::vector<int> p(n + 1);
        std::iota(p.begin(), p.end(), 0);

        for (int id = 0; const auto& i : log)
        {
            p[i] = ++id;
        }

        for (int i = 1; i <= n; ++i)
        {
            std::cout << p[i] << " \n"[i == n];
        }
    }

    return 0;
}
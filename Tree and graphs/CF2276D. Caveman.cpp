/**
 * Educational Codeforces Round 195 (Rated for Div. 2)
 *
 * => D. Caveman ( @c 1400 )
 *
 * -> https://codeforces.com/contest/2276/problem/D
 *
 * Submissions ~> https://codeforces.com/contest/2276/submission/394576809 By huanhuanonly
 *
 * @b Dfs on @a Graphs
 *
 * ----October 15, 2026 [00h:39m:03s]----
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

        for (int i = 0; i < m; ++i)
        {
            int u, v;
            std::cin >> u >> v;

            e[u].push_back(v);
            e[v].push_back(u);
        }

        std::vector<bool> vis(n + 1);

        std::vector<int> set;
        set.reserve(n);

        auto dfs = [&](const auto& self, int u, int fa) -> std::pair<int, int>
        {
            if (vis[u])
            {
                return {0, 0};
            }

            vis[u] = true;
            set.push_back(u);

            int size = 1, cnt = 0;

            for (const auto& v : e[u])
            {
                if (v != fa)
                {
                    const auto& [s, c] = self(self, v, u);
                    size += s;
                    cnt += c + 1;
                }
            }

            return {size, cnt};
        };

        int ans = 0;
        bool yes = true;

        for (int u = 1; u <= n; ++u)
        {
            if (not vis[u])
            {
                const auto [size, cnt] = dfs(dfs, u, 0);

                if (size == 1)
                {
                    yes = false;
                    break;
                }

                bool found = false;

                if (cnt == size - 1)
                {
                    for (const auto& v : set)
                    {
                        if (e[v].size() == size - 1)
                        {
                            found = true;
                            break;
                        }
                    }
                }

                if (found)
                {
                    ans += 2;
                }
                else
                {
                    ans += 3;
                }

                set.clear();
            }
        }

        if (yes)
        {
            if (ans == 2)
            {
                std::cout << "2\n";
            }
            else
            {
                std::cout << "Many\n";
            }
        }
        else
        {
            std::cout << "Brain Melt\n";
        }
    }

    return 0;
}
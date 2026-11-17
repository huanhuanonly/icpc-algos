/**
 * AtCoder Beginner Contest 472
 *
 * => E - Odd Cycle ( @c 450 )
 *
 * -> https://atcoder.jp/contests/abc472/tasks/abc472_e
 *
 * Submissions ~> https://atcoder.jp/contests/abc472/submissions/78622545 By huanhuanonly
 *
 * @b Dfs based on @b Layered-graph
 *
 * ----August 22, 2026 [20h:54m:19s]----
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

        std::vector vis(n + 1, std::array{false, false});

        std::vector<int> size(n + 1);
        std::vector<int> que;
        que.reserve(n);

        auto dfs = [&](const auto& self, int u) -> bool
        {
            if (vis[u][que.size() & 1])
            {
                return false;
            }

            vis[u][que.size() & 1] = true;

            que.push_back(0);

            for (const auto& v : e[u])
            {
                if (size[v])
                {
                    if ((size[v] ^ que.size()) & 1)
                    {
                        std::cout << que.size() - size[v] << '\n';

                        for (que.pop_back(); que.back() != v; que.pop_back())
                        {
                            std::cout << que.back() << ' ';
                        }

                        std::cout << v << '\n';

                        return true;
                    }
                }
                else
                {
                    que.back() = v;
                    size[v] = que.size();

                    if (self(self, v))
                    {
                        return true;
                    }

                    size[v] = 0;
                }
            }

            que.pop_back();
            return false;
        };

        if (not dfs(dfs, 1))
        {
            std::cout << "-1\n";
        }
    }

    return 0;
}
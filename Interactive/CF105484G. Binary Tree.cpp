/**
 * The 2024 ICPC Asia Nanjing Regional Contest (The 3rd Universal Cup. Stage 16: Nanjing)
 *
 * => G. Binary Tree
 *
 * -> https://codeforces.com/gym/105484/problem/G
 *
 * Submissions ~> https://codeforces.com/gym/105484/submission/389114484 By huanhuanonly
 *
 * @b Interactive
 * @b Centroid-decomposition
 * @b Classification-discussion
 *
 * ----September 01, 2026 [23h:52m:51s]----
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

    int _;
    std::cin >> _;

    while (_--)
    {
        int n;
        std::cin >> n;

        std::vector<std::vector<int>> e(n + 1);

        for (int i = 1; i <= n; ++i)
        {
            int u, v;
            std::cin >> u >> v;

            if (u)
            {
                e[i].push_back(u);
                e[u].push_back(i);
            }

            if (v)
            {
                e[i].push_back(v);
                e[v].push_back(i);
            }
        }

        auto query = [rem = std::countr_zero(std::bit_floor(uint32(n)))](int u, int v) mutable -> int
        {
            assert(rem--);
            std::cout << "? " << u << ' ' << v << std::endl;

            int t;
            std::cin >> t;

            return t - 1;
        };

        static auto answer = [](int s) -> void
        {
            std::cout << "! " << s << std::endl;
        };

        std::vector<int> size(n + 1);
        std::vector<bool> removed(n + 1);

        auto find_centroid = [&](int u) -> int
        {
            std::vector<int> set;

            auto build = [&](const auto& self, int u, int fa) -> void
            {
                size[u] = 1;
                set.push_back(u);

                for (const auto& v : e[u])
                {
                    if (v != fa and not removed[v])
                    {
                        self(self, v, u);
                        size[u] += size[v];
                    }
                }
            };

            build(build, u, 0);

            for (const auto& v : set)
            {
                int mx = size[u] - size[v];

                for (const auto& i : e[v])
                {
                    if (not removed[i] and size[i] < size[v])
                    {
                        mx = std::max(mx, size[i]);
                    }
                }

                if (mx <= size[u] / 2)
                {
                    return v;
                }
            }

            std::unreachable();
        };

        auto dfs = [&](const auto& self, int u) -> int
        {
            std::erase_if(e[u], [&](int v) -> bool { return removed[v]; });

            if (e[u].empty())
            {
                return u;
            }
            else if (e[u].size() == 1)
            {
                if (query(u, e[u].front()) < 0)
                {
                    return u;
                }
                else
                {
                    removed[u] = true;
                    return self(self, find_centroid(e[u].front()));
                }
            }

            std::ranges::sort(e[u], std::ranges::greater{}, [&](int u) -> int { return size[u]; });

            const auto c = query(e[u][0], e[u][1]);

            if (c < 0)
            {
                removed[u] = true;
                return self(self, find_centroid(e[u][0]));
            }
            else if (c > 0)
            {
                removed[u] = true;
                return self(self, find_centroid(e[u][1]));
            }
            else
            {
                removed[e[u][0]] = removed[e[u][1]] = true;
                return self(self, find_centroid(u));
            }
        };

        answer(dfs(dfs, find_centroid(1)));
    }

    return 0;
}
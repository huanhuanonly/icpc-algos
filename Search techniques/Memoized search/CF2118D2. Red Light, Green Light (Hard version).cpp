/**
 * Codeforces Round 1030 (Div. 2)
 * 
 * => D2. Red Light, Green Light (Hard version) ( @c 2200 )
 * 
 * -> https://codeforces.com/contest/2118/problem/D2
 * 
 * Submissions ~> https://codeforces.com/contest/2118/submission/324634155 By huanhuanonly
 * 
 * @b Memoized-search
 * 
 * ----June 16, 2025 [19h:14m:47s]----
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

#ifdef __GNUC__
using int128 = __int128;
using uint128 = unsigned __int128;
#endif

using real32 = float;
using real64 = double;
using real128 = long double;

int main(void)
{
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr), std::cout.tie(nullptr);

#ifdef __localhost
    ::freopen("in", "r", stdin);
    ::freopen("out", "w", stdout);
#endif

    int _;
    std::cin >> _;

    while (_--)
    {
        int64 n, k;
        std::cin >> n >> k;

        std::vector<int64> p(n + 1), d(n + 1);

        for (int i = 1; i <= n; ++i)
        {
            std::cin >> p[i];
        }

        for (int i = 1; i <= n; ++i)
        {
            std::cin >> d[i];
        }

        std::map<int64, std::vector<int>> next, prev;

        for (int i = 1; i <= n; ++i)
        {
            next[(p[i] % k + k - d[i]) % k].push_back(i);
            prev[(p[i] % k + d[i]) % k].push_back(i);
        }

        std::map<std::pair<int, bool>, int> vis;

        enum: int { placeholder = std::numeric_limits<int>::max() };

        auto dfs = [&](const auto& self, int i, bool direction) -> bool
        {
            direction = not direction;

            if (auto it = vis.find({i, direction}); it != vis.end())
            {
                return it->second != placeholder ? it->second : it->second = false;
            }
            else
            {
                vis[{i, direction}] = placeholder;
            }

            // forward
            if (direction)
            {
                const auto& v = next[(p[i] % k + k - d[i]) % k];

                if (auto it = std::ranges::upper_bound(v, i); it == v.end())
                {
                    return vis[{i, direction}] = true;
                }
                else
                {
                    return vis[{i, direction}] = self(self, *it, direction);
                }
            }
            // backward
            else
            {
                const auto& v = prev[(p[i] % k + d[i]) % k];

                if (auto it = std::upper_bound(v.rbegin(), v.rend(), i, std::greater()); it == v.rend())
                {
                    return vis[{i, direction}] = true;
                }
                else
                {
                    return vis[{i, direction}] = self(self, *it, direction);
                }
            }
        };

        int q;
        std::cin >> q;

        for (int i = 0; i < q; ++i)
        {
            int64 cpos;
            std::cin >> cpos;

            bool yes = true;

            if (auto it = next.find(cpos % k); it != next.end())
            {
                auto fit = std::ranges::lower_bound(it->second, cpos, [&](int64 lv, int64 rv) -> bool {
                    return p[lv] < rv;
                });

                if (fit != it->second.end())
                {
                    yes = dfs(dfs, *fit, true);
                }
            }

            if (yes)
                std::cout << "YES\n";
            else
                std::cout << "NO\n";
        }
    }

    return 0;
}
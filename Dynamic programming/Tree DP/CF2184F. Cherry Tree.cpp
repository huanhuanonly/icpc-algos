/**
 * Codeforces Round 1072 (Div. 3)
 * 
 * => F. Cherry Tree ( @c 1900 )
 * 
 * -> https://codeforces.com/contest/2184/problem/F
 * 
 * Submissions ~> https://codeforces.com/contest/2184/submission/359324604 By huanhuanonly
 * 
 * @b Tree-DP
 * 
 * ----January 23, 2026 [17h:35m:49s]----
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

#ifdef __huanhuanonly_localhost
    ::freopen("in", "r", stdin);
    ::freopen("out", "w", stdout);
#endif

    int _;
    std::cin >> _;

    while (_--)
    {
        int n;
        std::cin >> n;

        std::vector<std::vector<int>> e(n + 1);

        for (int i = 0; i < n - 1; ++i)
        {
            int u, v;
            std::cin >> u >> v;

            e[u].push_back(v);
            e[v].push_back(u);
        }

        using result_type = std::array<bool, 3>;

        auto dfs = [&](const auto& self, int u, int fa) -> result_type
        {
            result_type result{{0, 1, 0}};

            int cnt = 0;
            int add1 = 0, add2 = 0;

            for (const int& i : e[u] | std::views::filter([fa](int i) -> bool { return i != fa; }))
            {
                auto res = self(self, i, u);

                ++cnt;

                add1 += res[2];
                add2 += res[0];
            }

            if (cnt)
            {
                add1 = std::min(add1, 3);
                add2 = std::min(add2, 2);
    
                for (int a1 = 0; a1 <= add1; ++a1)
                {
                    for (int a2 = 0; a2 <= add2; ++a2)
                    {
                        result[(cnt + a1 + a2 * 2) % 3] = true;
                    }
                }
            }

            return result;
        };

        if (dfs(dfs, 1, 0)[0])
        {
            std::cout << "YES\n";
        }
        else
        {
            std::cout << "NO\n";
        }
    }

    return 0;
}
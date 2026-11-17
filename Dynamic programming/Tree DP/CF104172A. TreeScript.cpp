/**
 * The 2023 ICPC Asia Hong Kong Regional Programming Contest (The 1st Universal Cup, Stage 2:Hong Kong)
 *
 * => A. TreeScript
 *
 * -> https://codeforces.com/gym/104172/problem/A
 *
 * Submissions ~> https://codeforces.com/gym/104172/submission/389466752 By huanhuanonly
 *
 * @b Tree-DP
 *
 * ----September 05, 2026 [22h:09m:38s]----
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
        int n;
        std::cin >> n;

        std::vector<std::vector<int>> e(n + 1);

        for (int i = 1, fa; i <= n; ++i)
        {
            std::cin >> fa;
            e[fa].push_back(i);
        }

        auto dfs = [&](const auto& self, int u) -> int
        {
            if (e[u].empty())
            {
                return 1;
            }

            std::vector<int> que;

            for (const auto& v : e[u])
            {
                que.push_back(1 + self(self, v));
            }

            --*std::ranges::max_element(que);
            return std::ranges::max(que);
        };

        std::cout << dfs(dfs, 1) << '\n';
    }

    return 0;
}
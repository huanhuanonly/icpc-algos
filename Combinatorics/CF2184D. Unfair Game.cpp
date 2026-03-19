/**
 * Codeforces Round 1072 (Div. 3)
 * 
 * => D. Unfair Game ( @c 1600 )
 * 
 * -> https://codeforces.com/contest/2184/problem/D
 * 
 * Submissions ~> https://codeforces.com/contest/2184/submission/357577679 By huanhuanonly
 * 
 * @b Combinatorics
 * 
 * ----January 13, 2026 [00h:11m:28s]----
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

    std::vector C(32, std::vector(32, uint64{}));

    for (uint64 i = 0; i < 32; ++i)
    {
        C[i][0] = C[i][i] = 1;

        for (uint64 j = 1; j < i; ++j)
        {
            C[i][j] = C[i - 1][j] + C[i - 1][j - 1];
        }
    }

    int _;
    std::cin >> _;

    while (_--)
    {
        uint64 n, k;
        std::cin >> n >> k;

        uint64 ans = 0;

        for (uint64 i = 0; (1U << i) <= n; ++i)
        {
            if (i + 1 > k)
            {
                ++ans;
            }

            if ((1U << i) < n)
            {
                for (uint64 j = 1; j <= i; ++j)
                {
                    if (i + 1 + j > k)
                    {
                        ans += C[i][j];
                    }
                }
            }
        }

        std::cout << ans << '\n';
    }

    return 0;
}
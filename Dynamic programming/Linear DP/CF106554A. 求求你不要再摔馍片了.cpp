/**
 * [Unofficial Mirror] 2026 CCPC National Invitational (Nanchang) and The 3rd Jiangxi Provincial Programming Contest
 *
 * => A. 求求你不要再摔馍片了
 *
 * -> https://codeforces.com/gym/106554/problem/A
 *
 * Submissions ~> https://codeforces.com/gym/106554/submission/391832621 By huanhuanonly
 *
 * @b Linear-DP
 *
 * ----September 24, 2026 [10h:49m:35s]----
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

void chmax(auto& lhs, const auto& rhs)
{
    if (lhs < rhs)
    {
        lhs = rhs;
    }
}

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

    std::vector<uint64> v(n + 1);

    for (int i = 1; i <= n; ++i)
    {
        std::cin >> v[i];
    }

    static auto $ = [](int x, int y) -> int
    {
        return (y + 5 - x) % 5;
    };

    constexpr int inf = std::numeric_limits<int>::max() / 2;

    std::vector dp(n + 1, std::vector(6, std::vector(6, std::vector(6, -inf))));
    dp[0][0][0][0] = n;

    for (int i = 1; i <= n; ++i)
    {
        for (int ea = 0; ea <= 5; ++ea)
        {
            for (int sb = 0; sb <= 5; ++sb)
            {
                for (int eb = 0; eb <= 5; ++eb)
                {
                    if (ea)
                    {
                        chmax(dp[i][v[i]][sb][eb], dp[i - 1][ea][sb][eb] + $(ea, v[i]));
                    }
                    else
                    {
                        chmax(dp[i][v[i]][sb][eb], dp[i - 1][ea][sb][eb]);
                    }

                    if (sb)
                    {
                        chmax(dp[i][ea][sb][v[i]], dp[i - 1][ea][sb][eb] + $(eb, v[i]));
                    }
                    else
                    {
                        chmax(dp[i][ea][v[i]][v[i]], dp[i - 1][ea][sb][eb]);
                    }
                }
            }
        }
    }

    int max = 0;

    for (int ea = 0; ea <= 5; ++ea)
    {
        for (int sb = 0; sb <= 5; ++sb)
        {
            for (int eb = 0; eb <= 5; ++eb)
            {
                if (ea and sb)
                {
                    chmax(max, dp.back()[ea][sb][eb] + $(ea, sb));
                }
                else
                {
                    chmax(max, dp.back()[ea][sb][eb]);
                }
            }
        }
    }

    std::cout << max << '\n';

    return 0;
}
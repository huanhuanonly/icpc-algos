/**
 * Educational DP Contest
 * 
 * => C - Vacation ( @c 100 )
 * 
 * -> https://atcoder.jp/contests/dp/tasks/dp_c
 * 
 * Submissions ~> https://atcoder.jp/contests/dp/submissions/75095917 By huanhuanonly
 * 
 * @b Linear-DP
 * 
 * ----April 19, 2026 [00h:25m:15s]----
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

    int n;
    std::cin >> n;

    std::vector<std::array<int64, 3>> v(n + 1);

    for (int i = 1; i <= n; ++i)
    {
        std::cin >> v[i][0] >> v[i][1] >> v[i][2];
    }

    constexpr auto inf = std::numeric_limits<int64>::max() / 2;

    std::vector dp(n + 1, std::array<int64, 3>{});

    for (int i = 1; i <= n; ++i)
    {
        for (int j = 0; j < 3; ++j)
        {
            for (int k = 0; k < 3; ++k)
            {
                if (j != k)
                {
                    dp[i][j] = std::max(dp[i][j], dp[i - 1][k] + v[i][j]);
                }
            }
        }
    }

    std::cout << *std::ranges::max_element(dp.back()) << '\n';

    return 0;
}
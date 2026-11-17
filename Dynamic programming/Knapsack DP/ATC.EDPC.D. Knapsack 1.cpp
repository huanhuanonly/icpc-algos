/**
 * Educational DP Contest
 * 
 * => D - Knapsack 1 ( @c 100 )
 * 
 * -> https://atcoder.jp/contests/dp/tasks/dp_d
 * 
 * Submissions ~> https://atcoder.jp/contests/dp/submissions/75096003 By huanhuanonly
 * 
 * @b Knapsack-DP ( @a 0/1-knapsack-problem )
 * 
 * ----April 19, 2026 [00h:32m:44s]----
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

    int n, w;
    std::cin >> n >> w;

    std::vector<std::pair<int64, int64>> v(n + 1);

    for (int i = 1; i <= n; ++i)
    {
        std::cin >> v[i].first >> v[i].second;
    }

    std::vector dp(n + 1, std::vector(w + 1, int64{}));

    for (int i = 1; i <= n; ++i)
    {
        for (int j = 1; j <= w; ++j)
        {
            dp[i][j] = std::max(dp[i - 1][j], dp[i][j - 1]);

            if (j - v[i].first >= 0)
            {
                dp[i][j] = std::max(dp[i][j], dp[i - 1][j - v[i].first] + v[i].second);
            }
        }
    }

    std::cout << dp.back().back() << '\n';

    return 0;
}
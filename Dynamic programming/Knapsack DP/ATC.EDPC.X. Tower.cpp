/**
 * Educational DP Contest
 * 
 * => X - Tower ( @c 100 )
 * 
 * -> https://atcoder.jp/contests/dp/tasks/dp_x
 * 
 * Submissions ~> https://atcoder.jp/contests/dp/submissions/75136238 By huanhuanonly
 * 
 * @b Knapsack-DP ( @a 0/1-knapsack-problem )
 * 
 * ----April 20, 2026 [22h:52m:35s]----
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

    struct item
    {
        int w, s;
        uint64 v;
    };

    std::vector<item> d(n + 1);

    for (auto& [w, s, v] : d | std::views::drop(1))
    {
        std::cin >> w >> s >> v;
    }

    std::ranges::sort(d | std::views::drop(1), {}, [](const item& i) { return i.w + i.s; });

    constexpr int maxw = 2e4;
    std::vector dp(n + 1, std::vector(maxw + 1, uint64{}));

    for (int i = 1; i <= n; ++i)
    {
        for (int j = 1; j <= maxw; ++j)
        {
            if (d[i].w <= j and j - d[i].w <= d[i].s)
            {
                dp[i][j] = dp[i - 1][j - d[i].w] + d[i].v;
            }

            dp[i][j] = std::max({dp[i][j], dp[i][j - 1], dp[i - 1][j]});
        }
    }

    std::cout << dp.back().back() << '\n';

    return 0;
}
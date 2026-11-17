/**
 * Educational DP Contest
 * 
 * => A - Frog 1 ( @c 100 )
 * 
 * -> https://atcoder.jp/contests/dp/tasks/dp_a
 * 
 * Submissions ~> https://atcoder.jp/contests/dp/submissions/75095727 By huanhuanonly
 * 
 * @b Linear-DP
 * 
 * ----April 19, 2026 [00h:10m:11s]----
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

    std::vector<int> v(n);

    for (int i = 0; i < n; ++i)
    {
        std::cin >> v[i];
    }

    std::vector<int> dp(n);

    for (int i = 0; i < n; ++i)
    {
        if (i - 1 >= 0)
        {
            dp[i] = dp[i - 1] + std::abs(v[i] - v[i - 1]);
        }

        if (i - 2 >= 0)
        {
            dp[i] = std::min(dp[i], dp[i - 2] + std::abs(v[i] - v[i - 2]));
        }
    }

    std::cout << dp.back() << '\n';

    return 0;
}
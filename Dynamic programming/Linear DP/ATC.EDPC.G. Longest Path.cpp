/**
 * Educational DP Contest
 * 
 * => G - Longest Path ( @c 100 )
 * 
 * -> https://atcoder.jp/contests/dp/tasks/dp_g
 * 
 * Submissions ~> https://atcoder.jp/contests/dp/submissions/74973791 By huanhuanonly
 * 
 * @b Linear-DP
 * 
 * ----April 15, 2026 [14h:15m:06s]----
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

    int h, w;
    std::cin >> h >> w;

    constexpr uint64 mod = 1e9 + 7;

    std::vector<std::string> map(h);

    for (auto& i : map)
    {
        std::cin >> i;
    }

    std::vector dp(h, std::vector(w, uint64{}));

    dp[0][0] = 1;

    for (int i = 0; i < h; ++i)
    {
        for (int j = 0; j < w; ++j)
        {
            if (map[i][j] == '.')
            {
                if (i)
                {
                    dp[i][j] += dp[i - 1][j];
                }

                if (j)
                {
                    dp[i][j] += dp[i][j - 1];
                }

                dp[i][j] %= mod;
            }
        }
    }

    std::cout << dp.back().back() << '\n';

    return 0;
}
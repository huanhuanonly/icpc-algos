/**
 * 牛客周赛 Round 160
 *
 * => E-小月的相交弦 ( @c 1500 )
 *
 * -> https://ac.nowcoder.com/acm/contest/139989/E
 *
 * Submissions ~> https://ac.nowcoder.com/acm/contest/view-submission?submissionId=84661719 By huanhuanonly
 *
 * @b Interval-DP
 *
 * ----September 07, 2026 [11h:22m:47s]----
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

    n <<= 1;

    std::vector dp(n + 1, std::vector<int64>(n + 1));

    std::vector<std::pair<int, int>> lpos(n + 1);

    for (int i = 0; i < (n >> 1); ++i)
    {
        int l, r, w;
        std::cin >> l >> r >> w;

        if (w > 0)
        {
            lpos[r] = {l, w};
            dp[l][r] = w;
        }
    }

    for (int k = 1; k < n; ++k)
    {
        for (int l = 1; l + k <= n; ++l)
        {
            const int r = l + k;

            dp[l][r] = std::max({dp[l][r], dp[l][r - 1], dp[l + 1][r]});

            if (lpos[r].first == l)
            {
                dp[l][r] = std::max(dp[l][r], dp[l + 1][r - 1] + lpos[r].second);
            }
            else if (lpos[r].first - 1 >= l)
            {
                dp[l][r] = std::max(dp[l][r], dp[l][lpos[r].first - 1] + dp[lpos[r].first][r - 1] + lpos[r].second);
            }
        }
    }

    std::cout << dp[1][n] << '\n';

    return 0;
}
/**
 * 2026 ICPC Nanchang Invitational and Jiangxi Provincial Collegiate Programming Contest
 *
 * => I. Gotta Go Fast
 *
 * -> https://codeforces.com/gym/106551/problem/I
 *
 * Submissions ~> https://codeforces.com/gym/106551/submission/389432610 By huanhuanonly
 *
 * @b Linear-DP
 *
 * ----September 05, 2026 [16h:06m:21s]----
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

    int n, d;
    std::cin >> n >> d;

    std::array<int64, 3> t;
    std::cin >> t[0] >> t[1] >> t[2];

    std::string s;
    std::cin >> s;

    std::vector<std::array<int64, 4>> dp(n + 1);

    for (int i = 1; i <= n; ++i)
    {
        for (int c = 0; c < 4; ++c)
        {
            dp[i][c] = dp[i - 1][c] + t[s[i - 1] - '0'];

            if (c + 1 < 4)
            {
                dp[i][c] = std::min(dp[i][c], dp[std::max(i - d, 0)][c + 1]);
            }
        }
    }

    std::cout << std::ranges::min(dp.back()) << '\n';

    return 0;
}
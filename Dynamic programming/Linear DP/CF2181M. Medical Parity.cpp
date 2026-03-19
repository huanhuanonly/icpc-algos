/**
 * 2025-2026 ICPC, NERC, Northern Eurasia Finals (Unrated, Online Mirror, ICPC Rules, Teams Preferred)
 * 
 * => M. Medical Parity ( @c 1700 )
 * 
 * -> https://codeforces.com/contest/2181/problem/M
 * 
 * Submissions ~> https://codeforces.com/contest/2181/submission/356521548 By huanhuanonly
 * 
 * @b Linear-DP
 * 
 * ----January 05, 2026 [23h:55m:50s]----
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

    int _;
    std::cin >> _;

    while (_--)
    {
        std::string s, t;
        std::cin >> s >> t;

        const int n = static_cast<int>(s.size());

        std::vector dp(2, std::vector(n + 1, 0));
        dp[1][0] = std::numeric_limits<int>::max() / 2;

        for (int i = 1; i <= n; ++i)
        {
            dp[0][i] = std::min(dp[0][i - 1] + (s[i - 1] != '0'), dp[1][i - 1] + (s[i - 1] != '1')) + (t[i - 1] != '0');
            dp[1][i] = std::min(dp[1][i - 1] + (s[i - 1] != '0'), dp[0][i - 1] + (s[i - 1] != '1')) + (t[i - 1] != '1');
        }

        std::cout << std::min(dp[0][n], dp[1][n]) << '\n';
    }

    return 0;
}
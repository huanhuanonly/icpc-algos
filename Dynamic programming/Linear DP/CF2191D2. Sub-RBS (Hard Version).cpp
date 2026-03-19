/**
 * Codeforces Round 1073 (Div. 2)
 * 
 * => D2. Sub-RBS (Hard Version) ( @c 1900 )
 * 
 * -> https://codeforces.com/contest/2191/problem/D2
 * 
 * Submissions ~> https://codeforces.com/contest/2191/submission/360176906 By huanhuanonly
 * 
 * @b Linear-DP
 * 
 * ----January 27, 2026 [23h:46m:51s]----
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
        int n;
        std::cin >> n;

        std::string s;
        std::cin >> s;

        s.insert(s.begin(), '$');

        constexpr uint64 mod = 998244353;

        std::vector dp(n + 1, std::vector(n + 1, std::vector(n + 1, std::array<uint64, 4>{})));

        dp[0][0][0][0] = 1;

        for (int i = 1; i <= n; ++i)
        {
            dp[i] = dp[i - 1];

            for (int len = 1; len <= n; ++len)
            {
                for (int dif = 0; dif <= n; ++dif)
                {
                    if (s[i] == ')')
                    {
                        if (dif + 1 <= n)
                        {
                            (dp[i][len][dif][1] += dp[i - 1][len - 1][dif + 1][0]) %= mod;
                            (dp[i][len][dif][1] += dp[i - 1][len - 1][dif + 1][1]) %= mod;
                            (dp[i][len][dif][2] += dp[i - 1][len - 1][dif + 1][2]) %= mod;
                            (dp[i][len][dif][3] += dp[i - 1][len - 1][dif + 1][3]) %= mod;
                        }
                    }
                    else
                    {
                        if (dif - 1 >= 0)
                        {
                            (dp[i][len][dif][0] += dp[i - 1][len - 1][dif - 1][0]) %= mod;
                            (dp[i][len][dif][2] += dp[i - 1][len - 1][dif - 1][1]) %= mod;
                            (dp[i][len][dif][3] += dp[i - 1][len - 1][dif - 1][2]) %= mod;
                            (dp[i][len][dif][3] += dp[i - 1][len - 1][dif - 1][3]) %= mod;
                        }
                    }
                }
            }
        }

        uint64 ans = 0;

        for (int len = 3; len <= n; ++len)
        {
            (ans += dp[n][len][0][3] * (len - 2)) %= mod;
        }

        std::cout << ans << '\n';
    }

    return 0;
}
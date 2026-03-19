/**
 * Codeforces Round 1076 (Div. 3)
 * 
 * => E. Product Queries ( @c 1300 )
 * 
 * -> https://codeforces.com/contest/2193/problem/E
 * 
 * Submissions ~> https://codeforces.com/contest/2193/submission/359863787 By huanhuanonly
 * 
 * @b Linear-DP and @b Number-theory ( @a divisor )
 * 
 * ----January 26, 2026 [01h:42m:30s]----
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

        constexpr auto inf = std::numeric_limits<int>::max() / 2;

        std::vector<int> dp(n + 1, inf);

        for (int i = 0, v; i < n; ++i)
        {
            std::cin >> v;
            dp[v] = 1;
        }

        std::vector<std::vector<int>> table(n + 1);

        for (int i = 1; i <= n; ++i)
        {
            for (int j = 1; i * j <= n; ++j)
            {
                table[i * j].push_back(i);
            }
        }

        for (int i = 1; i <= n; ++i)
        {
            if (dp[i] == inf)
            {
                for (const auto& j : table[i])
                {
                    if (dp[j] == 1)
                    {
                        dp[i] = std::min(dp[i], dp[i / j] + 1);
                    }
                }
            }

            if (dp[i] != inf)
            {
                std::cout << dp[i] << ' ';
            }
            else
            {
                std::cout << -1 << ' ';
            }
        }

        std::cout.put('\n');
    }

    return 0;
}
/**
 * 牛客周赛 Round 105
 * 
 * => F-小苯的前缀gcd构造 ( @c 1800 )
 * 
 * -> https://ac.nowcoder.com/acm/contest/115861/F
 * 
 * Submissions ~> https://ac.nowcoder.com/acm/contest/view-submission?submissionId=78907337 By huanhuanonly
 * 
 * @b Linear-DP and @b Number-theory ( @a greatest-common-divisor )
 * 
 * ----August 18, 2025 [13h:05m:29s]----
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

    constexpr int maxn = 50;
    std::vector<std::vector<int>> ds(maxn + 1);

    for (int i = 1; i <= maxn; ++i)
    {
        for (int j = i; j <= maxn; j += i)
        {
            ds[j].push_back(i);
        }
    }

    int _;
    std::cin >> _;

    while (_--)
    {
        int n, m, x;
        std::cin >> n >> m >> x;

        std::vector dp(n + 1, std::vector(m + 1, std::vector(x + 1, 0)));

        for (int i = 1; i <= std::min(m, x); ++i)
        {
            dp[1][i][i] = i;
        }

        for (int i = 1; i < n; ++i)
        {
            for (int j = 1; j <= m; ++j)
            {
                for (int k = 1; k <= x; ++k)
                {
                    if (dp[i][j][k])
                    {
                        for (int d : ds[j])
                        {
                            if (k + d > x)
                            {
                                break;
                            }

                            dp[i + 1][d][k + d] = j;
                        }
                    }
                }
            }
        }

        int cur = -1;

        for (int i = 1; i <= m; ++i)
        {
            if (dp[n][i][x])
            {
                cur = i;
                break;
            }
        }

        if (cur == -1)
        {
            std::cout << -1 << '\n';
        }
        else
        {
            std::vector<int> ans(n + 1);

            for (int i = n; i >= 1; --i)
            {
                ans[i] = cur;

                cur = dp[i][cur][x];
                x -= ans[i];
            }

            for (int i = 1; i <= n; ++i)
            {
                std::cout << ans[i] << " \n"[i == n];
            }
        }
    }

    return 0;
}
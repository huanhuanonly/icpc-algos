/**
 * Educational DP Contest
 * 
 * => E - Knapsack 2 ( @c 100 )
 * 
 * -> https://atcoder.jp/contests/dp/tasks/dp_e
 * 
 * Submissions ~> https://atcoder.jp/contests/dp/submissions/69927684 By huanhuanonly
 * 
 * @b Knapsack-DP ( @a 0/1-knapsack-problem )
 * 
 * ----October 06, 2025 [19h:31m:40s]----
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

    int64 N, W;
    std::cin >> N >> W;

    std::vector<int64> w(N + 1), v(N + 1);

    for (int i = 1; i <= N; ++i)
    {
        std::cin >> w[i] >> v[i];
    }

    constexpr auto inf = std::numeric_limits<int64>::max() / 2;
    std::vector dp(N + 1, std::vector(N * int64(1e3) + 1, inf));

    dp[0][0] = 0;

    for (int i = 1; i <= N; ++i)
    {
        for (int j = 0; j < dp[N].size(); ++j)
        {
            if (j >= v[i])
            {
                dp[i][j] = std::min(dp[i - 1][j], dp[i - 1][j - v[i]] + w[i]);
            }
            else
            {
                dp[i][j] = dp[i - 1][j];
            }
        }
    }

    int64 ans = 0;

    for (int i = 0; i < dp[N].size(); ++i)
    {
        if (dp[N][i] <= W)
        {
            ans = i;
        }
    }

    std::cout << ans;

    return 0;
}
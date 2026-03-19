/**
 * JPRS Programming Contest 2026#1 (AtCoder Beginner Contest 442)
 * 
 * => F - Diagonal Separation 2 ( @c 500 )
 * 
 * -> https://atcoder.jp/contests/abc442/tasks/abc442_f
 * 
 * Submissions ~> https://atcoder.jp/contests/abc442/submissions/72737865 By huanhuanonly
 * 
 * @b Linear-DP
 * 
 * ----January 24, 2026 [23h:12m:02s]----
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

    int n;
    std::cin >> n;

    std::vector<std::string> mp(n);

    for (std::string& i : mp)
    {
        std::cin >> i;
    }

    constexpr auto inf = std::numeric_limits<int>::max() / 2;

    std::vector<int> dp(n + 2);
    dp[n + 1] = inf;

    std::vector<int> pre(n + 1);

    for (int i = 1; i <= n; ++i)
    {
        for (int j = 1; j <= n; ++j)
        {
            pre[j] = pre[j - 1] + (mp[i - 1][j - 1] == '.');
        }

        for (int j = n; j >= 0; --j)
        {
            dp[j] = std::min(dp[j + 1], dp[j] + (j - pre[j]) + (pre[n] - pre[j]));
        }
    }

    std::cout << dp[0];

    return 0;
}
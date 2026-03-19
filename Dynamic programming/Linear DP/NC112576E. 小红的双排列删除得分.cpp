/**
 * 牛客周赛 Round 100
 * 
 * => E-小红的双排列删除得分 ( @c 1500 )
 * 
 * -> https://ac.nowcoder.com/acm/contest/112576/E
 * 
 * Submissions ~> https://ac.nowcoder.com/acm/contest/view-submission?submissionId=78155021 By huanhuanonly
 * 
 * @b Linear-DP
 * 
 * ----July 13, 2025 [22h:59m:36s]----
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

    n <<= 1;

    std::vector<uint64> v(n + 1);

    for (int i = 1; i <= n; ++i)
    {
        std::cin >> v[i];
    }

    std::map<int, int> mp;

    std::vector<uint64> pre(n + 1);
    std::partial_sum(v.begin(), v.end(), pre.begin());

    for (int i = 1; i <= n; ++i)
    {
        if (not mp.contains(v[i]))
        {
            mp[v[i]] = i;
        }
    }

    std::vector<uint64> dp(n + 1);

    for (int i = 1; i <= n; ++i)
    {
        if (mp[v[i]] != i)
        {
            dp[i] = std::max(dp[i - 1], dp[mp[v[i]] - 1] + pre[i] - pre[mp[v[i]] - 1]);
        }
        else
        {
            dp[i] = dp[i - 1];
        }
    }

    std::cout << dp.back();

    return 0;
}
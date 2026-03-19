/**
 * 2026牛客寒假算法基础集训营1
 * 
 * => H-Blackboard ( @c 2000 )
 * 
 * -> https://ac.nowcoder.com/acm/contest/120561/H
 * 
 * Submissions ~> https://ac.nowcoder.com/acm/contest/view-submission?submissionId=81961396 By huanhuanonly
 * 
 * @b Linear-DP and @b Bitwise-OR
 * 
 * ----February 03, 2026 [16h:44m:44s]----
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

    int _;
    std::cin >> _;

    while (_--)
    {
        int n;
        std::cin >> n;

        std::vector<uint64> v(n);

        for (int i = 0; i < n; ++i)
        {
            std::cin >> v[i];
        }

        constexpr uint64 mod = 998244353;

        std::vector dp(n, std::array<uint64, 2>{});
        dp[0][0] = 1;

        std::deque<int> que{0};
        std::pair<uint64, uint64> sum{v[0], dp[0][0]};

        for (int i = 1; i < n; ++i)
        {
            dp[i][0] = (dp[i - 1][0] + dp[i - 1][1]) % mod;

            while (sum.first & v[i])
            {
                sum.first &= ~v[que.front()];
                sum.second = (sum.second + mod - dp[que.front()][0]) % mod;

                que.pop_front();
            }
            
            dp[i][1] = sum.second;
            
            sum.first |= v[i];
            (sum.second += dp[i][0]) %= mod;
            
            que.push_back(i);
        }

        std::cout << (dp.back()[0] + dp.back()[1]) % mod << '\n';
    }

    return 0;
}
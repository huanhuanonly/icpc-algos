/**
 * Educational DP Contest
 * 
 * => S - Digit Sum ( @c 100 )
 * 
 * -> https://atcoder.jp/contests/dp/tasks/dp_s
 * 
 * Submissions ~> https://atcoder.jp/contests/dp/submissions/75025168 By huanhuanonly
 * 
 * @b Digit-DP
 * 
 * ----April 18, 2026 [12h:21m:18s]----
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

    std::string s;
    int d;
    
    std::cin >> s >> d;

    constexpr uint64 mod = 1e9 + 7;

    std::vector dp(s.size(), std::vector(d, uint64(-1)));

    auto dfs = [&](const auto& self, int pos, int sum, bool lead, bool limit) -> uint64
    {
        if (pos == s.size())
        {
            return not lead and sum == 0;
        }

        if (not lead and not limit and ~dp[pos][sum])
        {
            return dp[pos][sum];
        }

        uint64 cnt = 0;

        for (int i = 0, up = limit ? s[pos] - '0' : 9; i <= up; ++i)
        {
            cnt += self(self, pos + 1, (sum + i) % d, lead and i == 0, limit and i == up);
            cnt %= mod;
        }

        if (not lead and not limit)
        {
            dp[pos][sum] = cnt;
        }

        return cnt;
    };

    std::cout << dfs(dfs, 0, 0, true, true) << '\n';

    return 0;
}
/**
 * 2026牛客寒假算法基础集训营1
 * 
 * => G-Digital Folding ( @c 1600 )
 * 
 * -> https://ac.nowcoder.com/acm/contest/120561/G
 * 
 * Submissions ~> https://ac.nowcoder.com/acm/contest/view-submission?submissionId=81946318 By huanhuanonly
 * 
 * @b Digit-DP
 * 
 * ----February 03, 2026 [15h:46m:42s]----
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
        std::string l, r;
        std::cin >> l >> r;

        if (l.size() != r.size())
        {
            l.insert(0, std::string(r.size() - l.size(), '0'));
        }

        std::vector<uint64> dp(l.size(), -1);

        auto dfs = [&](const auto& self, int pos, bool llim, bool ulim, bool lead) -> uint64
        {
            if (pos == l.size())
            {
                return 0;
            }

            if (not llim and not ulim and not lead and ~dp[pos])
            {
                return dp[pos];
            }

            const int low = llim ? l[pos] - '0' : 0;
            const int upp = ulim ? r[pos] - '0' : 9;

            uint64 ans = 0;

            for (int i = low; i <= upp; ++i)
            {
                const uint64 res = self(self, pos + 1, llim and i == low, ulim and i == upp, lead and i == 0);
                
                if (lead and i == 0)
                {
                    ans = std::max(ans, res);
                }
                else
                {
                    ans = std::max(ans, res * 10 + i);
                }
            }

            if (not llim and not ulim and not lead)
            {
                dp[pos] = ans;
            }

            return ans;
        };

        std::cout << dfs(dfs, 0, true, true, true) << '\n';
    }

    return 0;
}
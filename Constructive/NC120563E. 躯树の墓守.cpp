/**
 * 2026牛客寒假算法基础集训营3
 * 
 * => E-躯树の墓守 ( @c 2400 )
 * 
 * -> https://ac.nowcoder.com/acm/contest/120563/E
 * 
 * Submissions ~> https://ac.nowcoder.com/acm/contest/view-submission?submissionId=82700276 By huanhuanonly
 * 
 * @b Constructive and @b Minimum-spanning-tree
 * 
 * ----March 10, 2026 [23h:40m:46s]----
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
        int64 n, m, k;
        std::cin >> n >> m >> k;

        if (n == 1 or n * (n - 1) / 2 > k)
        {
            std::cout << "NO\n";
            continue;
        }

        std::vector<bool> used(m + 1);

        std::vector<int64> x(n);

        int64 sum = k - n * (n - 1) / 2;
        
        for (int64 i = n - 1; i >= 1; --i)
        {
            x[i] = std::min({(i - 2) * (i - 1) / 2, m - n + 1, sum});
            sum -= x[i];
        }

        if (sum)
        {
            std::cout << "NO\n";
            continue;
        }

        for (int64 i = 1; i < n; ++i)
        {
            used[i + x[i]] = true;
        }

        std::vector<std::tuple<int, int, int>> ans;
        ans.reserve(m);

        for (int i = 1, c = 1, u = 2, v = 2; i <= m; ++i)
        {
            if (used[i])
            {
                ans.emplace_back(++c, 1, i);
            }
            else
            {
                if (u <= v)
                {
                    ++u;
                    v = 2;
                }

                ans.emplace_back(u, v++, i);
            }
        }

        std::cout << "YES\n";

        for (const auto& [u, v, w] : ans)
        {
            std::cout << u << ' ' << v << ' ' << w << '\n';
        }
    }

    return 0;
}
/**
 * 2026牛客寒假算法基础集训营5
 * 
 * => C-智乃的草坪 ( @c 2300 )
 * 
 * -> https://ac.nowcoder.com/acm/contest/120565/C
 * 
 * Submissions ~> https://ac.nowcoder.com/acm/contest/view-submission?submissionId=82688824 By huanhuanonly
 * 
 * @b Binary-search and @b Geometry
 * 
 * ----March 10, 2026 [09h:24m:32s]----
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

    do
    {
        uint64 n, k, r, c;
        std::cin >> n >> k >> r >> c;

        std::vector<std::pair<uint64, uint64>> s(n);

        for (auto& [p, v] : s)
        {
            std::cin >> p >> v;
        }

        constexpr real80 eps = 1e-7;

        auto check = [&](real80 t) -> bool
        {
            std::vector<std::pair<real80, real80>> pre;
            pre.reserve(n);

            for (uint64 i = 0; i < n; ++i)
            {
                const auto& [p, v] = s[i];

                const auto res = std::sqrt(v * t * v * t - r * r);

                if (not std::isnan(res))
                {
                    const auto left = -res + p;
                    const auto right = res + p;
                    
                    pre.emplace_back(left, right);
                }
            }

            std::ranges::sort(pre);

            real80 pos = 0;
            real80 max = 0;
            uint64 cnt = 0;
            
            for (uint64 i = 0; cnt < k; ++cnt)
            {
                for (; i < pre.size() and pre[i].first <= pos; max = std::max(max, pre[i].second), ++i);
                pos = max + eps;
            }

            return pos > c;
        };

        real80 lo = 0, hi = 1e6, mid;

        while (hi - lo > eps)
        {
            mid = (lo + hi) / 2;

            if (check(mid))
            {
                hi = mid;
            }
            else
            {
                lo = mid;
            }
        }

        std::cout << std::fixed << std::setprecision(12) << hi << '\n';

    } while (false);

    return 0;
}
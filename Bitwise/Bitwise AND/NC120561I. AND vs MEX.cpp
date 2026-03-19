/**
 * 2026牛客寒假算法基础集训营1
 * 
 * => I-AND vs MEX ( @c 2400 )
 * 
 * -> https://ac.nowcoder.com/acm/contest/120561/I
 * 
 * Submissions ~> https://ac.nowcoder.com/acm/contest/view-submission?submissionId=82005732 By huanhuanonly
 * 
 * @b Bitwise-AND and @b Classification-discussion
 * 
 * ----February 04, 2026 [23h:18m:48s]----
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
        uint64 l, r;
        std::cin >> l >> r;

        if (l == 0 or std::bit_width(l) + 1 < std::bit_width(r))
        {
            std::cout << r + 1 << '\n';
        }
        else if (std::bit_floor(l) == std::bit_floor(r))
        {
            std::cout << 0 << '\n';
        }
        else
        {
            if (not std::has_single_bit(l + 1))
            {
                l &= ~(std::bit_floor(~l & std::bit_floor(l) - 1) - 1);
            }

            if (const uint64 ans = (r ^ std::bit_floor(r)) + 1; ans >= l)
            {
                std::cout << r + 1 << '\n';
            }
            else
            {
                std::cout << ans << '\n';
            }
        }
    }

    return 0;
}
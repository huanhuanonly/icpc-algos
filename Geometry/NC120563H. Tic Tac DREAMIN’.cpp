/**
 * 2026牛客寒假算法基础集训营3
 * 
 * => H-Tic Tac DREAMIN’ ( @c 1200 )
 * 
 * -> https://ac.nowcoder.com/acm/contest/120563/H
 * 
 * Submissions ~> https://ac.nowcoder.com/acm/contest/view-submission?submissionId=82135820 By huanhuanonly
 * 
 * @b Geometry
 * 
 * ----February 07, 2026 [15h:06m:20s]----
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

    int64 x1, y1, x2, y2;
    std::cin >> x1 >> y1 >> x2 >> y2;

    const int64 a = x1 * y2 - x2 * y1;
    const int64 k = y1 - y2;

    if (k == 0)
    {
        if (std::abs(a) == 4)
        {
            std::cout << 0;
        }
        else
        {
            std::cout << "no answer";
        }
    }
    else
    {
        std::cout << std::fixed << std::setprecision(12) << real64(4 - a) / k;
    }

    return 0;
}
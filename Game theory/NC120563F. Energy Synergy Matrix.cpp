/**
 * 2026牛客寒假算法基础集训营3
 * 
 * => F-Energy Synergy Matrix ( @c 1400 )
 * 
 * -> https://ac.nowcoder.com/acm/contest/120563/F
 * 
 * Submissions ~> https://ac.nowcoder.com/acm/contest/view-submission?submissionId=82162725 By huanhuanonly
 * 
 * @b Game-theory
 * 
 * ----February 08, 2026 [22h:13m:21s]----
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
        uint64 n;
        std::cin >> n;

        if (n < 5)
        {
            std::cout << n - 1 << '\n';
        }
        else
        {
            std::cout << n + (n - 5) / 5 << '\n';
        }
    }

    return 0;
}
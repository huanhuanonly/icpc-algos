/**
 * 2026牛客寒假算法基础集训营2
 * 
 * => E-01矩阵 ( @c 1800 )
 * 
 * -> https://ac.nowcoder.com/acm/contest/120562/E
 * 
 * Submissions ~> https://ac.nowcoder.com/acm/contest/view-submission?submissionId=82071148 By huanhuanonly
 * 
 * @b Constructive
 * 
 * ----February 05, 2026 [17h:09m:53s]----
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

    int n;
    std::cin >> n;

    std::vector map(n, std::string(n, '0'));

    for (int d = n - 2; d >= 0; d -= 2)
    {
        for (int i = 0; i <= d; ++i)
        {
            map[i][d] = '1';
        }

        for (int j = 0; j <= d; ++j)
        {
            map[d][j] = '1';
        }
    }

    for (const std::string& i : map)
    {
        std::cout << i << '\n';
    }

    return 0;
}
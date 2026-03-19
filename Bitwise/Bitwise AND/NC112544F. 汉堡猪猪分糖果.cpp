/**
 * 牛客周赛 Round 99
 * 
 * => F-汉堡猪猪分糖果 ( @c 2000 )
 * 
 * -> https://ac.nowcoder.com/acm/contest/112544/F
 * 
 * Submissions ~> https://ac.nowcoder.com/acm/contest/view-submission?submissionId=78078021 By huanhuanonly
 * 
 * @b Bitwise-AND
 * 
 * ----July 06, 2025 [22h:04m:37s]----
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

    int _;
    std::cin >> _;

    while (_--)
    {
        uint64 n, m;
        std::cin >> n >> m;

        uint64 ans = 0;

        for (uint64 cur = (1ULL << 32ULL); cur; cur >>= 1ULL)
        {
            if (n >= cur * m)
            {
                n -= cur * m;
                ans |= cur;
            }
            else if (cur > 1 and n > (cur - 1) * m)
            {
                uint64 l = 0, r = m, mid;

                while (r - l > 1)
                {
                    mid = l + r >> 1;

                    if (n - cur * mid <= (cur - 1) * m)
                    {
                        r = mid;
                    }
                    else
                    {
                        l = mid;
                    }
                }

                n -= cur * r;
            }
        }

        std::cout << ans << '\n';
    }

    return 0;
}
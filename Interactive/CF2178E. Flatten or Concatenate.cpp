/**
 * Good Bye 2025
 * 
 * => E. Flatten or Concatenate ( @c 2000 )
 * 
 * -> https://codeforces.com/contest/2178/problem/E
 * 
 * Submissions ~> https://codeforces.com/contest/2178/submission/355825127 By huanhuanonly
 * 
 * @b Interactive and @b Binary-search
 * 
 * ----December 30, 2025 [11h:40m:17s]----
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

uint64 query(uint64 l, uint64 r)
{
    std::cout << "? " << l << ' ' << r << std::endl;

    uint64 res;
    std::cin >> res;

    return res;
}

void answer(uint64 m)
{
    std::cout << "! " << m << std::endl;
}

int main(void)
{
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr), std::cout.tie(nullptr);

    int _;
    std::cin >> _;

    while (_--)
    {
        uint64 n;
        std::cin >> n;

        uint64 l = 1, r = n;
        uint64 sum = query(l, r);

        while (l != r)
        {
            sum >>= 1;

            uint64 lo = l, hi = r, mid;

            while (hi - lo > 1)
            {
                mid = lo + hi >> 1;

                if (query(l, mid) <= sum)
                {
                    lo = mid;
                }
                else
                {
                    hi = mid;
                }
            }

            if (lo - l <= r - (lo + 1))
            {
                r = lo;
            }
            else
            {
                l = lo + 1;
            }
        }

        answer(query(l, r));
    }

    return 0;
}
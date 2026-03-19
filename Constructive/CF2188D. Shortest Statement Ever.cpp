/**
 * Codeforces Round 1077 (Div. 2)
 * 
 * => D. Shortest Statement Ever ( @c 1800 )
 * 
 * -> https://codeforces.com/contest/2188/problem/D
 * 
 * Submissions ~> https://codeforces.com/contest/2188/submission/360839756 By huanhuanonly
 * 
 * @b Constructive and @b Bitwise-AND
 * 
 * ----January 31, 2026 [17h:50m:12s]----
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
        static auto compute = [](uint64 x, uint64 y) -> uint64
        {
            const uint64 mark = std::bit_floor(x & y);
            const uint64 fbit = 1 << std::countr_one(x | y | mark - 1);

            const uint64 p1 = x & ~(fbit - 1) | fbit;
            const uint64 p2 = (x & ~(mark - 1) | ~y & mark - 1) ^ mark;

            return p1 - x <= x - p2 ? p1 : p2;
        };

        static auto difference = [](uint64 x, uint64 y) -> uint64
        {
            if (x < y)
            {
                std::swap(x, y);
            }

            return x - y;
        };

        uint64 x, y;
        std::cin >> x >> y;

        if (x & y)
        {
            const uint64 p = compute(x, y);
            const uint64 q = compute(y, x);

            assert(not (p & y));
            assert(not (x & q));

            if (difference(p, x) <= difference(q, y))
            {
                std::cout << p << ' ' << y << '\n';
            }
            else
            {
                std::cout << x << ' ' << q << '\n';
            }
        }
        else
        {
            std::cout << x << ' ' << y << '\n';
        }
    }

    return 0;
}
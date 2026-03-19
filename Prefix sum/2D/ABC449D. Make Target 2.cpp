/**
 * AtCoder Beginner Contest 449
 * 
 * => D - Make Target 2 ( @c 425 )
 * 
 * -> https://atcoder.jp/contests/abc449/tasks/abc449_d
 * 
 * Submissions ~> https://atcoder.jp/contests/abc449/submissions/74126031 By huanhuanonly
 * 
 * @b 2D-Prefix-sum
 * @b Geometry
 * @b Classification-discussion
 * 
 * ----March 14, 2026 [21h:42m:39s]----
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

    static auto count = [](int64 x, int64 y) -> int64
    {
        if (x < 0 or y < 0)
        {
            return 0;
        }

        if (x > y)
        {
            std::swap(x, y);
        }

        int64 sum = 0;

        for (int64 i = 0; i <= x; i += 2)
        {
            sum += i * 2 + 1;
        }

        return sum + (y - x + (x & 1)) / 2 * (x + 1);
    };

    static auto calc = [](int64 x0, int64 y0, int64 x1, int64 y1) -> int64
    {
        return count(x1, y1) - count(x0 - 1, y1) - count(x1, y0 - 1) + count(x0 - 1, y0 - 1);
    };

    static auto $ = [](int64 n) -> int64
    {
        return n >= 0 ? n / 2 + 1 : 0;
    };

    int64 l, r, d, u;
    std::cin >> l >> r >> d >> u;

    int64 sum = 0;

    if (l <= 0 and r <= 0)
    {
        l = -l;
        r = -r;

        if (l > r)
        {
            std::swap(l, r);
        }
    }

    if (d <= 0 and u <= 0)
    {
        d = -d;
        u = -u;

        if (d > u)
        {
            std::swap(d, u);
        }
    }

    if (l < 0 and r > 0)
    {
        if (d < 0 and u > 0)
        {
            sum += calc(0, 0, std::abs(l), std::abs(u));
            sum += calc(0, 0, std::abs(l), std::abs(d));
            sum += calc(0, 0, std::abs(r), std::abs(u));
            sum += calc(0, 0, std::abs(r), std::abs(d));

            sum -= $(std::abs(l)) + $(std::abs(r)) + $(std::abs(u)) + $(std::abs(d)) - 1;
        }
        else
        {
            sum += calc(0, d, std::abs(l), std::abs(u));
            sum += calc(1, d, std::abs(r), std::abs(u));
        }
    }
    else
    {
        if (d < 0 and u > 0)
        {
            sum += calc(l, 0, std::abs(r), std::abs(u));
            sum += calc(l, 1, std::abs(r), std::abs(d));
        }
        else
        {
            sum += calc(l, d, r, u);
        }
    }

    std::cout << sum << '\n';

    return 0;
}
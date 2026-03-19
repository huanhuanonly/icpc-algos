/**
 * Educational Codeforces Round 187 (Rated for Div. 2)
 * 
 * => C. Test Generator ( @c Rating )
 * 
 * -> https://codeforces.com/contest/2203/problem/C
 * 
 * Submissions ~> https://codeforces.com/contest/2203/submission/367294557 By huanhuanonly
 * 
 * @b Binary-search and @b Bitwise-AND
 * 
 * ----March 19, 2026 [09h:50m:38s]----
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
        uint64 s, m;
        std::cin >> s >> m;

        auto check = [&](uint64 mid) -> bool
        {
            std::array<uint64, 62> v{};
    
            for (int i = 60; i >= 0; --i)
            {
                if (s & (1ULL << i))
                {
                    ++v[i + 1];
                }
    
                if (not (m & (1ULL << i)))
                {
                    v[i] = v[i + 1] * 2;
                    v[i + 1] = 0;
                }

                if (v[i + 1] > mid)
                {
                    v[i] += (v[i + 1] - mid) * 2;
                    v[i + 1] = mid;
                }
            }

            return v[0] == 0;
        };

        uint64 l = 0, r = uint64(1e18) + 1, mid;

        while (r - l > 1)
        {
            mid = l + r >> 1;

            if (check(mid))
            {
                r = mid;
            }
            else
            {
                l = mid;
            }
        }

        if (r <= uint64(1e18))
        {
            std::cout << r << '\n';
        }
        else
        {
            std::cout << -1 << '\n';
        }
    }

    return 0;
}
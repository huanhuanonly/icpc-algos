/**
 * Codeforces Round 1108 (Div. 2)
 *
 * => D. diss_quack and Array Game ( @c 1900 )
 *
 * -> https://codeforces.com/contest/2246/problem/D
 *
 * Submissions ~> https://codeforces.com/contest/2246/submission/382303066 By huanhuanonly
 *
 * @b Game-theory
 *
 * ----July 13, 2026 [01h:24m:30s]----
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
        int n;
        std::cin >> n;

        std::vector<uint64> v(n);

        for (int i = 0; i < n; ++i)
        {
            std::cin >> v[i];
        }

        static auto cost = [](uint64 x) -> uint64
        {
            return std::popcount(x) + std::bit_width(x) - 1;
        };

        constexpr uint64 inf = std::numeric_limits<uint64>::max();
        uint64 ans = inf;

        for (uint64 c = 0; c <= 30; ++c)
        {
            uint64 cnt = c;

            for (int i = 0; i < n; ++i)
            {
                uint64 min = inf;

                for (uint64 cc = c; cc <= 30; ++cc)
                {
                    uint64 t = (v[i] + (1 << cc) - 1) / (1 << cc) * (1 << cc);
                    min = std::min(min, t - v[i] + cost(t / (1 << c)));
                }

                cnt += min;
            }

            ans = std::min(ans, cnt);
        }

        std::cout << ans << '\n';
    }

    return 0;
}
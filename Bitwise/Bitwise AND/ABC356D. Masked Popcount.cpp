/**
 * AtCoder Beginner Contest 356
 *
 * => D - Masked Popcount ( @c 400 )
 *
 * -> https://atcoder.jp/contests/abc356/tasks/abc356_d
 *
 * Submissions ~> https://atcoder.jp/contests/abc356/submissions/78139441 By huanhuanonly
 *
 * @b Bitwise-AND
 *
 * ----August 06, 2026 [01h:14m:24s]----
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

    uint64 n, m;
    std::cin >> n >> m;

    constexpr uint64 mod = 998244353;
    uint64 sum = 0;

    for (uint64 i = 1; i < 1ULL << 63; i <<= 1)
    {
        if (m & i)
        {
            uint64 cnt = (n + 1) / (i << 1) * i;
            uint64 rem = (n + 1) % (i << 1);

            if (rem > i)
            {
                cnt += rem - i;
            }

            sum += cnt;
            sum %= mod;
        }
    }

    std::cout << sum << '\n';

    return 0;
}
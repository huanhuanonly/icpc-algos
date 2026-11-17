/**
 * AtCoder Beginner Contest 367
 *
 * => D - Pedometer ( @c 400 )
 *
 * -> https://atcoder.jp/contests/abc367/tasks/abc367_d
 *
 * Submissions ~> https://atcoder.jp/contests/abc367/submissions/78157744 By huanhuanonly
 *
 * @b Number-theory ( @a modular-arithmetic )
 * @b Prefix-sum
 *
 * ----August 07, 2026 [02h:49m:47s]----
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

    std::vector<uint64> v(n + n + 1);

    for (uint64 i = 1; i <= n; ++i)
    {
        std::cin >> v[i];
        v[i + n] = v[i] %= m;
    }

    for (uint64 i = 1; i <= n + n; ++i)
    {
        (v[i] += v[i - 1]) %= m;
    }

    std::map<uint64, uint64> cnt{{0, 1}};

    uint64 sum = 0;

    for (uint64 i = 1; i < n + n; ++i)
    {
        if (i >= n)
        {
            --cnt[v[i - n]];
        }

        sum += cnt[v[i]];

        if (i < n)
        {
            ++cnt[v[i]];
        }
    }

    std::cout << sum << '\n';

    return 0;
}
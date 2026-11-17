/**
 * AtCoder Beginner Contest 356
 *
 * => E - Max/Min ( @c 475 )
 *
 * -> https://atcoder.jp/contests/abc356/tasks/abc356_e
 *
 * Submissions ~> https://atcoder.jp/contests/abc356/submissions/78157521 By huanhuanonly
 *
 * @b Prefix-sum
 *
 * ----August 07, 2026 [01h:56m:16s]----
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

    constexpr uint64 maxv = 1e6;
    std::vector<uint64> cnt(maxv + 1);

    for (uint64 i = 0, v; i < n; ++i)
    {
        std::cin >> v;
        ++cnt[v];
    }

    uint64 sum = 0;

    for (uint64 i = 1; i <= maxv; ++i)
    {
        if (cnt[i])
        {
            sum += cnt[i] * (cnt[i] - 1) / 2;
        }
    }

    std::partial_sum(cnt.begin(), cnt.end(), cnt.begin());

    for (uint64 i = 1; i <= maxv; ++i)
    {
        sum += (cnt[std::min(i * 2 - 1, maxv)] - cnt[i]) * (cnt[i] - cnt[i - 1]);

        for (uint64 k = 2; i * k <= maxv; ++k)
        {
            sum += k * (cnt[std::min(i * (k + 1) - 1, maxv)] - cnt[i * k - 1]) * (cnt[i] - cnt[i - 1]);
        }
    }

    std::cout << sum << '\n';

    return 0;
}
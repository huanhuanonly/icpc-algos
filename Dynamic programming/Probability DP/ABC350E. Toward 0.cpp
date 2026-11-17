/**
 * AtCoder Beginner Contest 350
 *
 * => E - Toward 0 ( @c 450 )
 *
 * -> https://atcoder.jp/contests/abc350/tasks/abc350_e
 *
 * Submissions ~> https://atcoder.jp/contests/abc350/submissions/78138187 By huanhuanonly
 *
 * @b Expectation-DP and @b Dfs
 *
 * ----August 05, 2026 [22h:57m:40s]----
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

    uint64 n, a, x, y;
    std::cin >> n >> a >> x >> y;

    std::map<uint64, real80> record;

    auto dfs = [&](this const auto& f, uint64 n) -> real80
    {
        if (not n)
        {
            return 0;
        }

        if (auto it = record.find(n); it != record.end())
        {
            return it->second;
        }

        return record[n] = std::min(
            x + f(n / real80(a)),
            (y + (f(n / 2.L) + f(n / 3.L) + f(n / 4.L) + f(n / 5.L) + f(n / 6.L)) * (1 / 6.L)) / 5.L * 6.L
        );
    };

    std::cout << std::fixed << std::setprecision(12) << dfs(n) << '\n';

    return 0;
}
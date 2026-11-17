/**
 * Codeforces Round 1122 (Div. 3)
 *
 * => E. Prime Destruction ( @c 1400 )
 *
 * -> https://codeforces.com/contest/2266/problem/E
 *
 * Submissions ~> https://codeforces.com/contest/2266/submission/392858296 By huanhuanonly
 *
 * @b Number-theory ( @a prime-factorization )
 * @b Memoized-search
 *
 * ----October 02, 2026 [00h:23m:41s]----
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

inline namespace huanhuanonly {
    inline namespace math
{
template<typename _Tp>
[[nodiscard]] std::vector<_Tp>
prime_factorization(_Tp __n)
{
    std::vector<_Tp> res;

    for (_Tp i = 2; i * i <= __n; ++i)
    {
        if (__n % i == 0)
        {
            res.push_back(i);
            for (__n /= i; __n % i == 0; __n /= i);
        }

    }

    if (__n != 1)
    {
        res.push_back(__n);
    }

    return res;
}
}} // namespace huanhuanonly::math

int main(void)
{
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);

#ifdef __huanhuanonly_localhost
    ::freopen("in", "r", stdin);
    ::freopen("out", "w", stdout);
#endif

    constexpr int maxv = 2e5;
    const auto pds =
        std::views::iota(0, maxv + 1) |
        std::views::transform(&prime_factorization<int>) |
        std::ranges::to<std::vector>();

    int _;
    std::cin >> _;

    while (_--)
    {
        int n, k;
        std::cin >> n >> k;

        constexpr auto inf = std::numeric_limits<uint64>::max() / 2;
        std::vector<uint64> record(n + 1, inf);

        auto dfs = [&](const auto& self, int p) -> uint64
        {
            if (p <= k)
            {
                return 0;
            }

            if (record[p] != inf)
            {
                return record[p];
            }

            for (const auto& pd : pds[p])
            {
                record[p] = std::min(record[p], 1 + self(self, p / pd) * pd);
            }

            return record[p];
        };

        uint64 ans = 0;

        for (int i = 0, v; i < n; ++i)
        {
            std::cin >> v;
            ans += dfs(dfs, v);
        }

        std::cout << ans << '\n';
    }

    return 0;
}
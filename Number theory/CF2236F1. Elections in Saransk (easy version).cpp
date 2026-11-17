/**
 * Codeforces Round 1103 (Div. 3)
 *
 * => F1. Elections in Saransk (easy version) ( @c 1700 )
 *
 * -> https://codeforces.com/contest/2236/problem/F1
 *
 * Submissions ~> https://codeforces.com/contest/2236/submission/378995669 By huanhuanonly
 *
 * @b Number-theory ( @a least-common-multiple | @a prime-factorization )
 *
 * ----June 15, 2026 [22h:07m:38s]----
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
[[nodiscard]] std::map<_Tp, int>
prime_factorization_with_exponents(_Tp __n)
{
    std::map<_Tp, int> res;

    for (_Tp i = 2; i * i <= __n; ++i)
    {
        if (__n % i == 0)
        {
            for (auto& c = res[i]; __n % i == 0; __n /= i, ++c);
        }
    }

    if (__n != 1)
    {
        ++res[__n];
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

    int _;
    std::cin >> _;

    while (_--)
    {
        int n, x;
        std::cin >> n >> x;

        std::map<int, int> cnt;

        for (int i = 0, v; i < n; ++i)
        {
            std::cin >> v;

            for (const auto& [key, value] : prime_factorization_with_exponents(v))
            {
                cnt[key] += value;
            }
        }

        const uint64 mod = 1e9 + 7;

        uint64 ans = 1;

        for (const auto& [key, value] : cnt)
        {
            (ans *= value + 1) %= mod;
        }

        std::cout << ans << '\n';
    }

    return 0;
}
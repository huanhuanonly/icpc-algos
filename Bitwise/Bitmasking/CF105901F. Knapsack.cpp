/**
 * 2025 ICPC Wuhan Invitational Contest (The 3rd Universal Cup. Stage 37: Wuhan)
 * 
 * => F. Knapsack
 * 
 * -> https://codeforces.com/gym/105901/problem/F
 * 
 * Submissions ~> https://codeforces.com/gym/105901/submission/369270539 By huanhuanonly
 * 
 * @b Bitmasks
 * 
 * ----April 02, 2026 [01h:34m:47s]----
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
[[nodiscard]] constexpr _Tp binary_exponentiation(_Tp __lhs, _Tp __rhs, _Tp __mod)
{
    auto res = static_cast<_Tp>(1);

    for (__lhs %= __mod; __rhs; __lhs = (__lhs * __lhs) % __mod, __rhs >>= 1)
    {
        if (__rhs & 1)
        {
            res = (res * __lhs) % __mod;
        }
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
        uint64 n, m;
        std::cin >> n >> m;

        constexpr uint64 mod = 998244353;
        constexpr uint64 inf = std::numeric_limits<uint64>::max() / 2;

        std::map<uint64, uint64, std::ranges::greater> map;

        for (uint64 i = 0, a, b; i < n; ++i)
        {
            std::cin >> a >> b;
            map[b] += a;
        }

        uint64 k = 0;
        std::pair<uint64, uint64> cnt{map.begin()->first, 0};

        for (auto it = map.begin(); it != map.end(); ++it)
        {
            if (cnt.second)
            {
                if (cnt.first - it->first >= 63)
                {
                    cnt.second = inf;
                }
                else
                {
                    cnt.second = uint64(std::min(uint128(inf), uint128(cnt.second) * (1ULL << cnt.first - it->first)));
                }
            }

            cnt.first = it->first;

            const auto min = std::min(cnt.second, it->second);

            cnt.second -= min;
            it->second -= min;

            if (it->second)
            {
                const auto rem = it->second % m;
                const auto div = (it->second / m + !!rem) % mod;

                (k += binary_exponentiation(2ULL, it->first, mod) * div % mod) %= mod;

                if (rem)
                {
                    cnt.second += m - rem;
                }
            }
        }

        std::cout << k << '\n';
    }

    return 0;
}
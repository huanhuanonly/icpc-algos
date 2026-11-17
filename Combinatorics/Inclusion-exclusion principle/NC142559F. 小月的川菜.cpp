/**
 * 牛客周赛 Round 168
 *
 * => F-小月的川菜 ( @c 1800 )
 *
 * -> https://ac.nowcoder.com/acm/contest/142559/F
 *
 * Submissions ~> https://ac.nowcoder.com/acm/contest/view-submission?submissionId=85379947 By huanhuanonly
 *
 * @b Combinatorics ( @a inclusion-exclusion-principle )
 *
 * ----November 04, 2026 [00h:31m:30s]----
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

        std::vector<int> v(n);

        for (int i = 0; i < n; ++i)
        {
            std::cin >> v[i];
        }

        std::ranges::sort(v);

        constexpr uint64 mod = 1e9 + 7;

        auto f = [&](auto... excluded_idxs) -> uint64
        {
            static_assert(sizeof...(excluded_idxs) <= 2);

            uint64 sum = std::max(sizeof...(excluded_idxs), 1UZ);

            for (int i = 0, cnt = 0; i < n; ++i)
            {
                if (((i != excluded_idxs) and ...))
                {
                    if (v[i] <= cnt)
                    {
                        return 0;
                    }

                    (sum *= v[i] - cnt) %= mod;
                    ++cnt;
                }
            }

            return sum;
        };

        uint64 sum = 0;

        for (int i = 0; i < n; ++i)
        {
            for (int j = i + 1; j < n; ++j)
            {
                (sum += f(i, j) + mod - f(i) + mod - f(j) + f()) %= mod;
            }
        }

        std::cout << sum << '\n';
    }

    return 0;
}
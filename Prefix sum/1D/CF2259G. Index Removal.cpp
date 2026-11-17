/**
 * Codeforces Round 1119 (Div. 3)
 *
 * => G. Index Removal ( @c 1900 )
 *
 * -> https://codeforces.com/contest/2259/problem/G
 *
 * Submissions ~> https://codeforces.com/contest/2259/submission/389699693 By huanhuanonly
 *
 * @b Prefix-sum
 *
 * ----September 07, 2026 [09h:29m:31s]----
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
        int n, k;
        std::cin >> n >> k;

        std::vector<int64> v(n);

        for (int i = 0; i < n; ++i)
        {
            std::cin >> v[i];
        }

        std::vector<int64> d(n);

        for (int i = 0; i < n - 1; ++i)
        {
            d[i] = v[i] - (v[i + 1] - k);
        }

        std::partial_sum(d.begin(), d.end(), d.begin());

        auto sd = d;
        std::partial_sum(sd.begin(), sd.end(), sd.begin());

        d.back() = sd.back() = std::numeric_limits<int64>::max() / 2;

        std::cout << "0 ";

        for (int i = 1; i < n - 1; ++i)
        {
            int64 x = v[i + 1] - v[i - 1] - k;

            if (x <= 0)
            {
                std::cout << "0 ";
            }
            else
            {
                auto r = std::ranges::lower_bound(d, x + d[i]) - d.begin() - 1;
                std::cout << x * (r - i + 1) - (sd[r] - sd[i]) + (d[i] * (r - i)) << ' ';
            }
        }

        std::cout << "0\n";
    }

    return 0;
}
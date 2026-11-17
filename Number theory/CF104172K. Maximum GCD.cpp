/**
 * The 2023 ICPC Asia Hong Kong Regional Programming Contest (The 1st Universal Cup, Stage 2:Hong Kong)
 *
 * => K. Maximum GCD
 *
 * -> https://codeforces.com/gym/104172/problem/K
 *
 * Submissions ~> https://codeforces.com/gym/104172/submission/389463471 By huanhuanonly
 *
 * @b Number-theory ( @a greatest-common-divisor | @a modular-arithmetic )
 *
 * ----September 05, 2026 [21h:36m:24s]----
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

    std::vector<int> v(n);

    for (int i = 0; i < n; ++i)
    {
        std::cin >> v[i];
    }

    std::ranges::sort(v);

    int max = std::max(*std::ranges::fold_left_first(v, &std::gcd<int, int>), (v.front() + 1) / 2 - 1);
    int gcd = v.front();

    for (int i = 0; i < n - 1; ++i)
    {
        gcd = std::gcd(gcd, v[i]);

        for (int d = 1; d * d <= gcd; ++d)
        {
            if (v[i] % d == 0)
            {
                if ((v[i + 1] + 1) / 2 - 1 >= gcd / d)
                {
                    max = std::max(max, gcd / d);
                    break;
                }

                if ((v[i + 1] + 1) / 2 - 1 >= d)
                {
                    max = std::max(max, d);
                }
            }
        }
    }

    std::cout << max << '\n';

    return 0;
}
/**
 * 2023 (ICPC) Jiangxi Provincial Contest -- Official Contest
 *
 * => C. Battle
 *
 * -> https://codeforces.com/gym/104385/problem/C
 *
 * Submissions ~> https://codeforces.com/gym/104385/submission/387891056 By huanhuanonly
 *
 * @b Game-theory
 * @b Sprague-Grundy-theorem
 *
 * ----August 21, 2026 [21h:27m:23s]----
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

    uint64 n, p;
    std::cin >> n >> p;

    std::vector<uint64> v(n);

    for (auto& i : v)
    {
        std::cin >> i;
    }

    if (p & 1)
    {
        auto sg = [](uint64 n) -> uint64
        {
            return n & 1;
        };

        if (*std::ranges::fold_left_first(v | std::views::transform(sg), std::bit_xor{}))
        {
            std::cout << "GOOD\n";
        }
        else
        {
            std::cout << "BAD\n";
        }
    }
    else
    {
        auto sg = [p](uint64 n) -> uint64
        {
            if (n % (p + 1) % 2 == 0 and (n + 1) % (p + 1) % 2 != 0)
            {
                return 0;
            }
            else if (n >= p and (n - p) % (p + 1) == 0)
            {
                return 2;
            }
            else
            {
                return 1;
            }
        };

        if (*std::ranges::fold_left_first(v | std::views::transform(sg), std::bit_xor{}))
        {
            std::cout << "GOOD\n";
        }
        else
        {
            std::cout << "BAD\n";
        }
    }

    return 0;
}
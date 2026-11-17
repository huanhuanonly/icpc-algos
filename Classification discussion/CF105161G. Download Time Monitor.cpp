/**
 * 2024 Jiangsu Collegiate Programming Contest
 *
 * => G. Download Time Monitor
 *
 * -> https://codeforces.com/gym/105161/problem/G
 *
 * Submissions ~> https://codeforces.com/gym/105161/submission/388992403 By huanhuanonly
 *
 * @b Classification-discussion
 *
 * ----August 31, 2026 [19h:42m:44s]----
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

    std::cout << std::fixed << std::setprecision(12);

    while (_--)
    {
        std::array<int, 5> inputs;

        for (auto& i : inputs)
        {
            std::cin >> i;
        }

        real80 b = inputs[0], t1 = inputs[1], a1 = inputs[2], t2 = inputs[3], a2 = inputs[4];

        if (t1 + a1 / b <= t2)
        {
            std::cout << a1 / b << ' ' << a2 / b << '\n';
        }
        else
        {
            a1 -= (t2 - t1) * b;

            auto t = a1 / (b / 2);

            if (t2 + t <= t2 + a2 / (b / 2))
            {
                a2 -= t * (b / 2);
                std::cout << t2 + t - t1 << ' ' << t + a2 / b << '\n';
            }
            else
            {
                t = a2 / (b / 2);
                a1 -= t * (b / 2);

                std::cout << t2 + t + a1 / b - t1 << ' ' << t << '\n';
            }
        }
    }

    return 0;
}
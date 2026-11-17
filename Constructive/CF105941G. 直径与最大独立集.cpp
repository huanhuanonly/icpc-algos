/**
 * 2025 National Invitational of CCPC (Zhengzhou), 2025 CCPC Henan Provincial Collegiate Programming Contest
 *
 * => G. 直径与最大独立集
 *
 * -> https://codeforces.com/gym/105941/problem/G
 *
 * Submissions ~> https://codeforces.com/gym/105941/submission/391027518 By huanhuanonly
 *
 * @b Constructive
 * @b Trees
 *
 * ----September 17, 2026 [21h:00m:01s]----
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

        if (n == 2)
        {
            std::cout << "1 2\n";
        }
        else if (n == 4)
        {
            std::cout << "-1\n";
        }
        else if (n & 1)
        {
            std::cout << "2 1\n";
            std::cout << "2 3\n";

            for (int i = 4; i <= n; i += 2)
            {
                std::cout << i - 2 << ' ' << i << '\n';
                std::cout << i << ' ' << i + 1 << '\n';
            }
        }
        else
        {
            std::cout << "1 2\n";
            std::cout << "2 3\n";
            std::cout << "1 5\n";
            std::cout << "5 4\n";
            std::cout << "5 6\n";

            for (int i = 7; i <= n; i += 2)
            {
                std::cout << i - 2 << ' ' << i << '\n';
                std::cout << i << ' ' << i + 1 << '\n';
            }
        }
    }

    return 0;
}
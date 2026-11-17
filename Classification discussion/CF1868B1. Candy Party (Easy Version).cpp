/**
 * Codeforces Round 896 (Div. 1)
 *
 * => B1. Candy Party (Easy Version) ( @c 1700 )
 *
 * -> https://codeforces.com/contest/1868/problem/B1
 *
 * Submissions ~> https://codeforces.com/contest/1868/submission/387721644 By huanhuanonly
 *
 * @b Classification-discussion
 *
 * ----August 20, 2026 [02h:36m:59s]----
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

        constexpr int64 maxv = 1e9;

        std::vector<int64> v(n);
        int64 sum = 0;

        for (auto& i : v)
        {
            std::cin >> i;
            sum += i;
        }

        if (sum % n)
        {
            std::cout << "No\n";
            continue;
        }

        sum /= n;

        std::vector<int64> add, sub;

        bool yes = true;

        for (const auto& i : v)
        {
            if (i != sum)
            {
                bool found = false;

                for (int64 x = 1; x <= maxv and not found; x <<= 1)
                {
                    for (int64 y = 1; y <= maxv; y <<= 1)
                    {
                        if (i + x - y == sum)
                        {
                            found = true;

                            add.push_back(x);
                            sub.push_back(y);
                            break;
                        }
                    }
                }

                if (not found)
                {
                    yes = false;
                    break;
                }
            }
        }

        std::ranges::sort(add);
        std::ranges::sort(sub);

        if (yes and add == sub)
        {
            std::cout << "Yes\n";
        }
        else
        {
            std::cout << "No\n";
        }
    }

    return 0;
}
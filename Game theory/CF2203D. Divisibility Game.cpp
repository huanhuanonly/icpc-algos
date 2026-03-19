/**
 * Educational Codeforces Round 187 (Rated for Div. 2)
 * 
 * => D. Divisibility Game ( @c Rating )
 * 
 * -> https://codeforces.com/contest/2203/problem/D
 * 
 * Submissions ~> https://codeforces.com/contest/2203/submission/367298871 By huanhuanonly
 * 
 * @b Game-theory and @b Number-theory ( @a least-common-multiple )
 * 
 * ----March 19, 2026 [11h:10m:20s]----
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
        int n, m;
        std::cin >> n >> m;

        std::vector<int> a(n), b(m);

        std::vector<bool> exist(n + m + 1);

        for (auto& x : a)
        {
            std::cin >> x;
            exist[x] = true;
        }

        for (int i = 1; i <= n + m; ++i)
        {
            if (exist[i])
            {
                for (int j = i; j <= n + m; j += i)
                {
                    exist[j] = true;
                }
            }
        }
        
        for (auto& y : b)
        {
            std::cin >> y;
        }

        uint64 lcm = 1;

        for (const auto& x : a)
        {
            lcm = std::lcm<uint64, uint64>(lcm, x);

            if (lcm > n + m)
            {
                break;
            }
        }

        std::array<int, 3> cnt{};

        for (const auto& y : b)
        {
            if (y % lcm == 0)
            {
                ++cnt[0];
            }
            else
            {
                if (exist[y])
                {
                    ++cnt[2];
                }
                else
                {
                    ++cnt[1];
                }
            }
        }

        if (cnt[0] + (cnt[2] + 1) / 2 > cnt[1] + cnt[2] / 2)
        {
            std::cout << "Alice\n";
        }
        else
        {
            std::cout << "Bob\n";
        }
    }

    return 0;
}
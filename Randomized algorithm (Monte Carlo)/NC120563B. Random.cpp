/**
 * 2026牛客寒假算法基础集训营3
 * 
 * => B-Random ( @c 700 )
 * 
 * -> https://ac.nowcoder.com/acm/contest/120563/B
 * 
 * Submissions ~> https://ac.nowcoder.com/acm/contest/view-submission?submissionId=82119755 By huanhuanonly
 * 
 * @b Randomized-algorithm ( @a Monte-Carlo-algorithm )
 * 
 * ----February 07, 2026 [14h:22m:35s]----
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

        static std::mt19937 rng;

        bool found = false;

        for (int i = 0; i < n and not found; ++i)
        {
            for (int j = 0; j < 100; ++j)
            {
                const int r = rng() % n;

                if (i != r and std::gcd(v[i], v[r]) > 1)
                {
                    found = true;
                    std::cout << v[i] << ' ' << v[r] << '\n';
                    break;
                }
            }
        }

        if (not found)
        {
            std::cout << -1 << '\n';
        }
    }

    return 0;
}
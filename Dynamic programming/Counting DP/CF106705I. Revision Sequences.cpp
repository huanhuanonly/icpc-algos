/**
 * The 2026 ICPC China Guizhou Provincial Contest
 *
 * => I. Revision Sequences
 *
 * -> https://codeforces.com/gym/106705/problem/I
 *
 * Submissions ~> https://codeforces.com/gym/106705/submission/391831391 By huanhuanonly
 *
 * @b Counting-DP
 *
 * ----September 24, 2026 [10h:09m:02s]----
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
        std::string a, b;
        std::cin >> a >> b;

        constexpr uint64 mod = 998244353;

        std::vector f(2, std::vector<int>(b.size() + 1));
        std::vector g(2, std::vector<uint64>(b.size() + 1));

        g[0][0] = 1;

        for (int j = 1; j <= b.size(); ++j)
        {
            f[0][j] = j;
            g[0][j] = 1;
        }

        for (int i = 1; i <= a.size(); ++i)
        {
            f[1][0] = i;
            g[1][0] = 1;

            for (int j = 1; j <= b.size(); ++j)
            {
                f[1][j] = std::min({
                    f[0][j - 1] + (a[i - 1] != b[j - 1]),
                    f[1][j - 1] + 1,
                    f[0][j] + 1
                });

                g[1][j] = 0;

                if (f[0][j - 1] + (a[i - 1] != b[j - 1]) == f[1][j])
                {
                    g[1][j] += g[0][j - 1];
                }

                if (f[1][j - 1] + 1 == f[1][j])
                {
                    g[1][j] += g[1][j - 1];
                }

                if (f[0][j] + 1 == f[1][j])
                {
                    g[1][j] += g[0][j];
                }

                g[1][j] %= mod;
            }

            std::swap(f.front(), f.back());
            std::swap(g.front(), g.back());
        }

        uint64 fact = 1;

        for (int i = 2; i <= f.front().back(); ++i)
        {
            (fact *= i) %= mod;
        }

        std::cout << g.front().back() * fact % mod << '\n';
    }

    return 0;
}
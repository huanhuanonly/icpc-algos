/**
 * 第十二届中国大学生程序设计竞赛 长春站（CCPC 2026 Changchun Site）
 *
 * => J. 送给好友的惊喜
 *
 * -> https://qoj.ac/contest/4582/problem/22919
 *
 * Submissions ~> https://qoj.ac/submission/3398292 By huanhuanonly
 *
 * @b Bitwise-AND
 *
 * ----November 07, 2026 [16h:35m:15s]----
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
        uint64 n, m, k;
        std::cin >> n >> m >> k;

        struct item
        {
            uint64 x, y, z;

            auto operator<=>(const item&) const = default;
        };

        std::vector<uint64> v(n);
        std::vector<item> lims(m);

        for (auto& [x, y, z] : lims)
        {
            std::cin >> x >> y >> z;
            --x, --y;
        }

        std::ranges::sort(lims);

        bool can = true;

        for (int i = 1; i < m; ++i)
        {
            if (lims[i - 1].x == lims[i].x and lims[i - 1].y == lims[i].y and lims[i - 1].z != lims[i].z)
            {
                can = false;
                break;
            }
        }

        for (int b = 0; b < k and can; ++b)
        {
            std::ranges::sort(lims, {}, [b](const item& i) -> bool
            {
                return not (i.z & 1 << b);
            });

            for (const auto& [x, y, z] : lims)
            {
                if (z & 1 << b)
                {
                    v[x] |= 1 << b;
                    v[y] |= 1 << b;
                }
                else if (v[x] & 1 << b and v[y] & 1 << b)
                {
                    can = false;
                    break;
                }
            }
        }

        if (can)
        {
            std::cout << std::reduce(v.begin(), v.end()) << '\n';
        }
        else
        {
            std::cout << "-1\n";
        }
    }

    return 0;
}
/**
 * The 4th Universal Cup. Extra Stage 4: Chongqing
 * 第十一届中国大学生程序设计竞赛 重庆站（CCPC 2025 Chongqing Site）
 *
 * => H. Hot Pot
 *
 * -> https://qoj.ac/contest/3387/problem/15426
 *
 * Submissions ~> https://qoj.ac/submission/3442088 By huanhuanonly
 *
 * @b Classification-discussion
 *
 * ----November 12, 2026 [17h:12m:10s]----
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
        int x, y, z, a, b, c;
        std::cin >> x >> y >> z >> a >> b >> c;

        int ans = std::numeric_limits<int>::max();

        for (int i = 0; ; ++i)
        {
            ans = std::min(
                ans,
                i * b + (x + 1) / 2 * a + (y + 1) / 2 * c + (z - (x & 1) - (y & 1) + 1) / 2 * std::min(a, c));

            if (not (x or y or z))
            {
                break;
            }

            if (--x < 0)
            {
                ++x, --z;
            }

            if (--y < 0)
            {
                ++y, --z;
            }

            z = std::max(z, 0);
        }

        std::cout << ans << '\n';
    }

    return 0;
}
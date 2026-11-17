/**
 * AtCoder Beginner Contest 475
 *
 * => F - Rectangle Filling ( @c 525 )
 *
 * -> https://atcoder.jp/contests/abc475/tasks/abc475_f
 *
 * Submissions ~> https://atcoder.jp/contests/abc475/submissions/79272239 By huanhuanonly
 *
 * @b Prefix-sum
 *
 * ----September 15, 2026 [10h:59m:17s]----
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

    int h, w;
    std::cin >> h >> w;

    std::vector<std::string> map(std::min(h, w) + 1);

    if (h < w)
    {
        for (auto& i : map | std::views::drop(1))
        {
            std::cin >> i;
            i.insert(i.begin(), ' ');
        }
    }
    else
    {
        for (auto& i : map | std::views::drop(1))
        {
            i.resize(h + 1);
        }

        std::string s;

        for (int i = 1; i <= h; ++i)
        {
            std::cin >> s;

            for (int j = 1; j <= w; ++j)
            {
                map[j][i] = s[j - 1];
            }
        }

        std::swap(h, w);
    }

    std::vector pre(h + 1, std::vector<int>(w + 1));

    for (int j = 1; j <= w; ++j)
    {
        for (int i = 1; i <= h; ++i)
        {
            pre[i][j] = pre[i - 1][j] + (map[i][j] == '.');
        }
    }

    uint64 ans = 1;

    for (int il = 1; il <= h; ++il)
    {
        for (int ir = il; ir <= h; ++ir)
        {
            std::vector<int> has(w + 1);

            int last_top = 0, last_bottom = 0;

            for (int r = 1; r <= w; ++r)
            {
                has[r] = has[r - 1] + !!(pre[ir][r] - pre[il - 1][r]);

                if (map[il][r] == '.')
                {
                    last_top = r;
                }
                if (map[ir][r] == '.')
                {
                    last_bottom = r;
                }

                if (has[r] - has[r - 1])
                {
                    ans += has[std::min(last_top, last_bottom)];
                }
            }
        }
    }

    std::cout << ans << '\n';

    return 0;
}
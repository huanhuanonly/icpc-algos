/**
 * 第十二届中国大学生程序设计竞赛 女生专场（CCPC 2026 Women's Division）
 *
 * => E. 可带负权的背包问题
 *
 * -> https://qoj.ac/contest/4613/problem/23635
 *
 * Submissions ~> https://qoj.ac/submission/3346741 By huanhuanonly
 *
 * @b Constructive
 * @b Classification-discussion
 *
 * ----November 02, 2026 [23h:15m:06s]----
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

        std::vector<int64> v(n + 1);

        for (int i = 1; i <= n; ++i)
        {
            std::cin >> v[i];
        }

        std::vector<int64> pre(n + 1);
        std::partial_sum(v.begin(), v.end(), pre.begin());

        int q;
        std::cin >> q;

        while (q--)
        {
            int64 x;
            std::cin >> x;

            std::vector<int> ans(n + 1);

            for (int i = n; i >= 1; --i)
            {
                if (v[i] == x or v[i] == -x)
                {
                    ans[i] = v[i] == x ? +1 : -1;
                    x = 0;
                    break;
                }
                else if (-pre[i - 1] <= x and x <= +pre[i - 1])
                {
                    ans[i] = 0;
                }
                else if (-pre[i - 1] <= x - v[i] and x - v[i] <= +pre[i - 1])
                {
                    ans[i] = +1;
                    x -= v[i];
                }
                else
                {
                    ans[i] = -1;
                    x += v[i];
                }
            }

            if (x)
            {
                std::cout << "NO\n";
            }
            else
            {
                std::cout << "YES\n";

                for (int i = 1; i <= n; ++i)
                {
                    std::cout << ans[i] << " \n"[i == n];
                }
            }
        }
    }

    return 0;
}
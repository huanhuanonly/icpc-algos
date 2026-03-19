/**
 * 2026牛客寒假算法基础集训营1
 * 
 * => D-Sequence Coloring ( @c 2400 )
 * 
 * -> https://ac.nowcoder.com/acm/contest/120561/D
 * 
 * Submissions ~> https://ac.nowcoder.com/acm/contest/view-submission?submissionId=81998032 By huanhuanonly
 * 
 * @b Binary-search
 * 
 * ----February 04, 2026 [17h:38m:28s]----
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
        int n, k;
        std::cin >> n >> k;

        std::vector<int> v(n + 1);
        std::vector<int> cnt(n + 1);

        for (int i = 1; i <= n; ++i)
        {
            std::cin >> v[i];

            if (v[i] == 0)
            {
                cnt[i] = cnt[i - 1] + 1;
            }
        }

        std::vector<int> to(n + 1);

        for (int i = 1; i <= n; ++i)
        {
            to[i] = std::max(to[i - 1], i + v[i] - cnt[i]);
        }

        auto check = [&](int mid) -> bool
        {
            int c = 0;

            for (int cpos = 1; cpos <= n; ++cpos)
            {
                if (v[cpos] == 0)
                {
                    continue;
                }

                ++c;

                for (int i = 0; i < mid and cpos <= n and cpos != to[cpos]; ++i)
                {
                    cpos = to[cpos];
                }
            }

            return c <= k;
        };

        int l = -1, r = n, mid;

        while (r - l > 1)
        {
            mid = l + r >> 1;

            if (check(mid))
            {
                r = mid;
            }
            else
            {
                l = mid;
            }
        }

        if (check(r))
        {
            std::cout << r << '\n';
        }
        else
        {
            std::cout << -1 << '\n';
        }
    }

    return 0;
}
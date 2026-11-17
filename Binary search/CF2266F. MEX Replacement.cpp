/**
 * Codeforces Round 1122 (Div. 3)
 *
 * => F. MEX Replacement ( @c 2000 )
 *
 * -> https://codeforces.com/contest/2266/problem/F
 *
 * Submissions ~> https://codeforces.com/contest/2266/submission/392866537 By huanhuanonly
 *
 * @b Binary-search
 *
 * ----October 02, 2026 [01h:32m:34s]----
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

        std::map<int, int> cnt;
        int64 sum = 0;

        for (int i = 0; i < n; ++i)
        {
            int x, y;
            std::cin >> x >> y;

            cnt[x] += y;
            sum += y;
        }

        auto check = [&](int mid) -> bool
        {
            int64 need = 1;
            int64 cnt0 = cnt[0];

            for (--mid; mid > 0; --mid)
            {
                if (need > cnt[mid])
                {
                    need += need - cnt[mid];
                }
                else
                {
                    cnt0 += cnt[mid] - need;
                }

                if (sum < need)
                {
                    return false;
                }
            }

            return cnt0 >= need;
        };

        int l = cnt.rbegin()->first, r = 1e9 + 1;

        while (r - l > 1)
        {
            const int mid = l + r >> 1;

            if (check(mid))
            {
                l = mid;
            }
            else
            {
                r = mid;
            }
        }

        std::cout << l << '\n';
    }

    return 0;
}
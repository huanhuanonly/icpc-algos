/**
 * Codeforces Round 1134 (Div. 4)
 *
 * => G2. Lakeside Trail (Hard Version) ( @c Rating )
 *
 * -> https://codeforces.com/contest/2290/problem/G2
 *
 * Submissions ~> https://codeforces.com/contest/2290/submission/398354973 By huanhuanonly
 *
 * @b Binary-search
 *
 * ----November 13, 2026 [01h:28m:24s]----
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
        int64 n, k;
        std::cin >> n >> k;

        std::vector<int64> h(n);

        for (int i = 0; i < n; ++i)
        {
            std::cin >> h[i];
        }

        std::ranges::rotate(h, std::ranges::max_element(h));

        auto check = [&](int64 mid) -> bool
        {
            auto t = h;
            int64 cnt = 0;

            for (int i = 1; i < n; ++i)
            {
                if (t[i - 1] - mid > t[i])
                {
                    cnt += t[i - 1] - mid - t[i];
                    t[i] = t[i - 1] - mid;
                }
            }

            for (int i = n - 1; i > 0; --i)
            {
                if (t[(i + 1) % n] - mid > t[i])
                {
                    cnt += t[(i + 1) % n] - mid - t[i];
                    t[i] = t[(i + 1) % n] - mid;
                }
            }

            return cnt <= k;
        };

        int64 l = -1, r = 1e9, mid;

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

        std::cout << r << '\n';
    }

    return 0;
}
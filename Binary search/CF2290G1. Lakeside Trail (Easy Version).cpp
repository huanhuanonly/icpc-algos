/**
 * Codeforces Round 1134 (Div. 4)
 *
 * => G1. Lakeside Trail (Easy Version) ( @c Rating )
 *
 * -> https://codeforces.com/contest/2290/problem/G1
 *
 * Submissions ~> https://codeforces.com/contest/2290/submission/398352864 By huanhuanonly
 *
 * @b Binary-search
 * @b Dijkstra
 *
 * ----November 13, 2026 [01h:08m:08s]----
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

        auto check = [&](int64 mid) -> bool
        {
            auto t = h;

            std::priority_queue<std::pair<int64, int>> que;

            for (int i = 0; i < n; ++i)
            {
                que.emplace(t[i], i);
            }

            int64 cnt = 0;

            while (not que.empty())
            {
                const auto [value, idx] = que.top();
                que.pop();

                if (value != t[idx])
                {
                    continue;
                }

                const int l = idx ? idx - 1 : n - 1;
                const int r = (idx + 1) % n;

                for (const int i : {l, r})
                {
                    if (const int64 need = value - mid; need > t[i])
                    {
                        cnt += need - t[i];
                        t[i] = need;

                        que.emplace(t[i], i);
                    }
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
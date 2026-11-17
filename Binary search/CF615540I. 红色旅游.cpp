/**
 * 2025-2026 国际大学生程序设计竞赛贵州省赛
 *
 * => I. 红色旅游
 *
 * -> https://codeforces.com/gym/615540/problem/I
 *
 * Submissions ~> https://codeforces.com/gym/615540/submission/385455858 By huanhuanonly
 *
 * @b Binary-search
 *
 * ----August 04, 2026 [02h:36m:39s]----
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

        std::vector<std::pair<int64, int64>> v(n);

        for (int i = 0; i < n; ++i)
        {
            std::cin >> v[i].first >> v[i].second;
        }

        std::ranges::sort(v);

        auto check = [&](int64 mid) -> bool
        {
            std::priority_queue<int64, std::vector<int64>, std::ranges::greater> que;

            int64 ctime = 0;
            int64 waiting = 0;

            for (int i = 0; i < n; ++i)
            {
                ctime = std::max(ctime, v[i].first);

                for (; not que.empty() and que.top() < ctime; que.pop());

                if (que.size() >= mid)
                {
                    ctime = que.top() + 1;
                    que.pop();
                }

                waiting = std::max(waiting, ctime - v[i].first);
                que.push(ctime + v[i].second - 1);
            }

            return waiting <= k;
        };

        int64 l = 0, r = n, mid;

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
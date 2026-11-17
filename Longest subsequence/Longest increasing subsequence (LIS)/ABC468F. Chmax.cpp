/**
 * AtCoder Beginner Contest 468
 *
 * => F - Chmax ( @c 500 )
 *
 * -> https://atcoder.jp/contests/abc468/tasks/abc468_f
 *
 * Submissions ~> https://atcoder.jp/contests/abc468/submissions/78495871 By huanhuanonly
 *
 * @b Binary-search for @a longest-increasing-subsequence
 *
 * ----August 18, 2026 [02h:00m:53s]----
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

    int n;
    std::cin >> n;

    std::vector<int> p(n);

    for (int i = 0; i < n; ++i)
    {
        std::cin >> p[i];
    }

    for (int i = 0, max = 0; i < n; ++i)
    {
        if (p[i] > max)
        {
            max = std::exchange(p[i], 0);
        }
    }

    std::erase(p, 0);

    std::vector<int> que;

    for (int i = 0; i < p.size(); ++i)
    {
        if (auto it = std::ranges::upper_bound(que, p[i]); it != que.end())
        {
            *it = p[i];
        }
        else
        {
            que.push_back(p[i]);
        }
    }

    std::cout << n - p.size() + que.size() << '\n';

    return 0;
}
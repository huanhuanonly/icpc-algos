/**
 * Educational DP Contest
 * 
 * => Z - Frog 3 ( @c 100 )
 * 
 * -> https://atcoder.jp/contests/dp/tasks/dp_z
 * 
 * Submissions ~> https://atcoder.jp/contests/dp/submissions/75137764 By huanhuanonly
 * 
 * @b DP with @b Convex-hull-trick
 * @b Monotonic-queue
 * 
 * ----April 21, 2026 [01h:42m:02s]----
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

    int64 n, c;
    std::cin >> n >> c;

    std::vector<int64> h(n + 1);

    for (int i = 1; i <= n; ++i)
    {
        std::cin >> h[i];
    }

    struct point
    {
        int64 x, y;

        point operator-(const point& other) const
        {
            return {x - other.x, y - other.y};
        }

        int64 operator*(const point& other) const
        {
            return x * other.y - y * other.x;
        }
    };

    std::vector<int64> dp(n + 1);
    
    std::deque<point> que{{2 * h[1], h[1] * h[1]}};

    for (int i = 2; i <= n; ++i)
    {
        auto $ = [&](const point& p) -> int64
        {
            return p.y - h[i] * p.x;
        };

        for (; que.size() >= 2 and $(que[0]) > $(que[1]); que.pop_front());

        dp[i] = $(que.front()) + h[i] * h[i] + c;
        
        const point p{2 * h[i], dp[i] + h[i] * h[i]};
        for (; que.size() >= 2 and (p - que.back()) * (que.back() - que[que.size() - 2]) > 0; que.pop_back());
        que.push_back(p);
    }

    std::cout << dp.back() << '\n';

    return 0;
}
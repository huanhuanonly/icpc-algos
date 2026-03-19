/**
 * 2026牛客寒假算法基础集训营4
 * 
 * => D-东风谷早苗与博丽灵梦 ( @c 2000 )
 * 
 * -> https://ac.nowcoder.com/acm/contest/120564/D
 * 
 * Submissions ~> https://ac.nowcoder.com/acm/contest/view-submission?submissionId=82291096 By huanhuanonly
 * 
 * @b Number-theory ( @a Extended-Euclidean-algorithm ) and @b Binary-search
 * 
 * ----February 09, 2026 [17h:59m:47s]----
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

std::pair<int128, int128> extended_euclid(int128 a, int128 b)
{
    if (b == 0)
    {
        return {1, 0};
    }
    else
    {
        const auto [x, y] = extended_euclid(b, a % b);
        return {y, x - a / b * y};
    }
}

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
        int64 n, a, b;
        std::cin >> n >> a >> b;

        const int64 gcd = std::gcd(a, b);

        if (n % gcd)
        {
            std::cout << "No\n";
        }
        else
        {
            auto [x, y] = extended_euclid(a, b);

            a /= gcd;
            b /= gcd;

            x *= n / gcd;
            y *= n / gcd;

            int128 l = -1e18, r = 1e18, mid;

            while (r - l > 1)
            {
                mid = (l + r) / 2;

                if (x + int128(b) * mid > y - int128(a) * mid)
                {
                    r = mid;
                }
                else
                {
                    l = mid;
                }
            }

            std::vector<std::pair<int64, int64>> ans;

            if (x + b * l >= 0 and y - a * l >= 0)
            {
                ans.emplace_back(x + b * l, y - a * l);
            }

            if (x + b * r >= 0 and y - a * r >= 0)
            {
                ans.emplace_back(x + b * r, y - a * r);
            }

            if (ans.empty())
            {
                std::cout << "No\n";
            }
            else if (ans.size() == 1 or std::max(ans.front().first, ans.front().second) <= std::max(ans.back().first, ans.back().second))
            {
                std::cout << "Yes\n";
                std::cout << ans.front().first << ' ' << ans.front().second << '\n';
            }
            else
            {
                std::cout << "Yes\n";
                std::cout << ans.back().first << ' ' << ans.back().second << '\n';
            }
        }
    }

    return 0;
}
/**
 * The 13th Shandong ICPC Provincial Collegiate Programming Contest
 * 
 * => D. Fast and Fat
 * 
 * -> https://codeforces.com/gym/104417/problem/D
 * 
 * Submissions ~> https://codeforces.com/gym/104417/submission/360186126 By huanhuanonly
 * 
 * @b Binary-search
 * 
 * ----January 28, 2026 [00h:37m:17s]----
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

#ifdef __GNUC__
using int128 = __int128;
using uint128 = unsigned __int128;
#endif

using real32 = float;
using real64 = double;
using real128 = long double;

int main(void)
{
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr), std::cout.tie(nullptr);

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

        using item = std::pair<int64, int64>;
        std::vector<item> v(n);

        for (auto& [first, second] : v)
        {
            std::cin >> first >> second;
        }

        auto check = [&](int64 mid) -> bool
        {
            auto $ = [&](const item& value) -> int64
            {
                return value.second + (value.first - mid);
            };

            std::ranges::sort(v, {}, &item::first);

            auto fit = std::ranges::lower_bound(v, mid, {}, &item::first);

            if (std::ranges::distance(fit, v.end()) < std::ranges::distance(v.begin(), fit))
            {
                return false;
            }

            std::ranges::sort(v.begin(), fit, std::ranges::greater{}, &item::second);
            std::ranges::sort(fit, v.end(), std::ranges::greater{}, $);

            for (auto it1 = v.begin(), it2 = fit; it1 != fit; ++it1, ++it2)
            {
                if ($(*it2) < it1->second)
                {
                    return false;
                }
            }

            return true;
        };
        
        std::cout << *std::ranges::lower_bound(std::views::iota(int64(1), int64(1e9 + 1)) | std::views::reverse, true, {}, check) << '\n';
    }

    return 0;
}
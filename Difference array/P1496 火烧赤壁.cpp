/**
 * => P1496 火烧赤壁 ( @c 普及− )
 * 
 * -> https://www.luogu.com.cn/problem/P1496
 * 
 * Submissions ~> https://www.luogu.com.cn/record/268144793 By huanhuanonly
 * 
 * @b Difference-array
 * 
 * ----March 19, 2026 [16h:52m:57s]----
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

    int64 n;
    std::cin >> n;

    std::map<int64, int64> map;

    for (int64 i = 0, x, y; i < n; ++i)
    {
        std::cin >> x >> y;

        ++map[x];
        --map[y];
    }

    const auto view = map | std::views::values;
    std::partial_sum(view.begin(), view.end(), view.begin());

    int64 sum = 0;

    for (auto pit = map.begin(), nit = std::next(pit); nit != map.end(); ++pit, ++nit)
    {
        sum += (nit->first - pit->first) * !!pit->second;
    }

    std::cout << sum << '\n';

    return 0;
}
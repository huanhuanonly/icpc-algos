/**
 * => P1020 [NOIP 1999 提高组] 导弹拦截 ( @c 普及+/提高 )
 *
 * -> https://www.luogu.com.cn/problem/P1020
 *
 * Submissions ~> https://www.luogu.com.cn/record/228044298 By huanhuanonly
 *
 * @b Binary-search for @a longest-non-increasing-subsequence
 * @b Dilworth's-theorem
 *
 * ----July 31, 2025 [18h:17m:12s]----
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

    std::vector<int> v;
    for (int a; std::cin >> a; v.push_back(a));

    std::vector<int> q;

    for (int i = 0; i < v.size(); ++i)
    {
        if (auto it = std::ranges::upper_bound(q, v[i], std::ranges::greater()); it != q.end())
        {
            *it = v[i];
        }
        else
        {
            q.push_back(v[i]);
        }
    }

    std::cout << q.size() << '\n';

    q.clear();

    for (int i = 0; i < v.size(); ++i)
    {
        if (auto it = std::ranges::lower_bound(q, v[i]); it != q.end())
        {
            *it = v[i];
        }
        else
        {
            q.push_back(v[i]);
        }
    }

    std::cout << q.size() << '\n';

    return 0;
}
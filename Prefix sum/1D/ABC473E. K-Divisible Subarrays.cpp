/**
 * AtCoder Beginner Contest 473
 *
 * => E - K-Divisible Subarrays ( @c 450 )
 *
 * -> https://atcoder.jp/contests/abc473/tasks/abc473_e
 *
 * Submissions ~> https://atcoder.jp/contests/abc473/submissions/78857595 By huanhuanonly
 *
 * @b Prefix-sum
 *
 * ----August 31, 2026 [10h:59m:12s]----
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

    int n, k;
    std::cin >> n >> k;

    std::vector<int> v(n + 1);

    for (int i = 1; i <= n; ++i)
    {
        std::cin >> v[i];
        (v[i] += v[i - 1]) %= k;
    }

    std::set<int> set{0};
    int cnt = 0;

    for (int i = 1; i <= n; ++i)
    {
        if (set.contains(v[i]))
        {
            ++cnt;
            set.clear();
        }

        set.insert(v[i]);
    }

    std::cout << cnt << '\n';

    return 0;
}
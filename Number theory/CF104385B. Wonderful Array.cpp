/**
 * 2023 (ICPC) Jiangxi Provincial Contest -- Official Contest
 *
 * => B. Wonderful Array
 *
 * -> https://codeforces.com/gym/104385/problem/B
 *
 * Submissions ~> https://codeforces.com/gym/104385/submission/387739510 By huanhuanonly
 *
 * @b Number-theory ( @a modular-arithmetic )
 *
 * ----August 20, 2026 [09h:34m:45s]----
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

    int k;
    std::cin >> k;

    std::vector<int64> v(k);

    for (auto& i : v)
    {
        std::cin >> i;
    }

    int64 n, m, x;
    std::cin >> n >> m >> x;

    x %= m;

    for (auto& i : v)
    {
        i %= m;
    }

    const int64 bn = x + std::reduce(v.begin(), v.end()) * (n / k) + std::reduce(v.begin(), v.begin() + n % k);

    std::cout << n - (bn / m - x / m) << '\n';

    return 0;
}
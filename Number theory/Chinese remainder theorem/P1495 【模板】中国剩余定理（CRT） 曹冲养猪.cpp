/**
 * => P1495 【模板】中国剩余定理（CRT）/ 曹冲养猪 ( @c 提高+/省选− )
 *
 * -> https://www.luogu.com.cn/problem/P1495
 *
 * Submissions ~> https://www.luogu.com.cn/record/220367714 By huanhuanonly
 *
 * @b Chinese-remainder-theorem
 *
 * @see https://zh.wikipedia.org/wiki/%E4%B8%AD%E5%9B%BD%E5%89%A9%E4%BD%99%E5%AE%9A%E7%90%86
 *
 * ----June 13, 2025 [22h:09m:54s]----
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

uint64 ext_euclid(uint64 a, uint64 b, int64 &x, int64 &y)
{
    if (b == 0)
    {
        x = 1, y = 0;
        return a;
    }

    uint64 d = ext_euclid(b, a % b, y, x);
    y -= a / b * x;

    return d;
}

uint64 inverse(uint64 val, uint64 mod)
{
    int64 x, y;
    ext_euclid(val, mod, x, y);
    return (x + mod) % mod;
}

int main(void)
{
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr), std::cout.tie(nullptr);

#ifdef __huanhuanonly_localhost
    ::freopen("in", "r", stdin);
    ::freopen("out", "w", stdout);
#endif

    int n;
    std::cin >> n;

    struct item
    {
        uint64 val, mod;
    };

    std::vector<item> v(n);

    uint64 mul = 1;

    for (int i = 0; i < n; ++i)
    {
        std::cin >> v[i].mod >> v[i].val;
        mul *= v[i].mod;
    }

    uint64 ans = 0;

    for (int i = 0; i < n; ++i)
    {
        ans += static_cast<uint128>(1) * v[i].val * (mul / v[i].mod) * inverse(mul / v[i].mod, v[i].mod) % mul;
        ans %= mul;
    }

    std::cout << ans;

    return 0;
}
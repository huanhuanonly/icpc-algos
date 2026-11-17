/**
 * KEYENCE Programming Contest 2023 Summer（AtCoder Beginner Contest 315）
 *
 * => G - Ai + Bj + Ck = X (1 <= i, j, k <= N) ( @c 550 )
 *
 * -> https://atcoder.jp/contests/abc315/tasks/abc315_g
 *
 * Submissions ~> https://atcoder.jp/contests/abc315/submissions/76346531 By huanhuanonly
 *
 * @b Number-theory ( @a Extended-Euclidean-algorithm )
 *
 * ----June 02, 2026 [16h:36m:35s]----
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

inline namespace huanhuanonly {
    inline namespace math
{
template<typename _Tp>
constexpr _Tp exgcd(_Tp __a, _Tp& __x, _Tp __b, _Tp& __y)
{
    if (__b)
    {
        _Tp nx, ny;
        const _Tp gcd = exgcd(__b, nx, __a % __b, ny);

        __x = ny;
        __y = nx - __a / __b * ny;

        return gcd;
    }
    else
    {
        __x = 1, __y = 0;
        return __a;
    }
}
}} // namespace huanhuanonly::math

constexpr int128 div_floor(int128 lhs, int128 rhs)
{
    return lhs / rhs - ((lhs ^ rhs) < 0 and lhs % rhs);
}

constexpr int128 div_ceil(int128 lhs, int128 rhs)
{
    return lhs / rhs + ((lhs ^ rhs) >= 0 and lhs % rhs);
}

int main(void)
{
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);

#ifdef __huanhuanonly_localhost
    ::freopen("in", "r", stdin);
    ::freopen("out", "w", stdout);
#endif

    int64 n, a, b, c, x;
    std::cin >> n >> a >> b >> c >> x;

    const int128 d = std::gcd(a, b);

    int64 cnt = 0;

    for (int128 k = 1; k <= n and c * k <= x; ++k)
    {
        const int128 y = x - c * k;

        if (y % d)
        {
            continue;
        }

        int128 i, j;
        exgcd(a / d, i, b / d, j);

        i *= y / d;
        j *= y / d;

        const auto p = b / d;
        const auto q = a / d;

        const auto l = std::max(div_ceil(1 - i, p), div_ceil(j - n, q));
        const auto r = std::min(div_floor(n - i, p), div_floor(j - 1, q));

        if (l <= r)
        {
            cnt += r - l + 1;
        }
    }

    std::cout << cnt << '\n';

    return 0;
}
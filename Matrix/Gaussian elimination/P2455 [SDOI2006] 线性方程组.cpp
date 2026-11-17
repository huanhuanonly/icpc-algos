/**
 * => P2455 [SDOI2006] 线性方程组.cpp ( @c 提高+/省选− )
 *
 * -> https://www.luogu.com.cn/problem/P2455
 *
 * Submissions ~> https://www.luogu.com.cn/record/275056461 By huanhuanonly
 *
 * @b Gaussian-elimination
 *
 * ----April 22, 2026 [10h:09m:51s]----
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

    std::vector v(n, std::vector<real80>(n + 1));

    for (int i = 0; i < n; ++i)
    {
        for (int k = 0; k < n + 1; ++k)
        {
            std::cin >> v[i][k];
        }
    }

    constexpr real80 eps = 1e-12;

    int cur = 0;

    for (int k = 0; k < n; ++k)
    {
        int mxid = cur;
        for (int i = cur + 1; i < n; ++i)
        {
            if (std::abs(v[i][k]) > std::abs(v[mxid][k]))
            {
                mxid = i;
            }
        }

        std::swap(v[cur], v[mxid]);

        if (std::abs(v[cur][k]) < eps)
        {
            continue;
        }

        for (auto [i, div] = std::tuple(0, v[cur][k]); i < n + 1; ++i)
        {
            v[k][i] /= div;
        }

        for (int i = 0; i < n; ++i)
        {
            if (i == cur)
            {
                continue;
            }

            const auto x = v[i][k];

            for (int j = cur; j < n + 1; ++j)
            {
                v[i][j] -= v[cur][j] * x;
            }
        }

        ++cur;
    }

    if (cur < n)
    {
        bool found = false;

        for (; cur < n; ++cur)
        {
            if (std::abs(v[cur].back()) > eps)
            {
                found = true;
                break;
            }
        }

        if (found)
        {
            std::cout << "-1\n";
        }
        else
        {
            std::cout << "0\n";
        }
    }
    else
    {
        std::cout << std::fixed << std::setprecision(12);

        for (int i = 0; i < n; ++i)
        {
            std::cout << 'x' << i + 1 << '=' << v[i].back() << '\n';
        }
    }

    return 0;
}
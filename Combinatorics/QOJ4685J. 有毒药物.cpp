/**
 * 第十二届中国大学生程序设计竞赛 乐山站（CCPC 2026 Leshan Site）
 *
 * => J. 有毒药物
 *
 * -> https://qoj.ac/contest/4685/problem/24850
 *
 * Submissions ~> https://qoj.ac/submission/3424113 By huanhuanonly
 *
 * @b Combinatorics
 *
 * ----November 10, 2026 [18h:37m:42s]----
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

    const int maxk = 2e5;

    std::vector<std::vector<int>> C(maxk + 1);
    C.front().push_back(1);

    for (int i = 1; i <= maxk; ++i)
    {
        C[i].resize(C[i - 1].size() + 1);
        C[i][0] = 1;

        if (i < C[i].size())
        {
            C[i][i] = 1;
        }

        for (int j = 1; j < i; ++j)
        {
            if (j >= C[i - 1].size())
            {
                C[i].resize(j);
                break;
            }

            C[i][j] = C[i - 1][j] + C[i - 1][j - 1];

            if (C[i][j] >= maxk)
            {
                C[i].resize(j);
                break;
            }
        }
    }

    auto comb = [&](int n, int k) -> int
    {
        if (k > n)
        {
            return 0;
        }

        if (n - k < k)
        {
            k = n - k;
        }

        if (k < C[n].size())
        {
            return C[n][k];
        }
        else
        {
            return maxk;
        }
    };

    int _;
    std::cin >> _;

    while (_--)
    {
        int k;
        std::cin >> k;

        std::vector<int> v(k);

        for (int i = 0; i < k; ++i)
        {
            std::cin >> v[i];
        }

        std::ranges::sort(v);

        if (k >= 2 and v[1] == 0)
        {
            std::cout << "-1\n";
            continue;
        }

        auto check = [&](int mid) -> bool
        {
            for (int i = 1, c = 1; i < k; i += comb(mid, c), ++c)
            {
                if (v[i] < c or comb(mid, c) == 0)
                {
                    return false;
                }
            }

            return true;
        };

        int l = -1, r = k, mid;

        while (r - l > 1)
        {
            mid = l + r >> 1;

            if (check(mid))
            {
                r = mid;
            }
            else
            {
                l = mid;
            }
        }

        std::cout << r << '\n';
    }

    return 0;
}
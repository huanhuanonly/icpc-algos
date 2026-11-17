/**
 * Codeforces Round 1024 (Div. 2)
 *
 * => C. Mex in the Grid ( @c 1300 )
 *
 * -> https://codeforces.com/contest/2102/problem/C
 *
 * Submissions ~> https://codeforces.com/contest/2102/submission/319478286 By huanhuanonly
 *
 * @b Implementation ( @a draw-map )
 *
 * ----May 13, 2025 [17h:36m:39s]----
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

        if (n == 1)
        {
            std::cout << "0\n";
            continue;
        }

        std::vector<std::vector<int>> v(n, std::vector<int>(n, -1));

        int m = (n - 1) / 2;

        int id = 0;

        v[m][m] = 0;

        for (int k = 1; m + k < n; ++k)
        {
            for (int i = m - k + 1; i < m + k; ++i)
            {
                v[i][m + k] = ++id;
            }

            for (int i = m - k + 1; i <= m + k; ++i)
            {
                v[m + k][i] = ++id;
            }

            if (m - k >= 0)
            {
                for (int i = m - k + 1; i <= m + k; ++i)
                {
                    v[i][m - k] = ++id;
                }

                for (int i = m - k; i <= m + k; ++i)
                {
                    v[m - k][i] = ++id;
                }
            }
        }

        for (int i = 0; i < n; ++i)
        {
            for (int j = 0; j < n; ++j)
            {
                std::cout << v[i][j] << " \n"[j + 1 == n];
            }
        }
    }

    return 0;
}
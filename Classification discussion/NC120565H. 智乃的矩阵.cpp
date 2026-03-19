/**
 * 2026牛客寒假算法基础集训营5
 * 
 * => H-智乃的矩阵 ( @c 2100 )
 * 
 * -> https://ac.nowcoder.com/acm/contest/120565/H
 * 
 * Submissions ~> https://ac.nowcoder.com/acm/contest/view-submission?submissionId=82678745 By huanhuanonly
 * 
 * @b Classification-discussion
 * 
 * ----March 09, 2026 [15h:01m:39s]----
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

    do
    {
        int64 n;
        std::cin >> n;
    
        std::vector v(n, std::vector(n, int64{}));
    
        int64 sum = 0;
    
        for (int64 i = 0; i < n; ++i)
        {
            for (int64 j = 0; j < n; ++j)
            {
                std::cin >> v[i][j];
                sum += v[i][j];
            }
        }
    
        const int64 avg = sum / (n * n);
    
        if (sum != avg * (n * n))
        {
            std::cout << "No\n";
            break;
        }

        for (int64 i = 0; i < n; ++i)
        {
            for (int64 j = 0; j < n; ++j)
            {
                v[i][j] -= avg;
            }
        }

        bool yes = true;

        for (int64 i = 0; i < n; ++i)
        {
            if (std::reduce(v[i].begin(), v[i].end()) & 1)
            {
                yes = false;
                break;
            }
        }

        for (int64 j = 0; j < n; ++j)
        {
            int64 s = 0;

            for (int64 i = 0; i < n; ++i)
            {
                s += v[i][j];
            }

            if (s & 1)
            {
                yes = false;
                break;
            }
        }

        int64 sumx = 0;

        for (int i = 0; i < n; ++i)
        {
            for (int j = i & 1; j < n; j += 2)
            {
                sumx += v[i][j];
            }
        }

        yes = yes and sumx == 0;

        if (yes and n == 2)
        {
            v[1][0] += v[0][1] / 2 * 2;
            v[0][1] %= 2;

            v[1][1] += v[0][0] / 2 * 2;
            v[0][0] %= 2;

            if (v[0][0])
            {
                if (v[0][0] == v[0][1])
                {
                    v[1][0] += std::exchange(v[0][0], 0);
                    v[1][1] += std::exchange(v[0][1], 0);
                }
                else if (v[0][0] == v[1][0])
                {
                    v[0][1] += std::exchange(v[0][0], 0);
                    v[1][1] += std::exchange(v[1][0], 0);
                }
            }

            if (v[0][0] or v[0][1] or v[1][0] or v[1][1])
            {
                yes = false;
            }
        }

        if (yes)
        {
            std::cout << "Yes\n";
        }
        else
        {
            std::cout << "No\n";
        }

    } while (false);

    return 0;
}
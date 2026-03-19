/**
 * Codeforces Round 1071 (Div. 3)
 * 
 * => E. Blackslex and Girls ( @c 1800 )
 * 
 * -> https://codeforces.com/contest/2179/problem/E
 * 
 * Submissions ~> https://codeforces.com/contest/2179/submission/354829794 By huanhuanonly
 * 
 * @b Classification-discussion
 * 
 * ----December 24, 2025 [00h:47m:49s]----
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
        int64 n, x, y;
        std::cin >> n >> x >> y;

        std::string s;
        std::cin >> s;

        std::vector<int64> p(n);

        for (int64& i : p)
        {
            std::cin >> i;
        }

        std::vector<int64> a(n), b(n);

        int64 sa = 0, sb = 0;

        for (int64 i = 0; i < n; ++i)
        {
            if (s[i] == '0')
            {
                a[i] = p[i];
            }
            else
            {
                b[i] = p[i];
            }

            sa += a[i];
            sb += b[i];
        }

        if (sa > x or sb > y)
        {
            for (int64 i = 0; i < n; ++i)
            {
                if (s[i] == '0')
                {
                    if (const int64 t = std::min({sa - x, (a[i] - b[i] - 1) / 2, y - sb}); t > 0)
                    {
                        a[i] -= t;
                        b[i] += t;
    
                        sa -= t;
                        sb += t;
                    }
                }
                else
                {
                    if (const int64 t = std::min({sb - y, (b[i] - a[i] - 1) / 2, x - sa}); t > 0)
                    {
                        b[i] -= t;
                        a[i] += t;
    
                        sb -= t;
                        sa += t;
                    }
                }
            }
        }

        if (sa <= x and sb <= y)
        {
            const int64 t = std::min(x - sa, y - sb);

            a[0] += t;
            b[0] += t;

            sa += t;
            sb += t;

            for (int64 i = 0; i < n; ++i)
            {
                if (s[i] == '0')
                {
                    if (sa < x)
                    {
                        a[i] += x - sa;
                        sa = x;
                    }
    
                    if (sb < y)
                    {
                        const int64 t = std::min(y - sb, a[i] - b[i] - 1);
                        b[i] += t;
                        sb += t;
                    }
                }
                else
                {
                    if (sb < y)
                    {
                        b[i] += y - sb;
                        sb = y;
                    }
    
                    if (sa < x)
                    {
                        const int64 t = std::min(x - sa, b[i] - a[i] - 1);
                        a[i] += t;
                        sa += t;
                    }
                }
            }
        }

        if (sa == x and sb == y)
        {
            std::cout << "YES\n";
        }
        else
        {
            std::cout << "NO\n";
        }
    }

    return 0;
}
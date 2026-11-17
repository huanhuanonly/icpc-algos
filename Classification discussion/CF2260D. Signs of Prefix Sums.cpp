/**
 * Educational Codeforces Round 194 (Rated for Div. 2)
 *
 * => D. Signs of Prefix Sums ( @c 1700 )
 *
 * -> https://codeforces.com/contest/2260/problem/D
 *
 * Submissions ~> https://codeforces.com/contest/2260/submission/389939500 By huanhuanonly
 *
 * @b Classification-discussion
 *
 * ----September 09, 2026 [00h:06m:36s]----
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

    int _;
    std::cin >> _;

    while (_--)
    {
        int n;
        std::cin >> n;

        std::string s;
        std::cin >> s;

        if (s.front() == '0' or s.contains("00"))
        {
            std::cout << "-1\n";
            continue;
        }

        if (s.contains("+--+") or s.contains("-++-"))
        {
            std::cout << "3\n";
            continue;
        }

        std::vector<int> v(n);

        if (s.front() == '+')
        {
            v.front() = 1;
        }
        else
        {
            v.front() = -1;
        }

        for (int i = 1; i < n; ++i)
        {
            if (s[i] == '+')
            {
                if (v[i - 1] == 2)
                {
                    v[i] = 1;
                }
                else if (v[i - 1] >= 0)
                {
                    v[i] = v[i - 1] + 1;
                }
                else
                {
                    v[i] = 1;
                }
            }
            else if (s[i] == '-')
            {
                if (v[i - 1] == -2)
                {
                    v[i] = -1;
                }
                else if (v[i - 1] >= 0)
                {
                    v[i] = -1;
                }
                else
                {
                    v[i] = v[i - 1] - 1;
                }
            }
        }

        int max = std::abs(v.front());

        for (int i = 1; i < n; ++i)
        {
            max = std::max(max, std::abs(v[i] - v[i - 1]));
        }

        std::cout << std::min(max, 2) << '\n';
    }

    return 0;
}
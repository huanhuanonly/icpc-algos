/**
 * Codeforces Round 1119 (Div. 3)
 *
 * => D. MEX Multiset ( @c 1200 )
 *
 * -> https://codeforces.com/contest/2259/problem/D
 *
 * Submissions ~> https://codeforces.com/contest/2259/submission/389519007 By huanhuanonly
 *
 * @b Classification-discussion
 *
 * ----September 05, 2026 [23h:28m:13s]----
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

        std::map<int, std::vector<int>> map;

        for (int i = 0, v; i < n; ++i)
        {
            std::cin >> v;
            map[v].push_back(i);
        }

        std::string s(n, ' ');

        bool yes = true;

        for (int mex = 0; const auto& [v, ids] : map)
        {
            if (v != mex)
            {
                for (auto& c : s)
                {
                    if (c == ' ')
                    {
                        c = 'A';
                    }
                }

                break;
            }

            if (ids.size() == 1)
            {
                if ((mex + 1) + mex * 2 >= (mex + 1) * 2)
                {
                    s[ids[0]] = 'A';

                    for (auto& c : s)
                    {
                        if (c == ' ')
                        {
                            c = 'B';
                        }
                    }
                }
                else
                {
                    yes = false;
                }

                break;
            }
            else if (ids.size() == 2)
            {
                s[ids[0]] = 'A';
                s[ids[1]] = 'B';

                for (auto& c : s)
                {
                    if (c == ' ')
                    {
                        c = 'C';
                    }
                }

                break;
            }
            else if (ids.size() >= 3)
            {
                s[ids[0]] = 'A';
                s[ids[1]] = 'B';
                s[ids[2]] = 'C';

                for (const auto& i : ids | std::views::drop(3))
                {
                    s[i] = 'A';
                }
            }

            ++mex;
        }

        if (yes)
        {
            std::cout << "YES\n";
            std::cout << s << '\n';
        }
        else
        {
            std::cout << "NO\n";
        }
    }

    return 0;
}
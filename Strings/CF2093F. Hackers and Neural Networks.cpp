/**
 * Codeforces Round 1016 (Div. 3)
 *
 * => F. Hackers and Neural Networks ( @c 1800 )
 *
 * -> https://codeforces.com/contest/2093/problem/F
 *
 * Submissions ~> https://codeforces.com/contest/2093/submission/314970853 By huanhuanonly
 *
 * @b Standard-library-string-hash
 *
 * ----April 11, 2025 [15h:34m:51s]----
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

#ifdef __localhost
    ::freopen("in", "r", stdin);
    ::freopen("out", "w", stdout);
#endif

    int _;
    std::cin >> _;

    while (_--)
    {
        int n, m;
        std::cin >> n >> m;

        std::string s;

        std::vector<std::hash<std::string>::result_type> v(n);
        std::vector<bool> vis(n);

        for (int i = 0; i < n; ++i)
        {
            std::cin >> s;
            v[i] = std::hash<std::string>{}(s);
        }

        int max = 0;

        for (int i = 0; i < m; ++i)
        {
            int cnt = 0;

            for (int j = 0; j < n; ++j)
            {
                std::cin >> s;

                if (v[j] == std::hash<std::string>{}(s))
                {
                    vis[j] = true;
                    ++cnt;
                }
            }

            max = std::max(max, cnt);
        }

        if (std::find(vis.begin(), vis.end(), false) != vis.end())
            std::cout << -1 << '\n';
        else
            std::cout << n + (n - max) * 2 << '\n';
    }

    return 0;
}
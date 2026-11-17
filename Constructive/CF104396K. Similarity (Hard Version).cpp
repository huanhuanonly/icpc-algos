/**
 * 2023 Jiangsu Collegiate Programming Contest, 2023 National Invitational of CCPC (Hunan), The 13th Xiangtan Collegiate Programming Contest
 *
 * => K. Similarity (Hard Version)
 *
 * -> https://codeforces.com/gym/104396/problem/K
 *
 * Submissions ~> https://codeforces.com/gym/104396/submission/389777132 By huanhuanonly
 *
 * @b Constructive
 *
 * ----September 08, 2026 [01h:15m:12s]----
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
        int n, m, k;
        std::cin >> n >> m >> k;

        if (m == 0)
        {
            if (n <= 26)
            {
                std::cout << "Yes\n";

                for (int i = 0; i < n; ++i)
                {
                    std::cout << std::string(k, 'a' + i) << '\n';
                }
            }
            else
            {
                std::cout << "No\n";
            }

            break;
        }

        if (m >= k)
        {
            std::cout << "No\n";
            break;
        }

        static auto repeat = [&](const std::string& s, int n) -> std::string
        {
            std::string res;
            res.reserve(s.size() * n);
            for (; n--; res.append(s));
            return res;
        };

        std::vector<std::string> map;
        std::string s(2, ' ');

        for (char ci = 'a'; ci <= 'z' and map.size() < n; ++ci)
        {
            for (char cj = ci; cj <= 'z' and map.size() < n; ++cj)
            {
                s[0] = ci, s[1] = cj;
                map.push_back(repeat(s, (k + 1) / 2));
            }
        }

        map[1].replace(0, m, map[0].substr(0, m));

        if (m != k and map[0][m] == map[1][m])
        {
            map[1].erase(map[1].begin() + m);

            if (map[1].back() == 'a')
            {
                map[1].push_back('b');
            }
            else
            {
                map[1].push_back('a');
            }
        }

        std::cout << "Yes\n";

        for (int i = 0; i < n; ++i)
        {
            map[i].resize(k);
            std::cout << map[i] << '\n';
        }
    } while (false);

    return 0;
}
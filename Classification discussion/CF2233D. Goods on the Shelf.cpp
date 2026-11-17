/**
 * Educational Codeforces Round 191 (Rated for Div. 2)
 *
 * => D. Goods on the Shelf ( @c 1900 )
 *
 * -> https://codeforces.com/contest/2233/problem/D
 *
 * Submissions ~> https://codeforces.com/contest/2233/submission/377986801 By huanhuanonly
 *
 * @b Classification-discussion
 *
 * ----June 10, 2026 [00h:17m:33s]----
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

        std::vector<int> v(n);

        std::map<int, std::vector<int>> pos;

        for (int i = 0; i < n; ++i)
        {
            std::cin >> v[i];
            pos[v[i]].push_back(i);
        }

        auto check = [&](int ia, int ib) -> bool
        {
            if (not (0 <= ib and ib < n))
            {
                return false;
            }

            std::swap(v[ia], v[ib]);

            std::map<int, int> last;

            bool yes = true;

            for (int i = 0; i < n; ++i)
            {
                if (auto it = last.find(v[i]); it != last.end())
                {
                    if (it->second + 1 != i)
                    {
                        yes = false;
                        break;
                    }

                    it->second = i;
                }
                else
                {
                    last[v[i]] = i;
                }
            }

            std::swap(v[ia], v[ib]);
            return yes;
        };

        bool yes = true;

        for (const auto& [key, value] : pos)
        {
            std::vector<std::pair<int, int>> que{{value.front(), value.front()}};

            for (int i = 1; i < value.size(); ++i)
            {
                if (value[i - 1] + 1 == value[i])
                {
                    que.back().second = value[i];
                }
                else
                {
                    que.emplace_back(value[i], value[i]);
                }
            }

            static auto len = [](const std::pair<int, int>& p) -> int
            {
                return p.second - p.first + 1;
            };

            if (que.size() == 1)
            {
                continue;
            }
            else if (que.size() == 2)
            {
                if (len(que.front()) == 1)
                {
                    if (check(que.front().first, que.back().first - 1) or
                        check(que.front().first, que.back().second + 1))
                    {
                        break;
                    }
                }

                if (len(que.back()) == 1)
                {
                    if (check(que.back().first, que.front().first - 1) or
                        check(que.back().first, que.front().second + 1))
                    {
                        break;
                    }
                }

                if (que.front().second + 2 == que.back().first)
                {
                    if (check(que.front().first, que.back().first - 1) or
                        check(que.back().second, que.front().second + 1))
                    {
                        break;
                    }
                }
            }
            else if (que.size() == 3)
            {
                if (len(que[0]) == 1)
                {
                    if (check(que[0].first, que[1].second + 1))
                    {
                        break;
                    }
                }

                if (len(que[2]) == 1)
                {
                    if (check(que[2].first, que[0].second + 1))
                    {
                        break;
                    }
                }
            }

            yes = false;
            break;
        }

        if (yes)
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
/**
 * 2025 ICPC Asia Taichung Regional Contest (Unrated, Online Mirror, ICPC Rules, Preferably Teams)
 * 
 * => K. Kindergarten Homework ( @c 2100 )
 * 
 * -> https://codeforces.com/contest/2172/problem/K
 * 
 * Submissions ~> https://codeforces.com/contest/2172/submission/361171330 By huanhuanonly
 * 
 * @b Implementation
 * 
 * ----February 03, 2026 [00h:43m:56s]----
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

    int n, m, q;
    std::cin >> n >> m >> q;

    std::vector<std::string> map(n);

    for (std::string& i : map)
    {
        std::cin >> i;
    }

    constexpr uint64 maxv = 1e6;

    std::vector<uint64> ans(maxv);

    constexpr std::pair<int, int> d[]{
        {0, 1}, {1, 0}, {0, -1}, {-1, 0},
        {1, 1}, {-1, -1}, {1, -1}, {-1, 1}
    };

    for (int i = 0; i < n; ++i)
    {
        for (int j = 0; j < m; ++j)
        {
            if (not std::isdigit(map[i][j]))
            {
                continue;
            }

            ++ans[map[i][j] - '0'];

            for (const auto& [dx, dy] : d)
            {
                std::vector<uint64> list{static_cast<uint64>(map[i][j] - '0')};
                uint64 sum = list.back();

                char op = '+';

                for (int x = i + dx, y = j + dy; 0 <= x and x < n and 0 <= y and y < m; x += dx, y += dy)
                {
                    if (std::isdigit(map[x][y]))
                    {
                        if (op == '+')
                        {
                            sum -= list.back();
                            list.back() = list.back() * 10 + map[x][y] - '0';
                            sum += list.back();
                        }
                        else
                        {
                            sum -= std::max(list.back(), 1ULL) * list[list.size() - 2];
                            list.back() = list.back() * 10 + map[x][y] - '0';
                            sum += list.back() * list[list.size() - 2];
                        }

                        if (sum <= maxv)
                        {
                            ++ans[sum];
                        }
                        else
                        {
                            break;
                        }
                    }
                    else
                    {
                        if (not std::isdigit(map[x - dx][y - dy]))
                        {
                            break;
                        }

                        if (op == '*')
                        {
                            list[list.size() - 2] *= list.back();
                            list.pop_back();
                        }

                        op = map[x][y];
                        list.emplace_back();
                    }
                }
            }
        }
    }
    
    while (q--)
    {
        uint64 a;
        std::cin >> a;

        std::cout << ans[a] << '\n';
    }

    return 0;
}
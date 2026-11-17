/**
 * The 2024 ICPC Asia Nanjing Regional Contest (The 3rd Universal Cup. Stage 16: Nanjing)
 *
 * => J. Social Media
 *
 * -> https://codeforces.com/gym/105484/problem/J
 *
 * Submissions ~> https://codeforces.com/gym/105484/submission/389089584 By huanhuanonly
 *
 * @b Classification-discussion
 *
 * ----September 01, 2026 [19h:42m:06s]----
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
        int n, m, k;
        std::cin >> n >> m >> k;

        std::vector<bool> cur(k + 1);

        for (int i = 0, v; i < n; ++i)
        {
            std::cin >> v;
            cur[v] = true;
        }

        int cnt = 0;

        std::map<std::pair<int, int>, int> map;
        std::vector<int> w(k + 1);

        for (int i = 0; i < m; ++i)
        {
            int u, v;
            std::cin >> u >> v;

            if (cur[u] and cur[v])
            {
                ++cnt;
            }
            else if (u == v)
            {
                ++w[u];
            }
            else if (cur[u])
            {
                ++w[v];
            }
            else if (cur[v])
            {
                ++w[u];
            }
            else
            {
                ++map[std::minmax(u, v)];
            }
        }

        int ans = cnt;

        for (auto& [key, value] : map)
        {
            ans = std::max(ans, cnt + value + w[key.first] + w[key.second]);
        }

        std::ranges::sort(w, std::ranges::greater{});
        ans = std::max(ans, cnt + w[0] + w[1]);

        std::cout << ans << '\n';
    }

    return 0;
}
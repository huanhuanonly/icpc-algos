/**
 * Codeforces Round 1109 (Div. 3)
 *
 * => F. Anya Loves Trees! ( @c 1700 )
 *
 * -> https://codeforces.com/contest/2244/problem/F
 *
 * Submissions ~> https://codeforces.com/contest/2244/submission/382650592 By huanhuanonly
 *
 * @b Dfs on @a Trees
 *
 * ----July 14, 2026 [23h:47m:52s]----
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

        std::vector<std::vector<int>> e(n + 1);

        for (int i = 2, p; i <= n; ++i)
        {
            std::cin >> p;

            e[p].push_back(i);
            e[i].push_back(p);
        }

        std::vector<int> w(n + 1);

        for (int i = 1; i <= n; ++i)
        {
            std::cin >> w[i];
        }

        bool yes = true;

        auto dfs = [&](const auto& self, int u, int fa) -> std::pair<int, int>
        {
            std::vector<std::pair<int, int>> que;
            que.reserve(e[u].size());

            for (const int& v : e[u])
            {
                if (v != fa)
                {
                    que.push_back(self(self, v, u));
                }
            }

            if (que.empty())
            {
                return {w[u], w[u]};
            }

            std::ranges::rotate(que, std::ranges::min_element(que));

            for (int i = 1; i < que.size(); ++i)
            {
                if (que[i - 1].second > que[i].first)
                {
                    yes = false;
                    break;
                }
            }

            return {que.front().first, que.back().second};
        };

        dfs(dfs, 1, 0);

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
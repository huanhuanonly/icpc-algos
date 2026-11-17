/**
 * The 2026 ICPC Asia Chengdu Regional Contest (The 5th Universal Cup. Stage 5: Grand Prix of Chengdu)
 *
 * => I. Invisible Edges
 *
 * -> https://codeforces.com/gym/106799/problem/I
 *
 * Submissions ~> https://codeforces.com/gym/106799/submission/397580290 By huanhuanonly
 *
 * @b Communication
 * @b Constructive
 * @b Euler-order
 *
 * ----November 06, 2026 [22h:04m:49s]----
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

    std::string role;
    std::cin >> role;

    int _;
    std::cin >> _;

    if (role == "cat") while (_--)
    {
        int n, m;
        std::cin >> n >> m;

        std::vector<std::vector<int>> e(n + 1);

        for (int i = 0; i < m; ++i)
        {
            int u, v;
            std::cin >> u >> v;

            e[u].push_back(v);
            e[v].push_back(u);
        }

        std::vector<bool> vis(n + 1);
        std::vector<int> id(n + 1);

        auto dfs = [&, time = 0](auto& self, int u) mutable -> void
        {
            id[u] = ++time;
            vis[u] = true;

            for (const auto& v : e[u])
            {
                if (not vis[v])
                {
                    self(self, v);
                }
            }

            ++time;
        };

        for (int u = 1; u <= n; ++u)
        {
            if (not vis[u])
            {
                dfs(dfs, u);
            }
        }

        for (int u = 1; u <= n; ++u)
        {
            std::cout << id[u] << " \n"[u == n];
        }
    }
    else while (_--)
    {
        int n;
        std::cin >> n;

        std::vector<std::pair<int, int>> id(n);

        for (int i = 0; i < n; ++i)
        {
            std::cin >> id[i].first;
            id[i].second = i + 1;
        }

        std::ranges::sort(id);

        std::vector<std::pair<int, int>> e;

        std::stack<int> stack;
        int last = 0;

        for (const auto& [time, u] : id)
        {
            for (int i = 0; i < time - last - 1; stack.pop(), ++i);
            last = time;

            if (not stack.empty())
            {
                e.emplace_back(stack.top(), u);
            }

            stack.push(u);
        }

        std::cout << e.size() << '\n';

        for (const auto& [u, v] : e)
        {
            std::cout << u << ' ' << v << '\n';
        }
    }

    return 0;
}
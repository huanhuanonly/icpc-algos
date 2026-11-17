/**
 * Codeforces Round 318 [RussianCodeCup Thanks-Round] (Div. 2)
 *
 * => E. Bear and Drawing ( @c 2300 )
 *
 * -> https://codeforces.com/contest/574/problem/E
 *
 * Submissions ~> https://codeforces.com/contest/574/submission/328675297 By huanhuanonly
 *
 * @b Classification-discussion and @b Dfs on @a Trees
 *
 * ----July 12, 2025 [22h:54m:25s]----
*/

/// @brief This is an @c interesting problem!

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

    int n;
    std::cin >> n;

    std::vector<std::vector<int>> e(n + 1);

    for (int i = 0; i < n - 1; ++i)
    {
        int u, v;
        std::cin >> u >> v;

        e[u].push_back(v);
        e[v].push_back(u);
    }

    std::vector<int> v(n + 1);

    auto dfs = [&](const auto& self, int u, int fa) -> void
    {
        v[u] = e[u].size() > 2;

        for (int i : e[u] | std::views::filter([fa](int i) -> bool { return i != fa; }))
        {
            self(self, i, u);
            v[u] += v[i];
        }
    };

    auto check = [&](const auto& self, int u, int fa, int cur) -> bool
    {
        cur -= e[u].size() > 2;

        if (cur == 0)
        {
            return true;
        }

        for (int i : e[u] | std::views::filter([fa](int i) -> bool { return i != fa; }))
        {
            if (e[i].size() == 3)
            {
                --cur;
            }
        }

        for (int i : e[u] | std::views::filter([fa](int i) -> bool { return i != fa; }))
        {
            if (self(self, i, u, cur + (e[i].size() == 3)))
            {
                return true;
            }
        }

        return false;
    };

    auto test = [&](int root) -> bool
    {
        dfs(dfs, root, 0);

        int cnt = 0;
        bool yes = true;

        for (int i : e[root])
        {
            if (v[i] and not (v[i] == 1 and e[i].size() == 3))
            {
                ++cnt;
                yes = yes and check(check, i, root, v[i]);
            }
        }

        return yes and cnt <= 2;
    };

    int root = -1;

    for (int i = 1; i <= n; ++i)
    {
        if (e[i].size() > 2)
        {
            root = i;
            break;
        }
    }

    if (root == -1)
    {
        std::cout << "Yes";
    }
    else
    {
        bool yes = test(root);

        for (int i = 0; i < e[root].size() and not yes; ++i)
        {
            if (e[e[root][i]].size() > 2)
            {
                yes = test(e[root][i]);
            }
        }

        if (yes)
        {
            std::cout << "Yes";
        }
        else
        {
            std::cout << "No";
        }
    }

    return 0;
}
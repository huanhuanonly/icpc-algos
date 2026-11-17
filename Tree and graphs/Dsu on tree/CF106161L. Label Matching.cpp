/**
 * The 2025 ICPC Asia Chengdu Regional Contest (The 4rd Universal Cup. Stage 4: Grand Prix of Chengdu)
 *
 * => L. Label Matching
 *
 * -> https://codeforces.com/gym/106161/problem/L
 *
 * Submissions ~> https://codeforces.com/gym/106161/submission/374511379 By huanhuanonly
 *
 * @b Dsu-on-tree
 *
 * ----May 14, 2026 [21h:49m:40s]----
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

        std::vector<int> a(n + 1), b(n + 1);

        for (int i = 1; i <= n; ++i)
        {
            std::cin >> a[i];
        }

        for (int i = 1; i <= n; ++i)
        {
            std::cin >> b[i];
        }

        std::vector<std::vector<int>> e(n + 1);

        for (int i = 0; i < n - 1; ++i)
        {
            int u, v;
            std::cin >> u >> v;

            e[u].push_back(v);
            e[v].push_back(u);
        }

        struct node
        {
            int size;
            int wson;
        };

        std::vector<node> tree(n + 1);

        auto build = [&](const auto& self, int u, int fa) -> void
        {
            tree[u].size = 1;

            for (const auto& v : e[u])
            {
                if (v != fa)
                {
                    self(self, v, u);
                    tree[u].size += tree[v].size;

                    if (tree[v].size > tree[tree[u].wson].size)
                    {
                        tree[u].wson = v;
                    }
                }
            }
        };

        build(build, 1, 0);

        std::vector<int> ca(n + 1), cb(n + 1);
        int cnt = 0;

        std::string ans(n + 1, '0');

        auto add = [&](const auto& self, int u, int fa, int except) -> void
        {
            if (a[u])
            {
                cnt -= std::abs(ca[a[u]] - cb[a[u]]);
            }

            ++ca[a[u]];

            if (a[u])
            {
                cnt += std::abs(ca[a[u]] - cb[a[u]]);
            }


            if (b[u])
            {
                cnt -= std::abs(ca[b[u]] - cb[b[u]]);
            }

            ++cb[b[u]];

            if (b[u])
            {
                cnt += std::abs(ca[b[u]] - cb[b[u]]);
            }

            for (const auto& v : e[u])
            {
                if (v != fa and v != except)
                {
                    self(self, v, u, except);
                }
            }
        };

        auto remove = [&](const auto& self, int u, int fa) -> void
        {
            --ca[a[u]];
            --cb[b[u]];

            for (const auto& v : e[u])
            {
                if (v != fa)
                {
                    self(self, v, u);
                }
            }
        };

        auto calc = [&](int u) -> void
        {
            ans[u] = '0' + (cnt <= ca[0] + cb[0]);
        };

        auto dfs = [&](const auto& self, int u, int fa, bool clear = false) -> void
        {
            if (tree[u].wson)
            {
                for (const auto& v : e[u])
                {
                    if (v != fa and v != tree[u].wson)
                    {
                        self(self, v, u, true);
                    }
                }

                self(self, tree[u].wson, u, false);
            }

            add(add, u, fa, tree[u].wson);

            calc(u);

            if (clear)
            {
                cnt = 0;
                remove(remove, u, fa);
            }
        };

        dfs(dfs, 1, 0);

        std::cout << std::string_view(ans.begin() + 1, ans.end()) << '\n';
    }

    return 0;
}
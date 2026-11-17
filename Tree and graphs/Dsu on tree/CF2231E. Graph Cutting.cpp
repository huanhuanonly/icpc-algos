/**
 * Codeforces Round 1099 (Div. 2)
 *
 * => E. Graph Cutting ( @c 2300 )
 *
 * -> https://codeforces.com/contest/2231/problem/E
 *
 * Submissions ~> https://codeforces.com/contest/2231/submission/379098011 By huanhuanonly
 *
 * @b Dsu-on-tree
 * @b LCA
 *
 * ----June 16, 2026 [15h:49m:51s]----
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
        int n, d;
        std::cin >> n >> d;

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
            int depth;

            int parent;

            int head;
            int wson;
        };

        std::vector<node> tree(n + 1);

        auto build_tree = [&](const auto& self, int u) -> void
        {
            tree[u].wson = 0;
            tree[u].size = 1;

            for (int v : e[u])
            {
                if (v != tree[u].parent)
                {
                    tree[v].parent = u;
                    tree[v].depth = tree[u].depth + 1;

                    self(self, v);

                    tree[u].size += tree[v].size;

                    if (tree[v].size > tree[tree[u].wson].size)
                    {
                        tree[u].wson = v;
                    }
                }
            }
        };

        auto build_head = [&](const auto& self, int u, int head) -> void
        {
            tree[u].head = head;

            if (tree[u].wson)
            {
                self(self, tree[u].wson, head);

                for (int v : e[u])
                {
                    if (v != tree[u].parent and v != tree[u].wson)
                    {
                        self(self, v, v);
                    }
                }
            }
        };

        std::vector<int> dcnt(n + 1);

        auto add = [&](const auto& self, int u) -> void
        {
            ++dcnt[tree[u].depth];

            for (int v : e[u])
            {
                if (v != tree[u].parent)
                {
                    self(self, v);
                }
            }
        };

        auto clear = [&](const auto& self, int u) -> void
        {
            --dcnt[tree[u].depth];

            for (int v : e[u])
            {
                if (v != tree[u].parent)
                {
                    self(self, v);
                }
            }
        };

        uint64 ans = 0;

        auto calc = [&](const auto& self, int u, int eq) -> void
        {
            if (eq > tree[u].depth)
            {
                ans += dcnt[eq - tree[u].depth];
            }

            for (int v : e[u])
            {
                if (v != tree[u].parent)
                {
                    self(self, v, eq);
                }
            }
        };

        auto dfs = [&](const auto& self, int u, int root, bool flag) -> void
        {
            if (tree[u].wson)
            {
                for (int v : e[u])
                {
                    if (v != tree[u].parent and v != tree[u].wson)
                    {
                        self(self, v, root, true);
                    }
                }

                self(self, tree[u].wson, root, false);
            }

            for (int v : e[u])
            {
                if (v != tree[u].parent and v != tree[u].wson)
                {
                    calc(calc, v, d + tree[u].depth);
                    add(add, v);
                }
            }

            if (u != root)
            {
                ans += dcnt[d];
            }

            ++dcnt[tree[u].depth];

            if (flag)
            {
                clear(clear, u);
            }
        };

        for (int root = 1; root <= n; ++root)
        {
            tree[root].parent = 0;
            tree[root].depth = 1;

            build_tree(build_tree, root);
            build_head(build_head, root, root);

            dfs(dfs, root, root, true);
        }

        // assert(ans % 3 == 0);
        std::cout << ans / 3 << '\n';
    }

    return 0;
}
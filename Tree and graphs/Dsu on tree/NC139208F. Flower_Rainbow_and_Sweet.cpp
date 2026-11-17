/**
 * 牛客小白月赛136
 *
 * => F-Flower_Rainbow_and_Sweet ( @c 2200 )
 *
 * -> https://ac.nowcoder.com/acm/contest/139208/F
 *
 * Submissions ~> https://ac.nowcoder.com/acm/contest/view-submission?submissionId=84603072 By huanhuanonly
 *
 * @b Dsu-on-tree
 *
 * ----August 26, 2026 [02h:04m:48s]----
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
        int n, w;
        std::cin >> n >> w;

        std::vector<int> c(n + 1);

        for (int i = 1; i <= n; ++i)
        {
            std::cin >> c[i];
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
        std::vector<std::pair<int, int>> cnt(n + 1);

        auto build = [&](const auto& self, int u, int fa) -> void
        {
            tree[u].size = 1;

            ++cnt[c[u]].first;
            ++cnt[c[u]].second;

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

        int sum = 0;
        std::multiset<int, std::ranges::greater> set;

        auto add = [&](const auto& self, int u, int fa, int except) -> void
        {
            if (not --cnt[c[u]].second)
            {
                sum += cnt[c[u]].first;
                set.insert(cnt[c[u]].first);

                if (sum > w)
                {
                    sum -= set.extract(set.begin()).value();
                }
            }

            for (const auto& v : e[u])
            {
                if (v != fa and v != except)
                {
                    self(self, v, u, except);
                }
            }
        };

        auto clear = [&](const auto& self, int u, int fa) -> void
        {
            ++cnt[c[u]].second;

            for (const auto& v : e[u])
            {
                if (v != fa)
                {
                    self(self, v, u);
                }
            }
        };

        uint64 ans = 0;

        auto dfs = [&](const auto& self, int u, int fa, int depth, int restore) -> void
        {
            if (tree[u].wson)
            {
                for (const auto& v : e[u])
                {
                    if (v != fa and v != tree[u].wson)
                    {
                        self(self, v, u, depth + 1, true);
                    }
                }

                self(self, tree[u].wson, u, depth + 1, false);
            }

            add(add, u, fa, tree[u].wson);
            ans = std::max(ans, uint64(depth) * set.size());

            if (restore)
            {
                clear(clear, u, fa);

                sum = 0;
                set.clear();
            }
        };

        dfs(dfs, 1, 0, 1, true);
        std::cout << ans << '\n';
    }

    return 0;
}
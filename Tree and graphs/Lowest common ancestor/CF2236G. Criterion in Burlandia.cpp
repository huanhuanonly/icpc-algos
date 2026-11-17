/**
 * Codeforces Round 1103 (Div. 3)
 *
 * => G. Criterion in Burlandia ( @c 2600 )
 *
 * -> https://codeforces.com/contest/2236/problem/G
 *
 * Submissions ~> https://codeforces.com/contest/2236/submission/379209973 By huanhuanonly
 *
 * @b Dfs on @a Trees
 * @b LCA ( @a binary-lifting )
 * @b Two-pointers
 * @b Bitwise-XOR
 *
 * ----June 17, 2026 [15h:49m:08s]----
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
        int n, q;
        std::cin >> n >> q;

        std::vector<int> w(n + 1);

        for (int i = 1; i <= n; ++i)
        {
            std::cin >> w[i];
        }

        std::vector<std::vector<int>> e(n + 1);

        for (int i = 0; i < n - 1; ++i)
        {
            int u, v;
            std::cin >> u >> v;

            e[u].push_back(v);
            e[v].push_back(u);
        }

        constexpr int laycnt = 18;

        struct node
        {
            int depth;
            int nonzero_depth;

            std::array<int, laycnt> nonzero_parent;
            std::array<int, laycnt> parent;

            int bad;
            int64 ways;
            int64 pref;
        };

        std::vector<node> tree(n + 1);

        auto build = [&](const auto& self, int u) -> void
        {
            if (w[tree[u].parent[0]])
            {
                tree[u].nonzero_parent[0] = tree[u].parent[0];
            }
            else
            {
                tree[u].nonzero_parent[0] = tree[tree[u].parent[0]].nonzero_parent[0];
            }

            if (w[u])
            {
                tree[u].bad = u;
                for (int& i = tree[u].bad, sum = 0; i and (sum & w[i]) == 0; sum |= w[i], i = tree[i].nonzero_parent[0]);
            }
            else
            {
                tree[u].bad = tree[tree[u].parent[0]].bad;
            }

            tree[u].nonzero_depth = tree[tree[u].nonzero_parent[0]].nonzero_depth + 1;

            tree[u].ways = tree[u].depth - tree[tree[u].bad].depth;
            tree[u].pref = tree[tree[u].parent[0]].pref + tree[u].ways;

            for (int v : e[u])
            {
                if (v != tree[u].parent[0])
                {
                    tree[v].parent[0] = u;
                    tree[v].depth = tree[u].depth + 1;

                    self(self, v);
                }
            }
        };

        tree[0].depth = tree[0].nonzero_depth = -1;

        build(build, 1);

        for (int lay = 1; lay < laycnt; ++lay)
        {
            for (int u = 1; u <= n; ++u)
            {
                tree[u].parent[lay] = tree[tree[u].parent[lay - 1]].parent[lay - 1];
                tree[u].nonzero_parent[lay] = tree[tree[u].nonzero_parent[lay - 1]].nonzero_parent[lay - 1];
            }
        }

        auto lca = [&](int u, int v) -> int
        {
            if (tree[u].depth < tree[v].depth)
            {
                std::swap(u, v);
            }

            for (int i = laycnt, diff = tree[u].depth - tree[v].depth; i--; )
            {
                if (diff & 1 << i)
                {
                    u = tree[u].parent[i];
                }
            }

            if (u == v)
            {
                return u;
            }

            for (int i = laycnt; i--; )
            {
                if (tree[u].parent[i] != tree[v].parent[i])
                {
                    u = tree[u].parent[i];
                    v = tree[v].parent[i];
                }
            }

            return tree[u].parent[0];
        };

        auto dist = [&](int u, int v) -> int
        {
            return tree[u].depth + tree[v].depth - tree[lca(u, v)].depth * 2;
        };

        auto vertical_dist = [&](int u, int v) -> int
        {
            return std::abs(tree[u].depth - tree[v].depth);
        };

        auto nonzero_node = [&](int u) -> int
        {
            return w[u] ? u : tree[u].nonzero_parent[0];
        };

        auto nonzero_depth = [&](int u) -> int
        {
            return tree[nonzero_node(u)].nonzero_depth;
        };

        auto climb_nonzero = [&](int u, int target_nonzero_depth) -> int
        {
            if (not w[u])
            {
                u = tree[u].nonzero_parent[0];
            }

            for (int i = laycnt, diff = tree[u].nonzero_depth - target_nonzero_depth; i--; )
            {
                if (diff & 1 << i)
                {
                    u = tree[u].nonzero_parent[i];
                }
            }

            return u;
        };

        auto calc = [&, s = std::vector<int>()](int u, int v) mutable -> int64
        {
            const int t = lca(u, v);
            constexpr int limit = 21;

            const int lca_nonzero_depth = nonzero_depth(t);

            int64 sum = 0;

            if (const int ud = nonzero_depth(u); lca_nonzero_depth + limit < ud)
            {
                const int keep = climb_nonzero(u, lca_nonzero_depth + limit);
                sum += tree[u].pref - tree[keep].pref;
                u = keep;
            }

            if (const int vd = nonzero_depth(v); lca_nonzero_depth + limit < vd)
            {
                const int keep = climb_nonzero(v, lca_nonzero_depth + limit);
                sum += tree[v].pref - tree[keep].pref;
                v = keep;
            }

            for (int i = nonzero_node(u); i and tree[i].depth >= tree[t].depth; i = tree[i].nonzero_parent[0])
            {
                s.push_back(i);
            }

            const int checkpoint = s.size();

            for (int i = nonzero_node(v); i and tree[i].depth > tree[t].depth; i = tree[i].nonzero_parent[0])
            {
                s.push_back(i);
            }

            std::ranges::reverse(s.begin() + checkpoint, s.end());

            if (s.empty())
            {
                const int d = tree[u].depth + tree[v].depth - tree[t].depth * 2 + 1;
                return d * int64(d + 1) / 2;
            }

            assert(s.size() <= 50);

            std::vector<int> gap(s.size() + 1);

            gap.front() = dist(u, s.front());
            gap.back() = dist(s.back(), v);

            for (int i = 1; i < checkpoint; ++i)
            {
                gap[i] = vertical_dist(s[i - 1], s[i]) - 1;
            }

            for (int i = checkpoint + 1; i < int(s.size()); ++i)
            {
                gap[i] = vertical_dist(s[i - 1], s[i]) - 1;
            }

            if (1 <= checkpoint and checkpoint < s.size())
            {
                gap[checkpoint] = dist(s[checkpoint - 1], s[checkpoint]) - 1;
            }

            for (int d : gap)
            {
                sum += d * int64(d + 1) / 2;
            }

            for (int i = 0, j = 0, xorsum = 0, d = 0; i < int(s.size()); ++i)
            {
                for (; j < int(s.size()) and (xorsum & w[s[j]]) == 0; xorsum |= w[s[j]], ++j, d += 1 + gap[j]);

                sum += int64(gap[i] + 1) * d;

                xorsum &= ~w[s[i]];
                d -= 1 + gap[i + 1];
            }

            s.clear();
            return sum;
        };

        while (q--)
        {
            int u, v;
            std::cin >> u >> v;

            std::cout << calc(u, v) << '\n';
        }
    }

    return 0;
}
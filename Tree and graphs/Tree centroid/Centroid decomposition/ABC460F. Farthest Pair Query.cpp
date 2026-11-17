/**
 * AtCoder Beginner Contest 460
 *
 * => F - Farthest Pair Query ( @c 550 )
 *
 * -> https://atcoder.jp/contests/abc460/tasks/abc460_f
 *
 * Submissions ~> https://atcoder.jp/contests/abc460/submissions/76365506 By huanhuanonly
 *
 * @b Centroid-decomposition
 *
 * ----June 03, 2026 [16h:16m:39s]----
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

    std::vector<bool> removed(n + 1);
    std::vector<int> sizes(n + 1);

    auto find_centroid = [&](int u) -> int
    {
        std::vector<int> set;

        auto build = [&](const auto& self, int u, int fa) -> void
        {
            if (removed[u])
            {
                return;
            }

            set.push_back(u);

            sizes[u] = 1;

            for (int v : e[u])
            {
                if (v != fa)
                {
                    self(self, v, u);
                    sizes[u] += sizes[v];
                }
            }
        };

        build(build, u, 0);

        for (int v : set)
        {
            std::priority_queue<int> que;

            for (int i : e[v])
            {
                que.push(sizes[i]);
            }

            if (v != u)
            {
                que.pop();
                que.push(sizes[u] - sizes[v]);
            }

            if (que.top() <= sizes[u] / 2)
            {
                return v;
            }
        }

        std::unreachable();
    };

    std::vector<int> depth(n + 1);

    std::multiset<int, std::ranges::greater> best;

    std::vector<std::multiset<int, std::ranges::greater>> dsets(n + 1);
    std::vector<std::vector<std::multiset<int, std::ranges::greater>>> disets(n + 1);

    std::vector<std::vector<std::tuple<int, int, int>>> psets(n + 1);

    auto contr = [&](int u) -> int
    {
        if (dsets[u].size() >= 2)
        {
            return *dsets[u].begin() + *std::next(dsets[u].begin());
        }
        else
        {
            return 0;
        }
    };

    auto collect = [&](const auto& self, int u, int fa, int top) -> void
    {
        psets[u].emplace_back(top, disets[top].size() - 1, depth[u]);
        disets[top].back().insert(depth[u]);

        for (int v : e[u])
        {
            if (v != fa and not removed[v])
            {
                depth[v] = depth[u] + 1;
                self(self, v, u, top);
            }
        }
    };

    auto centroid_decomposition = [&](const auto& self, int u) -> void
    {
        removed[u] = true;
        sizes[u] = 0;
        depth[u] = 0;

        disets[u].emplace_back();
        psets[u].emplace_back(u, 0, 0);
        disets[u].back().insert(0);

        for (int v : e[u])
        {
            if (not removed[v])
            {
                depth[v] = 1;

                disets[u].emplace_back();
                collect(collect, v, u, u);
                self(self, find_centroid(v));
            }
        }

        for (const auto& set : disets[u])
        {
            dsets[u].insert(*set.begin());
        }

        best.insert(contr(u));
    };

    centroid_decomposition(centroid_decomposition, find_centroid(1));

    std::vector<bool> color(n + 1, true);

    int q;
    std::cin >> q;

    while (q--)
    {
        int u;
        std::cin >> u;

        for (const auto& [parent, id, d] : psets[u])
        {
            const int backup_contr = contr(parent);

            if (disets[parent][id].empty())
            {
                color[u] ? void(disets[parent][id].extract(d)) : void(disets[parent][id].insert(d));

                if (not disets[parent][id].empty())
                {
                    dsets[parent].insert(*disets[parent][id].begin());
                }
            }
            else
            {
                auto nd = dsets[parent].extract(*disets[parent][id].begin());
                color[u] ? void(disets[parent][id].extract(d)) : void(disets[parent][id].insert(d));

                if (not disets[parent][id].empty())
                {
                    nd.value() = *disets[parent][id].begin();
                    dsets[parent].insert(std::move(nd));
                }
            }

            const int current_contr = contr(parent);

            auto nd = best.extract(backup_contr);
            nd.value() = current_contr;
            best.insert(std::move(nd));
        }

        color[u] = not color[u];

        std::cout << *best.begin() << '\n';
    }

    return 0;
}
/**
 * UNICORNProgramming Contest2026(AtCoder Beginner Contest 477)
 *
 * => G - Frequency Query on Tree ( @c 625 )
 *
 * -> https://atcoder.jp/contests/abc477/tasks/abc477_g
 *
 * Submissions ~> https://atcoder.jp/contests/abc477/submissions/79647086 By huanhuanonly
 *
 * @b Mo's-algorithm ( @a on-trees )
 * @b Sqrt-decomposition ( @a by-index )
 *
 * ----October 01, 2026 [03h:11m:33s]----
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

    int n, q;
    std::cin >> n >> q;

    std::vector<int> x(n + 1);

    for (int i = 1; i <= n; ++i)
    {
        std::cin >> x[i];
    }

    std::vector<std::vector<int>> e(n + 1);

    for (int i = 0; i < n - 1; ++i)
    {
        int u, v;
        std::cin >> u >> v;

        e[u].push_back(v);
        e[v].push_back(u);
    }

    constexpr int laycnt = 20;
    std::vector<std::array<int, laycnt>> parent(n + 1);
    std::vector<int> depth(n + 1);

    std::vector<int> tour;
    tour.reserve(n * 2);

    std::vector<std::pair<int, int>> inout(n + 1);

    auto dfs = [&](const auto& self, int u) -> void
    {
        inout[u].first = tour.size();
        tour.push_back(u);

        for (int i = 1; i < laycnt; ++i)
        {
            parent[u][i] = parent[parent[u][i - 1]][i - 1];
        }

        for (const auto& v : e[u])
        {
            if (v != parent[u][0])
            {
                parent[v][0] = u;
                depth[v] = depth[u] + 1;

                self(self, v);
            }
        }

        inout[u].second = tour.size();
        tour.push_back(u);
    };

    dfs(dfs, 1);

    auto lca = [&](int u, int v) -> int
    {
        if (depth[u] < depth[v])
        {
            std::swap(u, v);
        }

        for (int i = 0, diff = depth[u] - depth[v]; i < laycnt; ++i)
        {
            if (diff & 1 << i)
            {
                u = parent[u][i];
            }
        }

        if (u == v)
        {
            return u;
        }

        for (int i = laycnt; i--; )
        {
            if (parent[u][i] != parent[v][i])
            {
                u = parent[u][i];
                v = parent[v][i];
            }
        }

        return parent[u][0];
    };

    struct query
    {
        int l, r, a, b;
        int extra;
        int qid, ans;
    };

    std::vector<query> queries(q);

    for (int id = 0; auto& [s, t, a, b, extra, qid, ans] : queries)
    {
        std::cin >> s >> t >> a >> b;

        if (inout[s].first > inout[t].first)
        {
            std::swap(s, t);
        }

        const int mid = lca(s, t);

        if (s == mid)
        {
            s = inout[s].first;
            t = inout[t].first;
            extra = ~0;
        }
        else
        {
            s = inout[s].second;
            t = inout[t].first;
            extra = inout[mid].first;
        }

        qid = id++;
    }

    const int sqn = std::ceil(tour.size() / std::sqrt(q));

    std::ranges::sort(queries, [&](const query& lhs, const query& rhs) -> bool
    {
        const int lbid = lhs.l / sqn;
        const int rbid = rhs.l / sqn;

        if (lbid != rbid)
        {
            return lbid < rbid;
        }

        if (lbid & 1)
        {
            return lhs.r > rhs.r;
        }
        else
        {
            return lhs.r < rhs.r;
        }
    });

    std::vector<int> cnt(n + 1);
    std::vector<int> tot(n + 1);
    std::vector<int> sum(n / sqn + 1);

    auto calc = [&](int l, int r) -> int
    {
        const int bl = l / sqn, br = r / sqn;

        int res = 0;

        if (bl == br)
        {
            for (; l <= r; ++l)
            {
                res += tot[l];
            }
        }
        else
        {
            for (; l < (bl + 1) * sqn; ++l)
            {
                res += tot[l];
            }

            for (; r >= br * sqn; --r)
            {
                res += tot[r];
            }

            for (int i = bl + 1; i < br; ++i)
            {
                res += sum[i];
            }
        }

        return res;
    };

    tot[0] = sum[0] = n;

    auto add = [&](int i) -> void
    {
        --tot[cnt[x[tour[i]]]];
        --sum[cnt[x[tour[i]]] / sqn];

        ++cnt[x[tour[i]]];

        ++tot[cnt[x[tour[i]]]];
        ++sum[cnt[x[tour[i]]] / sqn];
    };

    auto remove = [&](int i) -> void
    {
        --tot[cnt[x[tour[i]]]];
        --sum[cnt[x[tour[i]]] / sqn];

        --cnt[x[tour[i]]];

        ++tot[cnt[x[tour[i]]]];
        ++sum[cnt[x[tour[i]]] / sqn];
    };

    std::vector<bool> vis(n + 1);

    auto toggle = [&](int i) -> void
    {
        if (vis[tour[i]])
        {
            remove(i);
        }
        else
        {
            add(i);
        }

        vis[tour[i]] = not vis[tour[i]];
    };

    for (int l = 0, r = 0; auto& [s, t, a, b, extra, qid, ans] : queries)
    {
        for (; r <= t; toggle(r++));
        for (; s < l; toggle(--l));
        for (; t + 1 < r; toggle(--r));
        for (; l < s; toggle(l++));

        if (~extra)
        {
            add(extra);
        }

        ans = calc(a, b);

        if (~extra)
        {
            remove(extra);
        }
    }

    std::ranges::sort(queries, {}, &query::qid);

    for (const auto& ans : queries | std::views::transform(&query::ans))
    {
        std::cout << ans << '\n';
    }

    return 0;
}
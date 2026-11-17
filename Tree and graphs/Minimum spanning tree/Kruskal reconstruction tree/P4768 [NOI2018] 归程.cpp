/**
 * => P4768 [NOI2018] 归程 ( @c 省选/NOI- )
 *
 * -> https://www.luogu.com.cn/problem/P4768
 *
 * Submissions ~> https://www.luogu.com.cn/record/282193516 By huanhuanonly
 *
 * @b Kruskal-reconstruction-tree
 * @b Topological-sorting on @a Trees
 * @b Binary-lifting
 * @b Dijkstra
 *
 * ----June 18, 2026 [11h:05m:58s]----
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

inline namespace huanhuanonly {
    inline namespace data_structure
{
class DisjointSet
{
public:

    using size_type = int;

    explicit
    DisjointSet(size_type __n)
        : _M_parent(__n)
    { reset(); }

    [[nodiscard]] size_type
    find(size_type u)
    { return _M_parent[u] == u ? u : _M_parent[u] = find(_M_parent[u]); }

    bool
    unite(size_type u, size_type v)
    {
        const size_type fu = find(u);
        const size_type fv = find(v);

        if (fu != fv)
        {
            _M_parent[fv] = fu;
            return true;
        }
        else
        {
            return false;
        }
    }

    [[nodiscard]] bool
    connected(size_type u, size_type v)
    { return find(u) == find(v); }

    void
    expand(size_type __n)
    {
        const size_type size = static_cast<size_type>(_M_parent.size());
        _M_parent.resize(size + __n);
        std::iota(_M_parent.begin() + size, _M_parent.end(), size);
    }

    void
    reset()
    { std::iota(_M_parent.begin(), _M_parent.end(), 0); }

    [[nodiscard]] size_type
    size()
    { return static_cast<size_type>(_M_parent.size()); }

private:

    std::vector<size_type> _M_parent;
};
}} // namespace huanhuanonly::data_structure

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
        int n, m;
        std::cin >> n >> m;

        std::vector<std::tuple<int, int, int, int>> e(m);
        std::vector<std::vector<std::pair<int, int>>> g(n + 1);

        for (auto& [u, v, l, a] : e)
        {
            std::cin >> u >> v >> l >> a;

            g[u].emplace_back(v, l);
            g[v].emplace_back(u, l);
        }

        std::ranges::sort(e, std::ranges::greater{}, [](const auto& t) { return std::get<3>(t); });

        DisjointSet dsu(n + m + 1);

        constexpr int laycnt = 20;
        std::vector<std::array<int, laycnt>> parent(dsu.size());

        constexpr auto inf = std::numeric_limits<int>::max() / 2;

        std::vector<int> weight(n + m + 1);
        std::vector<int> dist(n + m + 1, inf);
        std::vector<int> outdegree(n + m + 1);

        for (int id = n; const auto& [u, v, l, a] : e)
        {
            if (not dsu.connected(u, v))
            {
                ++id;

                parent[dsu.find(u)][0] = parent[dsu.find(v)][0] = id;

                dsu.unite(id, u);
                dsu.unite(id, v);

                weight[id] = a;
                outdegree[id] = 2;
            }
        }

        for (int i = 1; i < laycnt; ++i)
        {
            for (int u = 1; u <= n + m; ++u)
            {
                parent[u][i] = parent[parent[u][i - 1]][i - 1];
            }
        }

        auto bfs = [&]() -> void
        {
            struct item
            {
                int to, w;

                bool operator<(const item& rhs) const
                {
                    return w > rhs.w;
                }
            };

            std::priority_queue<item> que;
            que.emplace(1, 0);
            dist[1] = 0;

            std::vector<bool> vis(n + 1);

            while (not que.empty())
            {
                const auto [u, cdis] = que.top();
                que.pop();

                if (vis[u])
                {
                    continue;
                }

                vis[u] = true;

                for (const auto& [v, w] : g[u])
                {
                    if (dist[u] + w < dist[v])
                    {
                        dist[v] = dist[u] + w;
                        que.emplace(v, dist[v]);
                    }
                }
            }
        };

        auto build = [&]() -> void
        {
            std::queue<int> que;

            for (int i = 1; i <= n; ++i)
            {
                que.push(i);
            }

            while (not que.empty())
            {
                const int u = que.front();
                que.pop();

                dist[parent[u][0]] = std::min(dist[parent[u][0]], dist[u]);

                if (--outdegree[parent[u][0]] == 0)
                {
                    que.push(parent[u][0]);
                }
            }
        };

        bfs();
        build();

        auto jump_up = [&](int u, int level) -> int
        {
            for (int i = laycnt; i--; )
            {
                if (weight[parent[u][i]] > level)
                {
                    u = parent[u][i];
                }
            }

            return u;
        };

        int q, k, s;
        std::cin >> q >> k >> s;

        for (int lastans = 0; q--; )
        {
            int u, p;
            std::cin >> u >> p;

            u = (u + k * lastans - 1) % n + 1;
            p = (p + k * lastans) % (s + 1);

            std::cout << (lastans = dist[jump_up(u, p)]) << '\n';
        }
    }

    return 0;
}
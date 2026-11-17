/**
 * AtCoder Grand Contest 002
 *
 * => D - Stamp Rally ( @c 1000 )
 *
 * -> https://atcoder.jp/contests/agc002/tasks/agc002_d
 *
 * Submissions ~> https://atcoder.jp/contests/agc002/submissions/76754642 By huanhuanonly
 *
 * @b Kruskal-reconstruction-tree
 * @b Topological-sorting on @a Trees
 * @b Binary-lifting
 * @b Binary-search
 *
 * ----June 18, 2026 [10h:17m:53s]----
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

    int n, m;
    std::cin >> n >> m;

    DisjointSet dsu(n + m + 1);

    constexpr int laycnt = 18;
    std::vector<std::array<int, laycnt>> parent(dsu.size());

    std::vector<int> weight(n + m + 1);
    std::vector<int> size(n + m + 1);
    std::vector<int> outdegree(n + m + 1);

    for (int i = 1, id = n; i <= m; ++i)
    {
        int u, v;
        std::cin >> u >> v;

        if (not dsu.connected(u, v))
        {
            ++id;

            parent[dsu.find(u)][0] = parent[dsu.find(v)][0] = id;

            dsu.unite(id, u);
            dsu.unite(id, v);

            weight[id] = i;
            outdegree[id] = 2;
        }
    }

    std::ranges::fill_n(size.begin() + 1, n, 1);
    weight[0] = std::numeric_limits<int>::max();

    auto bfs = [&]() -> void
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

            size[parent[u][0]] += size[u];

            if (--outdegree[parent[u][0]] == 0)
            {
                que.push(parent[u][0]);
            }
        }
    };

    bfs();

    for (int i = 1; i < laycnt; ++i)
    {
        for (int u = 1; u <= n + m; ++u)
        {
            parent[u][i] = parent[parent[u][i - 1]][i - 1];
        }
    }

    auto jump_up = [&](int u, int limit) -> int
    {
        for (int i = laycnt; i--; )
        {
            if (weight[parent[u][i]] <= limit)
            {
                u = parent[u][i];
            }
        }

        return u;
    };

    int q;
    std::cin >> q;

    while (q--)
    {
        int u, v, x;
        std::cin >> u >> v >> x;

        auto check = [&](int mid) -> bool
        {
            const int i = jump_up(u, mid);
            const int j = jump_up(v, mid);

            if (i != j)
            {
                return size[i] + size[j] >= x;
            }
            else
            {
                return size[i] >= x;
            }
        };

        int l = 0, r = m + 1, mid;

        while (r - l > 1)
        {
            mid = l + r >> 1;

            if (check(mid))
            {
                r = mid;
            }
            else
            {
                l = mid;
            }
        }

        std::cout << r << '\n';
    }

    return 0;
}
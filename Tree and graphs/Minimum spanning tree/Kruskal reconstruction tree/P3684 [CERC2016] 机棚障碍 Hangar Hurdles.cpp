/**
 * => P3684 [CERC2016] 机棚障碍 Hangar Hurdles ( @c 省选/NOI- )
 *
 * -> https://www.luogu.com.cn/problem/P3684
 *
 * Submissions ~> https://www.luogu.com.cn/record/282328593 By huanhuanonly
 *
 * @b Kruskal-reconstruction-tree
 * @b 2D-Prefix-sum
 * @b Binary-search
 * @b LCA ( @a binary-lifting )
 *
 * ----June 19, 2026 [19h:37m:42s]----
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

    int n;
    std::cin >> n;

    std::vector<std::string> map(n + 1);

    map[0] = std::string(n + 1, ' ');

    for (int i = 1; i <= n; ++i)
    {
        std::cin >> map[i];
        map[i].insert(map[i].begin(), ' ');
    }

    std::vector pre(n + 1, std::vector<int>(n + 1));

    for (int i = 1; i <= n; ++i)
    {
        for (int j = 1; j <= n; ++j)
        {
            pre[i][j] = pre[i - 1][j] + pre[i][j - 1] - pre[i - 1][j - 1] + (map[i][j] == '#');
        }
    }

    auto $ = [n](int x, int y) -> int
    {
        return (x - 1) * n + y;
    };

    auto blocks = [&](int left, int top, int right, int bottom) -> bool
    {
        auto within = [&](int p) -> bool
        {
            return p >= 1 and p <= n;
        };

        if (within(left) and within(top) and within(right) and within(bottom))
        {
            return pre[right][bottom] - pre[left - 1][bottom] - pre[right][top - 1] + pre[left - 1][top - 1];
        }
        else
        {
            return true;
        }
    };

    auto calc = [&](const std::pair<int, int>& s, const std::pair<int, int>& t) -> int
    {
        if (map[s.first][s.second] == '#' or map[t.first][t.second] == '#')
        {
            return 0;
        }

        auto check = [&](int mid) -> bool
        {
            return
                not blocks(s.first - mid, s.second - mid, s.first + mid, s.second + mid) and
                not blocks(t.first - mid, t.second - mid, t.first + mid, t.second + mid);
        };

        int l = 0, r = n / 2 + 1, mid;

        while (r - l > 1)
        {
            mid = l + r >> 1;

            if (check(mid))
            {
                l = mid;
            }
            else
            {
                r = mid;
            }
        }

        return l * 2 + 1;
    };

    std::vector<std::tuple<int, int, int>> e;

    for (int i = 1; i <= n; ++i)
    {
        for (int j = 1; j <= n; ++j)
        {
            if (i + 1 <= n)
            {
                e.emplace_back($(i, j), $(i + 1, j), calc({i, j}, {i + 1, j}));
            }

            if (j + 1 <= n)
            {
                e.emplace_back($(i, j), $(i, j + 1), calc({i, j}, {i, j + 1}));
            }
        }
    }

    std::ranges::sort(e, std::ranges::greater{}, [](const auto& t) { return std::get<2>(t); });

    DisjointSet dsu(n * n * 2 + 1);
    std::vector<int> weight(dsu.size());

    constexpr int laycnt = 22;
    std::vector<std::array<int, laycnt>> parent(dsu.size());

    std::vector<int> depth(dsu.size());

    for (int id = n * n; const auto& [u, v, w] : e)
    {
        if (not dsu.connected(u, v))
        {
            ++id;

            weight[id] = w;
            parent[dsu.find(u)][0] = parent[dsu.find(v)][0] = id;

            dsu.unite(id, u);
            dsu.unite(id, v);
        }
    }

    std::stack<int, std::vector<int>> stack;

    for (int i = 1; i <= n * n; ++i)
    {
        for (int u = i; u and not depth[u]; stack.push(u), u = parent[u][0]);
        for (; not stack.empty(); depth[stack.top()] = depth[parent[stack.top()][0]] + 1, stack.pop());
    }

    for (int i = 1; i < laycnt; ++i)
    {
        for (int u = 1; u < dsu.size(); ++u)
        {
            parent[u][i] = parent[parent[u][i - 1]][i - 1];
        }
    }

    auto lca = [&](int u, int v) -> int
    {
        if (depth[u] < depth[v])
        {
            std::swap(u, v);
        }

        for (int i = laycnt, diff = depth[u] - depth[v]; i--; )
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

    int q;
    std::cin >> q;

    while (q--)
    {
        int left, top, right, bottom;
        std::cin >> left >> top >> right >> bottom;

        std::cout << weight[lca($(left, top), $(right, bottom))] << '\n';
    }

    return 0;
}
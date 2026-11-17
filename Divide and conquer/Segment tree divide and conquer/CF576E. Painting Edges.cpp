/**
 * Codeforces Round 319 (Div. 1)
 *
 * => E. Painting Edges ( @c 3300 )
 *
 * -> https://codeforces.com/contest/576/problem/E
 *
 * Submissions ~> https://codeforces.com/contest/576/submission/383980337 By huanhuanonly
 *
 * @b Segment-tree-divide-and-conquer
 * @b Extended-domain-disjoint-set-with-rollback
 * @b Bipartite-graph
 *
 * ----July 24, 2026 [00h:53m:35s]----
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
class RollbackDisjointSet
{
public:

    using size_type = int;

    struct node
    {
        size_type parent;
        size_type size;
    };

    struct change_record
    {
        std::pair<size_type&, size_type> parent;
        std::pair<size_type&, size_type> size;
    };

    explicit
    RollbackDisjointSet(size_type __n = 0)
        : _M_tree(__n)
    { for (size_type i = 0; i < __n; _M_tree[i] = node{.parent = i++, .size = 1}); }

    [[nodiscard]] size_type
    find(size_type u) const
    { return is_root(u) ? u : find(_M_tree[u].parent); }

    bool
    unite(size_type u, size_type v)
    {
        size_type fu = find(u);
        size_type fv = find(v);

        if (fu == fv)
        {
            return false;
        }

        if (_M_tree[fu].size < _M_tree[fv].size)
        {
            std::swap(fu, fv);
        }

        _M_history.emplace(change_record{
                {_M_tree[fv].parent, _M_tree[fv].parent},
                {_M_tree[fu].size,   _M_tree[fu].size  }});

        _M_tree[fv].parent = fu;
        _M_tree[fu].size += _M_tree[fv].size;

        return true;
    }

    [[nodiscard]] bool
    is_root(size_type u) const
    { return _M_tree[u].parent == u; }

    [[nodiscard]] bool
    connected(size_type u, size_type v) const
    { return find(u) == find(v); }

    void
    expand(size_type __n)
    {
        assert(_M_history.empty());

        const size_type old_size = size();
        _M_tree.resize(old_size + __n);

        for (size_type i = old_size; i < old_size + __n; ++i)
        {
            _M_tree[i].parent = i;
            _M_tree[i].size = 1;
        }
    }

    void
    reset()
    { rollback(0); }

    [[nodiscard]] size_type
    size() const
    { return static_cast<size_type>(_M_tree.size()); }

    [[nodiscard]] size_type
    component_size(size_type u) const
    { return _M_tree[find(u)].size; }

    [[nodiscard]] size_type
    checkpoint() const
    { return static_cast<size_type>(_M_history.size()); }

    void
    undo()
    {
        if (not _M_history.empty())
        {
            const auto& rec = _M_history.top();

            rec.parent.first = rec.parent.second;
            rec.size.first = rec.size.second;

            _M_history.pop();
        }
    }

    void
    rollback(size_type __cp)
    { for (; checkpoint() > __cp; undo()); }

private:

    std::vector<node> _M_tree;
    std::stack<change_record, std::vector<change_record>> _M_history;
};
}} // namespace huanhuanonly::data_structure

class SegmentTree
{
public:

    struct edge
    {
        int p, c;
    };

    std::vector<std::vector<edge>> tree;

    explicit SegmentTree(int n)
        : tree(n << 2)
    { }

    static int ls(int u)
    {
        return u << 1;
    }

    static int rs(int u)
    {
        return u << 1 | 1;
    }

    void insert(int u, int l, int r, int x, int y, const edge& e)
    {
        if (x <= l and r <= y)
        {
            tree[u].push_back(e);
            return;
        }

        const int mid = l + r >> 1;

        if (x <= mid)
        {
            insert(ls(u), l, mid, x, y, e);
        }

        if (y > mid)
        {
            insert(rs(u), mid + 1, r, x, y, e);
        }
    }
};

int main(void)
{
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);

#ifdef __huanhuanonly_localhost
    ::freopen("in", "r", stdin);
    ::freopen("out", "w", stdout);
#endif

    int n, m, k, q;
    std::cin >> n >> m >> k >> q;

    std::vector<std::pair<int, int>> e(m + 1);
    std::vector<int> color(m + 1);

    for (auto& [u, v] : e | std::views::drop(1))
    {
        std::cin >> u >> v;
    }

    SegmentTree seg(q + 1);

    std::vector<bool> ans(q + 1);
    std::vector dsus(k + 1, RollbackDisjointSet(n + n + 1));

    std::vector<std::pair<int, int>> queries(q + 1);
    std::vector<std::vector<int>> next(m + 1);

    for (int i = 1; i <= q; ++i)
    {
        auto& [p, c] = queries[i];
        std::cin >> p >> c;

        next[p].push_back(i);
    }

    for (auto& i : next)
    {
        i.push_back(q + 1);
        std::ranges::reverse(i);
    }

    auto divide = [&](const auto& self, int u, int l, int r) -> void
    {
        const auto cps = dsus | std::views::transform(&RollbackDisjointSet::checkpoint) | std::ranges::to<std::vector>();

        for (const auto& [p, c] : seg.tree[u])
        {
            dsus[c].unite(e[p].first, n + e[p].second);
            dsus[c].unite(n + e[p].first, e[p].second);
        }

        if (l == r)
        {
            const auto& [p, c] = queries[l];

            if (ans[l] = not dsus[c].connected(e[p].first, e[p].second))
            {
                color[p] = c;
            }

            next[p].pop_back();
            seg.insert(1, 1, q, l + 1, next[p].back() - 1, {p, color[p]});
        }
        else
        {
            const int mid = l + r >> 1;
            self(self, seg.ls(u), l, mid);
            self(self, seg.rs(u), mid + 1, r);
        }

        for (auto&& [dsu, cp] : std::views::zip(dsus, cps))
        {
            dsu.rollback(cp);
        }
    };

    divide(divide, 1, 1, q);

    for (int i = 1; i <= q; ++i)
    {
        if (ans[i])
        {
            std::cout << "YES\n";
        }
        else
        {
            std::cout << "NO\n";
        }
    }

    return 0;
}
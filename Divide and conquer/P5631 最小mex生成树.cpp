/**
 * => P5631 最小mex生成树 ( @c 省选/NOI- )
 *
 * -> https://www.luogu.com.cn/problem/P5631
 *
 * Submissions ~> https://www.luogu.com.cn/record/286794299 By huanhuanonly
 *
 * @b Kruskal’s-algorithm
 * @b Divide-and-conquer
 * @b Disjoint-set-with-rollback
 *
 * ----July 17, 2026 [23h:34m:35s]----
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

    constexpr int maxw = 1e5 + 1;
    std::vector<std::vector<std::pair<int, int>>> e(maxw + 1);

    for (int i = 0; i < m; ++i)
    {
        int u, v, w;
        std::cin >> u >> v >> w;

        e[w].emplace_back(u, v);
    }

    RollbackDisjointSet dsu(n + 1);

    auto add = [&](int l, int r) -> void
    {
        for (; l <= r; ++l)
        {
            for (const auto& [u, v] : e[l])
            {
                dsu.unite(u, v);
            }
        }
    };

    auto divide = [&](const auto& self, int l, int r) -> int
    {
        if (l == r)
        {
            if (dsu.component_size(1) == n)
            {
                return l;
            }
            else
            {
                return ~0;
            }
        }

        const auto cp = dsu.checkpoint();

        const int mid = l + r >> 1;

        add(mid + 1, r);
        if (const int res = self(self, l, mid); ~res)
        {
            return res;
        }
        dsu.rollback(cp);

        add(l, mid);
        if (const int res = self(self, mid + 1, r); ~res)
        {
            return res;
        }
        dsu.rollback(cp);

        return ~0;
    };

    std::cout << divide(divide, 0, maxw) << '\n';

    return 0;
}
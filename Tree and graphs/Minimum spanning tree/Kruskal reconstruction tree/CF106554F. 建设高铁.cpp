/**
 * [Unofficial Mirror] 2026 CCPC National Invitational (Nanchang) and The 3rd Jiangxi Provincial Programming Contest
 *
 * => F. 建设高铁
 *
 * -> https://codeforces.com/gym/106554/problem/F
 *
 * Submissions ~> https://codeforces.com/gym/106554/submission/379819773 By huanhuanonly
 *
 * @b Kruskal-reconstruction-tree
 * @b Dfs on @a Trees
 * @b Dfs-order
 * @b LCA ( @a binary-lifting )
 * @b Split-merge-treap
 *
 * ----June 22, 2026 [23h:08m:24s]----
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

inline namespace huanhuanonly {
    inline namespace data_structure
{
template<
    typename _Derived,
    typename _Tp,
    typename _Comp = std::ranges::less,
    typename _MergeFunc = decltype([](const _Tp& lhs, const _Tp&) -> _Tp { return lhs; })>
requires std::convertible_to<std::invoke_result_t<_MergeFunc, _Tp, _Tp>, _Tp>
class MergeSplitTreapImpl
{
public:

    using value_type = _Tp;
    using reference = value_type&;
    using const_reference = const value_type&;
    using size_type = int;

    struct node
    {
        size_type ls, rs;

        size_type priority;
        size_type size;

        value_type value;
        value_type reduced_value;
    };

    explicit
    MergeSplitTreapImpl(_Comp __comp = {}, _MergeFunc __merge = {}) noexcept
        : _M_tree(1), _M_root(0), _M_comp(__comp), _M_merge(__merge)
    { }

    MergeSplitTreapImpl(std::initializer_list<value_type> __init, _Comp __comp = {}, _MergeFunc __merge = {}) noexcept
        : MergeSplitTreapImpl(__comp, __merge)
    { for (const auto& value : __init) { insert(value); } }

    template<std::input_iterator _Iter, std::sentinel_for<_Iter> _Sent, typename _Proj = std::identity>
    MergeSplitTreapImpl(_Iter __first, _Sent __last, _Proj __proj = {}, _Comp __comp = {}, _MergeFunc __merge = {}) noexcept
        : MergeSplitTreapImpl(__comp, __merge)
    { for (; __first != __last; ++__first) { insert(std::invoke(__proj, *__first)); } }

    template<std::ranges::input_range _Range, typename _Proj = std::identity>
    MergeSplitTreapImpl(_Range&& __r, _Proj __proj = {}, _Comp __comp = {}, _MergeFunc __merge = {}) noexcept
        : MergeSplitTreapImpl(__comp, __merge)
    { for (auto&& value : __r) { insert(std::invoke(__proj, value)); } }

    [[nodiscard]] size_type
    root() const noexcept
    { return _M_root; }

    constexpr void
    update_root(size_type __new_root) noexcept
    { _M_root = __new_root; }

    [[nodiscard]] size_type
    size() const noexcept
    { return _M_tree[root()].size; }

    void
    reserve(size_type __n) noexcept
    {
        _M_tree.reserve(1 + __n);

        if constexpr (requires() { static_cast<_Derived*>(this)->on_reserve(__n); })
        {
            static_cast<_Derived*>(this)->on_reserve(__n);
        }
    }

    [[nodiscard]] bool
    empty() const noexcept
    { return not size(); }

    void
    clear() noexcept
    {
        _M_tree.resize(1);
        update_root(size_type{});

        if constexpr (requires() { static_cast<_Derived*>(this)->on_clear(); })
        {
            static_cast<_Derived*>(this)->on_clear();
        }
    }

    [[nodiscard]] const node&
    node_at(size_type __i) const noexcept
    { return _M_tree[__i]; }

    void
    split_left_by_value(size_type u, const_reference value, size_type& rx, size_type& ry) noexcept
    {
        if (not u)
        {
            rx = ry = size_type{};
            return;
        }

        push_down(u);

        if (_M_comp(value, _M_tree[u].value))
        {
            ry = u;
            split_left_by_value(_M_tree[u].ls, value, rx, _M_tree[u].ls);
        }
        else
        {
            rx = u;
            split_left_by_value(_M_tree[u].rs, value, _M_tree[u].rs, ry);
        }

        push_up(u);
    }

    void
    split_right_by_value(size_type u, const_reference value, size_type& rx, size_type& ry) noexcept
    {
        if (not u)
        {
            rx = ry = size_type{};
            return;
        }

        push_down(u);

        if (_M_comp(_M_tree[u].value, value))
        {
            rx = u;
            split_right_by_value(_M_tree[u].rs, value, _M_tree[u].rs, ry);
        }
        else
        {
            ry = u;
            split_right_by_value(_M_tree[u].ls, value, rx, _M_tree[u].ls);
        }

        push_up(u);
    }

    void
    split_by_value(size_type u, const_reference value, size_type& rx, size_type& ry) noexcept
    { split_right_by_value(u, value, rx, ry); }

    void
    split_by_size(size_type u, size_type left_size, size_type& rx, size_type& ry) noexcept
    {
        if (not u)
        {
            rx = ry = size_type{};
            return;
        }

        push_down(u);

        if (left_size < _M_tree[_M_tree[u].ls].size + 1)
        {
            ry = u;
            split_by_size(_M_tree[u].ls, left_size, rx, _M_tree[u].ls);
        }
        else
        {
            rx = u;
            split_by_size(_M_tree[u].rs, left_size - _M_tree[_M_tree[u].ls].size - 1, _M_tree[u].rs, ry);
        }

        push_up(u);
    }

    size_type
    merge(size_type u, size_type v) noexcept
    {
        if (not u or not v)
        {
            return u | v;
        }

        if (_M_tree[u].priority > _M_tree[v].priority)
        {
            push_down(u);
            _M_tree[u].rs = merge(_M_tree[u].rs, v);
            push_up(u);
            return u;
        }
        else
        {
            push_down(v);
            _M_tree[v].ls = merge(u, _M_tree[v].ls);
            push_up(v);
            return v;
        }
    }

    void
    insert(const_reference __value) noexcept
    {
        size_type rx, ry;
        split_left_by_value(root(), __value, rx, ry);
        update_root(merge(merge(rx, create_node(__value)), ry));
    }

    void
    insert_before(size_type __pos, const_reference __value) noexcept
    {
        size_type rx, ry;
        split_by_size(root(), __pos, rx, ry);
        update_root(merge(merge(rx, create_node(__value)), ry));
    }

    bool
    remove(const_reference __value) noexcept
    {
        size_type rx, rm, ry;
        split_right_by_value(root(), __value, rx, rm);
        split_by_size(rm, 1, rm, ry);

        if (rm and not _M_comp(__value, _M_tree[rm].value))
        {
            update_root(merge(rx, ry));
            return true;
        }
        else
        {
            update_root(merge(merge(rx, rm), ry));
            return false;
        }
    }

    size_type
    remove_all(const_reference __value) noexcept
    {
        size_type rx, rm, ry;
        split_right_by_value(root(), __value, rx, rm);
        split_left_by_value(rm, __value, rm, ry);

        const size_type cnt = _M_tree[rm].size;

        update_root(merge(rx, ry));
        return cnt;
    }

    size_type
    remove_at(size_type __pos, size_type __n = 1)
    {
        size_type rx, rm, ry;
        split_by_size(root(), __pos, rx, rm);
        split_by_size(rm, __n, rm, ry);

        const size_type cnt = _M_tree[rm].size;

        update_root(merge(rx, ry));
        return cnt;
    }

    [[nodiscard]] const_reference
    find_by_order(size_type __rank) noexcept
    {
        size_type rx, rm, ry;
        split_by_size(root(), __rank, rx, rm);
        split_by_size(rm, 1, rm, ry);

        update_root(merge(merge(rx, rm), ry));
        return _M_tree[rm].value;
    }

    [[nodiscard]] size_type
    order_of_key(const_reference __value) noexcept
    {
        size_type rx, ry;
        split_right_by_value(root(), __value, rx, ry);

        const size_type rank = _M_tree[rx].size;

        update_root(merge(rx, ry));
        return rank;
    }

    [[nodiscard]] const_reference
    front() noexcept
    { return find_by_order(0); }

    [[nodiscard]] const_reference
    back() noexcept
    { return find_by_order(size() - 1); }

    [[nodiscard]] value_type
    reduce(size_type __pos, size_type __n) noexcept
    {
        size_type rx, rm, ry;
        split_by_size(root(), __pos, rx, rm);
        split_by_size(rm, __n, rm, ry);

        const value_type value = _M_tree[rm].reduced_value;

        update_root(merge(merge(rx, rm), ry));
        return value;
    }

    [[nodiscard]] value_type
    reduce() const noexcept
    { return _M_tree[root()].reduced_value; }

    [[nodiscard]] const_reference
    lower_bound(const_reference __value, bool* __found = nullptr) noexcept
    {
        size_type rx, rm, ry;
        split_right_by_value(root(), __value, rx, rm);
        split_by_size(rm, 1, rm, ry);

        if (__found)
        {
            *__found = static_cast<bool>(rm);
        }

        update_root(merge(merge(rx, rm), ry));
        return _M_tree[rm].value;
    }

    [[nodiscard]] const_reference
    upper_bound(const_reference __value, bool* __found = nullptr) noexcept
    {
        size_type rx, rm, ry;
        split_left_by_value(root(), __value, rx, rm);
        split_by_size(rm, 1, rm, ry);

        if (__found)
        {
            *__found = static_cast<bool>(rm);
        }

        update_root(merge(merge(rx, rm), ry));
        return _M_tree[rm].value;
    }

    struct equal_range_result
    {
        size_type pos;
        size_type len;
    };

    [[nodiscard]] equal_range_result
    equal_range(const_reference __value) noexcept
    {
        size_type rx, rm, ry;
        split_right_by_value(root(), __value, rx, rm);
        split_left_by_value(rm, __value, rm, ry);

        const equal_range_result result{_M_tree[rx].size, _M_tree[rm].size};

        update_root(merge(merge(rx, rm), ry));
        return result;
    }

    [[nodiscard]] size_type
    count(const_reference __value) noexcept
    { return equal_range(__value).len; }

    [[nodiscard]] bool
    contains(const_reference __value) noexcept
    { return static_cast<bool>(equal_range(__value).len); }

    template<typename _Func>
    void
    for_each(size_type __pos, size_type __n, _Func __func) noexcept
    {
        size_type rx, rm, ry;
        split_by_size(root(), __pos, rx, rm);
        split_by_size(rm, __n, rm, ry);

        inorder(rm, __func);
        update_root(merge(merge(rx, rm), ry));
    }

    template<typename _Func>
    void
    for_each(_Func __func) noexcept
    { inorder(root(), __func); }

    template<template<typename...> typename _Container>
    _Container<value_type>
    flatten() noexcept
    {
        _Container<value_type> result;
        for_each([&](const_reference value) -> void { result.push_back(value); });
        return result;
    }

protected:

    [[nodiscard]] static size_type
    generate_priority() noexcept
    {
        static std::mt19937 rng(std::random_device{}() ^ std::chrono::steady_clock::now().time_since_epoch().count());
        return rng();
    }

    size_type
    create_node(const value_type& __value) noexcept
    {
        _M_tree.emplace_back(0, 0, generate_priority(), 1, __value, __value);

        if constexpr (requires() { static_cast<_Derived*>(this)->on_create_node(__value); })
        {
            static_cast<_Derived*>(this)->on_create_node(__value);
        }

        return size_type(_M_tree.size()) - 1;
    }

    [[nodiscard]] node&
    node_at(size_type __i) noexcept
    { return _M_tree[__i]; }

    void
    push_up(size_type u) noexcept
    {
        _M_tree[u].size = _M_tree[_M_tree[u].ls].size + 1 + _M_tree[_M_tree[u].rs].size;

        _M_tree[u].reduced_value = _M_tree[u].value;

        if (_M_tree[u].ls)
        {
            _M_tree[u].reduced_value = _M_merge(_M_tree[_M_tree[u].ls].reduced_value, _M_tree[u].reduced_value);
        }

        if (_M_tree[u].rs)
        {
            _M_tree[u].reduced_value = _M_merge(_M_tree[u].reduced_value, _M_tree[_M_tree[u].rs].reduced_value);
        }
    }

    void
    push_down(size_type u) noexcept
    {
        if constexpr (requires() { static_cast<_Derived*>(this)->on_push_down(u); })
        {
            static_cast<_Derived*>(this)->on_push_down(u);
        }
    }

    template<typename _Func>
    void
    inorder(size_type u, _Func&& f) noexcept
    {
        if (u)
        {
            push_down(u);
            inorder(_M_tree[u].ls, std::forward<_Func>(f));
            std::invoke(f, _M_tree[u].value);
            inorder(_M_tree[u].rs, std::forward<_Func>(f));
        }
    }

private:

    std::vector<node> _M_tree;
    size_type _M_root;

protected:

    [[no_unique_address]] _Comp _M_comp;
    [[no_unique_address]] _MergeFunc _M_merge;
};

template<
    typename _Tp,
    typename _Comp = std::ranges::less,
    typename _MergeFunc = decltype([](const _Tp& lhs, const _Tp&) -> _Tp { return lhs; })>
requires std::convertible_to<std::invoke_result_t<_MergeFunc, _Tp, _Tp>, _Tp>
class MergeSplitTreap : public MergeSplitTreapImpl<MergeSplitTreap<_Tp, _Comp, _MergeFunc>, _Tp, _Comp, _MergeFunc>
{
public:
    using Base = MergeSplitTreapImpl<MergeSplitTreap<_Tp, _Comp, _MergeFunc>, _Tp, _Comp, _MergeFunc>;
    using Base::Base;
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

    int n, m, q;
    std::cin >> n >> m >> q;

    std::vector<int> a(n + 1);

    for (int i = 1; i <= n; ++i)
    {
        std::cin >> a[i];
    }

    std::vector<std::tuple<int, int, int>> e(m);

    for (auto& [u, v, w] : e)
    {
        std::cin >> u >> v >> w;
    }

    std::ranges::sort(e, {}, [](const auto& t) { return std::get<2>(t); });

    std::vector<std::array<int, 2>> bt(n + m + 1);

    std::vector<int> weight(n + m + 1);
    std::vector<int> depth(n + m + 1);

    std::vector<int> dfn(n + 1);
    std::vector<int> map(n + 1);

    DisjointSet dsu(n + m + 1);

    constexpr int laycnt = 20;
    std::vector<std::array<int, laycnt>> parent(dsu.size());

    for (int id = n; const auto& [u, v, w] : e)
    {
        if (not dsu.connected(u, v))
        {
            ++id;

            weight[id] = w;
            bt[id] = {dsu.find(u), dsu.find(v)};
            parent[dsu.find(u)][0] = parent[dsu.find(v)][0] = id;

            dsu.unite(id, u);
            dsu.unite(id, v);
        }
    }

    for (int i = 1; i < laycnt; ++i)
    {
        for (int u = 1; u <= n + m; ++u)
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

    auto dfs = [&, id = 0](auto& self, int u) mutable -> void
    {
        if (u >= 1 and u <= n)
        {
            dfn[u] = ++id;
            map[id] = u;
        }

        for (int v : bt[u])
        {
            if (v)
            {
                depth[v] = depth[u] + 1;
                self(self, v);
            }
        }
    };

    dfs(dfs, dsu.find(1));

    struct item
    {
        int id;
        int value;

        int mindfn;
        int maxdfn;
    };

    MergeSplitTreap<
        item,
        decltype([](const item& lhs, const item& rhs) -> bool
        {
            if (lhs.value != rhs.value)
            {
                return lhs.value > rhs.value;
            }
            else
            {
                return lhs.id < rhs.id;
            }
        }),
        decltype([](const item& lhs, const item& rhs) -> item
        {
            item result;
            result.mindfn = std::min(lhs.mindfn, rhs.mindfn);
            result.maxdfn = std::max(lhs.maxdfn, rhs.maxdfn);
            return result;
        })> set;

    for (int i = 1; i <= n; ++i)
    {
        set.insert({i, a[i], dfn[i], dfn[i]});
    }

    while (q--)
    {
        int op;
        std::cin >> op;

        if (op == 1)
        {
            int c, t;
            std::cin >> c >> t;

            set.remove({c, a[c], dfn[c], dfn[c]});
            a[c] = t;
            set.insert({c, a[c], dfn[c], dfn[c]});
        }
        else
        {
            int k;
            std::cin >> k;

            const auto result = set.reduce(0, k);
            std::cout << weight[lca(map[result.mindfn], map[result.maxdfn])] << '\n';
        }
    }

    return 0;
}
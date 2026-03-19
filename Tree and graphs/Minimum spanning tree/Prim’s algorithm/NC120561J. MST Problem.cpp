/**
 * 2026牛客寒假算法基础集训营1
 * 
 * => J-MST Problem ( @c 3000 )
 * 
 * -> https://ac.nowcoder.com/acm/contest/120561/J
 * 
 * Submissions ~> https://ac.nowcoder.com/acm/contest/view-submission?submissionId=82104586 By huanhuanonly
 * 
 * @b Prim’s-algorithm and @b Segment-tree
 * 
 * ----February 06, 2026 [20h:37m:02s]----
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

inline namespace huanhuanonly
{
template<typename _ValueType, typename _MergeFunc = std::plus<_ValueType>>
class SegmentTree
{
public:

    using container_type = std::vector<std::conditional_t<std::is_same_v<_ValueType, bool>, std::uint8_t, _ValueType>>;

    using value_type = container_type::value_type;
    using reference = container_type::reference;
    using const_reference = container_type::const_reference;
    using size_type = std::size_t;

    constexpr explicit
    SegmentTree(size_type __n = 0, _MergeFunc __merge = {}) noexcept
        : tree(nodes_count(__n)), merge(__merge)
    { }

    template<std::input_iterator _Iter, std::sentinel_for<_Iter> _Sent, typename _Proj = std::identity>
    constexpr
    SegmentTree(_Iter __first, _Sent __last, _Proj __proj = {}, _MergeFunc __merge = {}) noexcept
        : tree(nodes_count(static_cast<size_type>(std::ranges::distance(__first, __last)))), merge(__merge)
    { build(__first, __last, __proj); }

    template<std::ranges::input_range _Range, typename _Proj = std::identity>
    constexpr
    SegmentTree(_Range&& __r, _Proj __proj = {}, _MergeFunc __merge = {}) noexcept
        : SegmentTree(std::ranges::begin(__r), std::ranges::end(__r), __proj, __merge)
    { }

    constexpr
    SegmentTree(std::initializer_list<_ValueType> __list) noexcept
        : SegmentTree(__list.begin(), __list.end())
    { }


    [[nodiscard]] static constexpr size_type
    nodes_count(size_type __n) noexcept
    { return __n << 2; }

    [[nodiscard]] constexpr size_type
    nodes_count() const noexcept
    { return tree.size(); }

    [[nodiscard]] constexpr size_type
    size() const noexcept
    { return static_cast<size_type>(tree.size()) >> 2; }

    [[nodiscard]] constexpr bool
    empty() const noexcept
    { return size() == 0; }

    constexpr void
    resize(size_type __n)
    { tree.resize(nodes_count(__n)); }

    
    template<typename _Callback>
    requires std::invocable<_Callback, reference>
    constexpr void
    for_each(size_type __l, size_type __r, _Callback __func)
    { _M_for_each(1, 1, size(), __l + 1, __r + 1, __func); }
    
    template<typename _Callback>
    requires std::invocable<_Callback, reference>
    constexpr void
    for_each(_Callback __func)
    { empty() ? void() : for_each(0, size() - 1, __func); }

    template<typename _Callback>
    requires std::invocable<_Callback, reference>
    constexpr void
    for_each_segment(size_type __l, size_type __r, _Callback __func)
    { _M_for_each_segment(1, 1, size(), __l + 1, __r + 1, __func); }
    
    template<typename _Callback>
    requires std::invocable<_Callback, reference>
    constexpr void
    for_each_segment(_Callback __func)
    { empty() ? void() : for_each_segment(0, size() - 1, __func); }


    template<std::input_iterator _Iter, std::sentinel_for<_Iter> _Sent, typename _Proj = std::identity>
    requires std::assignable_from<value_type&, std::invoke_result_t<_Proj, std::iter_reference_t<_Iter>>>
    constexpr void
    build(size_type __l, size_type __r, _Iter __first, _Sent __last, _Proj __proj = {})
    {
        if (__first != __last)
        {
            for_each(__l, __r, [&](reference __ref) -> bool
            {
                __ref = std::invoke(__proj, *__first);
                return ++__first != __last;
            });
        }
    }

    template<std::ranges::input_range _Range, typename _Proj = std::identity>
    requires std::assignable_from<reference, std::invoke_result_t<_Proj, std::ranges::range_reference_t<_Range>>>
    constexpr void
    build(size_type __l, size_type __r, _Range&& __range, _Proj __proj = {})
    { build(__l, __r, std::ranges::begin(__range), std::ranges::end(__range), __proj); }
    
    template<std::input_iterator _Iter, std::sentinel_for<_Iter> _Sent, typename _Proj = std::identity>
    requires std::assignable_from<reference, std::invoke_result_t<_Proj, std::iter_reference_t<_Iter>>>
    constexpr void
    build(_Iter __first, _Sent __last, _Proj __proj = {})
    { empty() ? void() : build(0, size() - 1, __first, __last, __proj); }

    template<std::ranges::input_range _Range, typename _Proj = std::identity>
    requires std::assignable_from<reference, std::invoke_result_t<_Proj, std::ranges::range_reference_t<_Range>>>
    constexpr void
    build(_Range&& __range, _Proj __proj = {})
    { build(std::ranges::begin(__range), std::ranges::end(__range), __proj); }


    template<typename _Iter, typename _Proj = std::identity>
    requires std::output_iterator<_Iter, std::invoke_result_t<_Proj, const_reference>>
    constexpr void
    flatten(size_type __l, size_type __r, _Iter __first, _Proj __proj = {})
    { for_each(__l, __r, [&](const_reference __ref) -> bool { *__first = std::invoke(__proj, __ref); ++__first; return true; }); }


    [[nodiscard]] constexpr value_type
    reduce(size_type __l, size_type __r)
    { return _M_reduce(1, 1, size(), __l + 1, __r + 1); }

    [[nodiscard]] constexpr value_type
    reduce()
    { return empty() ? value_type{} : reduce(0, size() - 1); }

    [[nodiscard]] constexpr const_reference
    at(size_type __p)
    { return _M_at(1, 1, size(), __p + 1); }

    [[nodiscard]] constexpr const_reference
    operator[](size_type __p)
    { return at(__p); }

    [[nodiscard]] constexpr value_type
    operator[](const std::pair<size_type, size_type>& __p)
    { return reduce(__p.first, __p.second); }
    

    [[nodiscard]] constexpr const_reference
    front()
    { return at(0); }
    
    [[nodiscard]] constexpr const_reference
    back()
    { return at(size() - 1); }


    template<typename _Tp, typename _Proj = std::identity>
    requires std::assignable_from<reference, std::invoke_result_t<_Proj, const _Tp&>>
    constexpr void
    set(size_type __l, size_type __r, const _Tp& __value, _Proj __proj = {})
    { for_each(__l, __r, [&](reference __ref) -> bool { __ref = std::invoke(__proj, __value); return true; }); }

    template<typename _Tp, typename _Proj = std::identity>
    requires std::assignable_from<reference, std::invoke_result_t<_Proj, const _Tp&>>
    constexpr void
    set(size_type __p, const _Tp& __value, _Proj __proj = {})
    { set(__p, __p, __value, __proj); }

    template<typename _Tp, typename _Proj = std::identity>
    requires std::assignable_from<reference, std::invoke_result_t<_Proj, const _Tp&>>
    constexpr void
    fill(const _Tp& __value, _Proj __proj = {})
    { empty() ? void() : set(0, size() - 1, __value, __proj); }

    constexpr void
    reset()
    { std::ranges::fill(tree, value_type{}); }

protected:

    [[nodiscard]] static constexpr size_type
    ls(size_type __p) noexcept
    { return __p << 1; }

    [[nodiscard]] static constexpr size_type
    rs(size_type __p) noexcept
    { return __p << 1 | 1; }

    constexpr void
    push_up(size_type __p)
    { tree[__p] = merge(tree[ls(__p)], tree[rs(__p)]); }

    virtual void
    push_down(size_type __p, size_type __l, size_type __r)
    { }

private:

    template<typename _Callback>
    requires std::invocable<_Callback, reference>
    constexpr bool
    _M_for_each(size_type __p, size_type __l, size_type __r, size_type __x, size_type __y, _Callback&& __func)
    {
        if (__l == __r)
        {
            return __func(tree[__p]);
        }

        push_down(__p, __l, __r);

        const size_type mid = __l + __r >> 1;
        bool continues = true;

        if (__x <= mid)
        {
            continues = _M_for_each(ls(__p), __l, mid, __x, __y, std::forward<_Callback>(__func));
        }

        if (__y > mid and continues)
        {
            continues = _M_for_each(rs(__p), mid + 1, __r, __x, __y, std::forward<_Callback>(__func));
        }

        push_up(__p);

        return continues;
    }

    template<typename _Callback>
    requires std::invocable<_Callback, reference>
    constexpr bool
    _M_for_each_segment(size_type __p, size_type __l, size_type __r, size_type __x, size_type __y, _Callback&& __func)
    {
        if (__x <= __l and __r <= __y)
        {
            return __func(tree[__p]);
        }

        push_down(__p, __l, __r);

        const size_type mid = __l + __r >> 1;
        bool continues = true;

        if (__x <= mid)
        {
            continues = _M_for_each_segment(ls(__p), __l, mid, __x, __y, std::forward<_Callback>(__func));
        }

        if (__y > mid and continues)
        {
            continues = _M_for_each_segment(rs(__p), mid + 1, __r, __x, __y, std::forward<_Callback>(__func));
        }

        return continues;
    }

    [[nodiscard]] constexpr value_type
    _M_reduce(size_type __p, size_type __l, size_type __r, size_type __x, size_type __y)
    {
        if (__x <= __l and __r <= __y)
        {
            return tree[__p];
        }

        push_down(__p, __l, __r);

        const size_type mid = __l + __r >> 1;

        if (__x <= mid and __y > mid)
        {
            return merge(_M_reduce(ls(__p), __l, mid, __x, __y), _M_reduce(rs(__p), mid + 1, __r, __x, __y));
        }
        else if (__x <= mid)
        {
            return _M_reduce(ls(__p), __l, mid, __x, __y);
        }
        else
        {
            return _M_reduce(rs(__p), mid + 1, __r, __x, __y);
        }
    }

    [[nodiscard]] constexpr const_reference
    _M_at(size_type __p, size_type __l, size_type __r, size_type __i)
    {
        if (__l == __r)
        {
            return tree[__p];
        }

        push_down(__p, __l, __r);

        const size_type mid = __l + __r >> 1;

        if (__i <= mid)
        {
            return _M_at(ls(__p), __l, mid, __i);
        }
        else
        {
            return _M_at(rs(__p), mid + 1, __r, __i);
        }
    }

protected:

    container_type tree;
    _MergeFunc merge;
};

template<std::input_iterator _Iter, std::sentinel_for<_Iter> _Sent, typename _Proj = std::identity, typename _MergeFunc = std::plus<>>
SegmentTree(_Iter, _Sent, _Proj = {}, _MergeFunc = {}) -> SegmentTree<std::remove_reference_t<std::invoke_result_t<_Proj, std::iter_value_t<_Iter>>>, _MergeFunc>;

template<std::ranges::input_range _Range, typename _Proj = std::identity, typename _MergeFunc = std::plus<>>
SegmentTree(_Range&&, _Proj = {}, _MergeFunc = {}) -> SegmentTree<std::remove_reference_t<std::invoke_result_t<_Proj, std::ranges::range_value_t<_Range>>>, _MergeFunc>;
}

inline namespace huanhuanonly
{
struct MakeLazyFunc
{
    struct Add
    {
        constexpr void
        operator()(const auto& that, const auto& value) const noexcept
        {
            that.value += value;
            that.lazy  += value;
        }
    };

    struct RangeAdd
    {
        constexpr void
        operator()(const auto& that, const auto& value) const noexcept
        {
            that.value += value * that.size;
            that.lazy  += value;
        }
    };

    struct Assign
    {
        constexpr void
        operator()(const auto& that, const auto& value) const noexcept
        {
            that.value = value;
            that.lazy  = value;
        }
    };

    struct Merge
    {
        constexpr void
        operator()(const auto& that, const auto& value) const noexcept
        {
            that.value = that.merge(that.value, value);

            if (that.marked)
                that.lazy = that.merge(that.lazy, value);
            else
                that.lazy = value;
        }
    };
};

template<
    typename _ValueType, typename _MergeFunc = std::plus<_ValueType>,
    typename _LazyType = _ValueType, typename _MakeLazyFunc = MakeLazyFunc::RangeAdd>
class LazySegmentTree : public SegmentTree<_ValueType, _MergeFunc>
{
public:

    using parent_type     = SegmentTree<_ValueType, _MergeFunc>;

    using container_type  = parent_type::container_type;
    using value_type      = parent_type::value_type;
    using lazy_type       = std::conditional_t<std::is_same_v<_ValueType, bool>, std::uint8_t, _LazyType>;
    using reference       = parent_type::reference;
    using const_reference = parent_type::const_reference;
    using size_type       = parent_type::size_type;

    using parent_type::size;
    using parent_type::nodes_count;
    
    struct lazy_build_info
    {
        value_type& value;
        lazy_type&  lazy;
        _MergeFunc& merge;

        size_type size;
        bool marked;
    };

protected:

    using parent_type::ls;
    using parent_type::rs;

    using parent_type::push_up;

    using parent_type::tree;
    using parent_type::merge;

public:
    
    constexpr explicit
    LazySegmentTree(size_type __n = 0, _MergeFunc __merge = {}, _MakeLazyFunc __makelazy = {}) noexcept
        : parent_type(__n, __merge), lazy(tree.size()), marked(tree.size()), make_lazy_func(__makelazy)
    { }

    template<std::input_iterator _Iter, std::sentinel_for<_Iter> _Sent, typename _Proj = std::identity>
    constexpr
    LazySegmentTree(_Iter __first, _Sent __last, _Proj __proj = {}, _MergeFunc __merge = {}, _MakeLazyFunc __makelazy = {}) noexcept
        : parent_type(__first, __last, __proj, __merge), lazy(tree.size()), marked(tree.size()), make_lazy_func(__makelazy)
    { }

    template<std::ranges::input_range _Range, typename _Proj = std::identity>
    constexpr
    LazySegmentTree(_Range&& __r, _Proj __proj = {}, _MergeFunc __merge = {}, _MakeLazyFunc __makelazy = {}) noexcept
        : parent_type(std::ranges::begin(__r), std::ranges::end(__r), __proj, __merge), lazy(tree.size()), marked(tree.size()), make_lazy_func(__makelazy)
    { }

    constexpr
    LazySegmentTree(std::initializer_list<_ValueType> __list) noexcept
        : LazySegmentTree(__list.begin(), __list.end())
    { }


    constexpr void
    range_update(size_type __l, size_type __r, const lazy_type& __value)
    { _M_range_update(1, 1, size(), __l + 1, __r + 1, __value); }
    
    constexpr void
    resize(size_type __n)
    {
        parent_type::resize(__n);
        lazy.resize(nodes_count(__n));
        marked.resize(nodes_count(__n));
    }

    constexpr void
    reset()
    {
        parent_type::reset();
        std::ranges::fill(lazy, lazy_type{});
        marked.assign(marked.size(), false);
    }

protected:

    constexpr void
    make_lazy(size_type __p, size_type __l, size_type __r, const lazy_type& __value)
    {
        make_lazy_func(lazy_build_info{
            .value  = tree[__p],
            .lazy   = lazy[__p],
            .merge  = merge,
            .size   = __r - __l + 1,
            .marked = marked[__p]
        }, __value);

        marked[__p] = true;
    }

    void
    push_down(size_type __p, size_type __l, size_type __r) override
    {
        if (marked[__p])
        {
            const size_type mid = (__l + __r) >> 1;

            make_lazy(ls(__p), __l, mid, lazy[__p]);
            make_lazy(rs(__p), mid + 1, __r, lazy[__p]);
            
            lazy[__p] = lazy_type{};
            marked[__p] = false;
        }
    }

private:

    constexpr void
    _M_range_update(size_type __p, size_type __l, size_type __r, size_type __x, size_type __y, const lazy_type& __v)
    {
        if (__x <= __l and __r <= __y)
        {
            make_lazy(__p, __l, __r, __v);
            return;
        }

        push_down(__p, __l, __r);

        size_type mid = (__l + __r) >> 1;

        if (__x <= mid)
        {
            _M_range_update(ls(__p), __l, mid, __x, __y, __v);
        }

        if (__y > mid)
        {
            _M_range_update(rs(__p), mid + 1, __r, __x, __y, __v);
        }
        
        push_up(__p);
    }

protected:

    std::vector<lazy_type> lazy;
    std::vector<bool> marked;

    _MakeLazyFunc make_lazy_func;
};

template<std::input_iterator _Iter, std::sentinel_for<_Iter> _Sent, typename _Proj = std::identity, typename _MergeFunc = std::plus<>, typename _MakeLazyFunc = MakeLazyFunc::RangeAdd>
LazySegmentTree(_Iter, _Sent, _Proj = {}, _MergeFunc = {}, _MakeLazyFunc = {}) -> LazySegmentTree<std::remove_reference_t<std::invoke_result_t<_Proj, std::iter_value_t<_Iter>>>, _MergeFunc, std::remove_reference_t<std::invoke_result_t<_Proj, std::iter_value_t<_Iter>>>, _MakeLazyFunc>;

template<std::ranges::input_range _Range, typename _Proj = std::identity, typename _MergeFunc = std::plus<>, typename _MakeLazyFunc = MakeLazyFunc::RangeAdd>
LazySegmentTree(_Range&&, _Proj = {}, _MergeFunc = {}, _MakeLazyFunc = {}) -> LazySegmentTree<std::remove_reference_t<std::invoke_result_t<_Proj, std::ranges::range_value_t<_Range>>>, _MergeFunc, std::remove_reference_t<std::invoke_result_t<_Proj, std::ranges::range_value_t<_Range>>>, _MakeLazyFunc>;
}

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
    
        constexpr auto inf = std::numeric_limits<uint64>::max() / 2;

        std::vector w(n + 1, inf);
    
        for (int i = 1; i <= n; ++i)
        {
            std::cin >> w[i];
        }
    
        std::vector e(n + 1, std::vector<int>{});
    
        for (int i = 0; i < m; ++i)
        {
            int u, v;
            std::cin >> u >> v;
    
            e[u].push_back(v);
            e[v].push_back(u);
        }

        for (int i = 1; i <= n; ++i)
        {
            e[i].push_back(0);
            e[i].push_back(n + 1);

            std::ranges::sort(e[i]);
        }

        struct node
        {
            std::pair<uint64, int> cmin;
            std::pair<uint64, int> rmin;

            node operator+(const node& other) const noexcept
            {
                return node{
                    .cmin = std::min(cmin, other.cmin),
                    .rmin = std::min(rmin, other.rmin)
                };
            }
        };

        using make_lazy = decltype([](const auto& that, const auto& value) -> void
        {
            auto rmin = that.value.rmin;
            rmin.first += value;

            that.value.cmin = std::min(that.value.cmin, rmin);

            if (that.marked)
            {
                that.lazy = std::min(that.lazy, value);
            }
            else
            {
                that.lazy = value;
            }
        });

        LazySegmentTree<node, std::plus<node>, uint64, make_lazy> seg(n + 1);

        seg.build(std::views::iota(0), [&](int i) -> node
        {
            return node{
                .cmin = {inf, inf},
                .rmin = {w[i], i}
            };
        });

        bool connected = true;

        uint64 ans = 0;

        for (int cnt = 0, u = 1; cnt < n - 1; ++cnt)
        {
            for (int i = 1; i < e[u].size(); ++i)
            {
                if (e[u][i - 1] + 1 <= e[u][i] - 1)
                {
                    seg.range_update(e[u][i - 1] + 1, e[u][i] - 1, w[u]);
                }
            }
            
            seg.for_each(u, u, [](node& nd) -> bool
            {
                nd.rmin.first = nd.cmin.first = inf;
                return false;
            });

            node&& nd = seg.reduce();

            if (nd.cmin.first == inf)
            {
                connected = false;
                break;
            }

            ans += nd.cmin.first;
            u = nd.cmin.second;
        }

        if (connected)
        {
            std::cout << ans << '\n';
        }
        else
        {
            std::cout << -1 << '\n';
        }
    }

    return 0;
}
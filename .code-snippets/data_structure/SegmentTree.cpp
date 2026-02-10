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
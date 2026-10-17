template<typename _ValueType, typename _MergeFunc = std::plus<_ValueType>>
class SegmentTree
{
public:

    using container_type =
        std::vector<std::conditional_t<std::is_same_v<_ValueType, bool>, std::uint8_t, _ValueType>>;

    using value_type = container_type::value_type;
    using reference = container_type::reference;
    using const_reference = container_type::const_reference;
    using size_type = std::size_t;

    constexpr explicit
    SegmentTree(size_type __n = 0, _MergeFunc __merge = {}) noexcept
        : tree(storage_size(__n)), merge(std::move(__merge))
    { }

    template<std::forward_iterator _Iter, std::sentinel_for<_Iter> _Sent, typename _Proj = std::identity>
    constexpr
    SegmentTree(_Iter __first, _Sent __last, _Proj __proj = {}, _MergeFunc __merge = {}) noexcept
        : tree(storage_size(static_cast<size_type>(std::ranges::distance(__first, __last))))
        , merge(std::move(__merge))
    { build(std::move(__first), std::move(__last), std::move(__proj)); }

    template<std::ranges::forward_range _Range>
    constexpr
    SegmentTree(_Range&& __r, _MergeFunc __merge = {}) noexcept
        : SegmentTree(std::ranges::begin(__r), std::ranges::end(__r), {}, std::move(__merge))
    { }

    constexpr
    SegmentTree(std::initializer_list<_ValueType> __list) noexcept
        : SegmentTree(__list.begin(), __list.end())
    { }

    virtual ~SegmentTree() = default;

    [[nodiscard]] static constexpr size_type
    storage_size(size_type __n) noexcept
    { return __n << 2; }

    [[nodiscard]] constexpr size_type
    storage_size() const noexcept
    { return tree.size(); }

    [[nodiscard]] constexpr size_type
    size() const noexcept
    { return static_cast<size_type>(tree.size()) >> 2; }

    [[nodiscard]] constexpr bool
    empty() const noexcept
    { return size() == 0; }

    virtual constexpr void
    resize(size_type __n)
    {
        if (__n == size())
        {
            return;
        }

        if (__n)
        {
            auto&& c = size() < __n ? to<std::vector<value_type>>() : to<std::vector<value_type>>(0, __n - 1);
            tree.resize(storage_size(__n));
            build(c);

            if (static_cast<size_type>(c.size()) < __n)
            {
                range_set(c.size(), __n - 1, value_type{});
            }
        }
        else
        {
            tree.clear();
        }
    }

    constexpr void
    fill(const value_type& __value)
    { empty() ? void() : range_set(0, size() - 1, __value); }

    virtual constexpr void
    reset()
    { std::ranges::fill(tree, value_type{}); }


    template<typename _Callback>
    requires std::invocable<_Callback&, reference>
    constexpr void
    for_each(size_type __l, size_type __r, _Callback __func)
    {
        assert(__l <= __r and 0 <= __l and __r < size());
        _M_for_each(1, 0, size() - 1, __l, __r, std::move(__func));
    }

    template<typename _Callback>
    requires std::invocable<_Callback&, reference>
    constexpr void
    for_each(_Callback __func)
    { empty() ? void() : for_each(0, size() - 1, std::move(__func)); }

    template<typename _Callback>
    requires std::invocable<_Callback&, const_reference>
    constexpr void
    for_each_cover_node(size_type __l, size_type __r, _Callback __func)
    {
        assert(__l <= __r and 0 <= __l and __r < size());
        _M_for_each_cover_node(1, 0, size() - 1, __l, __r, std::move(__func));
    }

    template<typename _Callback>
    requires std::invocable<_Callback&, const_reference>
    constexpr void
    for_each_cover_node(_Callback __func)
    { empty() ? void() : for_each_cover_node(0, size() - 1, std::move(__func)); }


    template<std::input_iterator _Iter, std::sentinel_for<_Iter> _Sent, typename _Proj = std::identity>
    requires std::assignable_from<value_type&, std::invoke_result_t<_Proj&, std::iter_reference_t<_Iter>>>
    constexpr void
    build(_Iter __first, _Sent __last, _Proj __proj = {}, size_type __l = 0)
    {
        if (__first != __last)
        {
            for_each(__l, size() - 1, [&](reference __ref) -> bool
            {
                __ref = std::invoke(__proj, *__first);
                return ++__first != __last;
            });
        }
    }

    template<std::ranges::input_range _Range>
    constexpr void
    build(_Range&& __range, size_type __l = 0)
    { build(std::ranges::begin(__range), std::ranges::end(__range), {}, __l); }


    template<typename _Container, typename _Proj = std::identity>
    requires
        std::default_initializable<_Container> and
        std::invocable<_Proj&, const_reference> and
        std::constructible_from<
            typename _Container::value_type,
            std::invoke_result_t<_Proj&, const_reference>>
    [[nodiscard]] constexpr _Container
    to(size_type __l, size_type __r, _Proj __proj = {})
    {
        _Container c;

        if constexpr (requires { c.reserve(size_type{}); })
        {
            c.reserve(__r - __l + 1);
        }

        for_each(__l, __r, [&](const_reference __ref) -> bool
        {
            if constexpr (requires { c.emplace_back(std::invoke(__proj, __ref)); })
            {
                c.emplace_back(std::invoke(__proj, __ref));
            }
            else if constexpr (requires { c.emplace(std::invoke(__proj, __ref)); })
            {
                c.emplace(std::invoke(__proj, __ref));
            }
            else if constexpr (requires { c.emplace(c.end(), std::invoke(__proj, __ref)); })
            {
                c.emplace(c.end(), std::invoke(__proj, __ref));
            }
            else
            {
                static_assert(false);
            }

            return true;
        });

        return c;
    }

    template<typename _Container, typename _Proj = std::identity>
    [[nodiscard]] constexpr auto
    to(_Proj __proj = {}) -> decltype(to<_Container>(size_type{}, size_type{}, std::move(__proj)))
    { return empty() ? _Container{} : to<_Container>(0, size() - 1, std::move(__proj)); }


    [[nodiscard]] constexpr value_type
    reduce(size_type __l, size_type __r)
    {
        value_type result{};
        bool init = true;

        for_each_cover_node(__l, __r, [&](const_reference value) -> void
        {
            if (init)
            {
                result = value;
                init = false;
            }
            else
            {
                result = merge(std::move(result), value);
            }
        });

        return result;
    }

    [[nodiscard]] constexpr value_type
    reduce() const
    { return empty() ? value_type{} : tree[1]; }

    [[nodiscard]] constexpr const_reference
    all() const noexcept
    { assert(not empty()); return tree[1]; }

    [[nodiscard]] constexpr const_reference
    at(size_type __p)
    { assert(0 <= __p and __p < size()); return _M_at(1, 0, size() - 1, __p); }

    [[nodiscard]] constexpr const_reference
    operator[](size_type __p)
    { return at(__p); }

    [[nodiscard]] constexpr const_reference
    front()
    { return at(0); }

    [[nodiscard]] constexpr const_reference
    back()
    { return at(size() - 1); }


    struct recursion_context_probe
    {
        size_type l, r;

        [[nodiscard]] constexpr bool
        is_leaf() const noexcept;

        [[nodiscard]] constexpr size_type
        size() const noexcept;

        [[nodiscard]] constexpr const_reference
        left_value() const noexcept;

        [[nodiscard]] constexpr const_reference
        right_value() const noexcept;

        struct return_placeholder
        {
            template<typename _Tp>
            constexpr operator _Tp() const noexcept;
        };

        template<typename... _Args>
        [[nodiscard]] constexpr return_placeholder
        to_left(_Args&&...) const;

        template<typename... _Args>
        [[nodiscard]] constexpr return_placeholder
        to_right(_Args&&...) const;
    };

    template<typename _Func, typename... _Args>
    struct recursion_context
    {
    private: size_type p;
    public:  size_type l, r;

    public:  SegmentTree* const that;

    private:

        _Func& func;

        constexpr
        recursion_context(size_type __p, size_type __l, size_type __r, SegmentTree* __that, _Func& __func) noexcept
            : p(__p), l(__l), r(__r), that(__that), func(__func)
        { }

    public:

        friend class SegmentTree;

        [[nodiscard]] constexpr bool
        is_leaf() const noexcept
        { return l == r; }

        [[nodiscard]] constexpr size_type
        size() const noexcept
        { return r - l + 1; }

        [[nodiscard]] constexpr const_reference
        left_value() const noexcept
        { assert(not is_leaf()); return that->tree[ls(p)]; }

        [[nodiscard]] constexpr const_reference
        right_value() const noexcept
        { assert(not is_leaf()); return that->tree[rs(p)]; }

        template<typename... _NextArgs>
        constexpr decltype(auto)
        to_left(_NextArgs&&... __args) const
        {
            assert(not is_leaf());
            const size_type mid = (l + r) >> 1;
            return func(recursion_context(ls(p), l, mid, that, func), std::forward<_NextArgs>(__args)...);
        }

        template<typename... _NextArgs>
        constexpr decltype(auto)
        to_right(_NextArgs&&... __args) const
        {
            assert(not is_leaf());
            const size_type mid = (l + r) >> 1;
            return func(recursion_context(rs(p), mid + 1, r, that, func), std::forward<_NextArgs>(__args)...);
        }
    };

    template<typename _Callback, typename... _Args>
    constexpr decltype(auto)
    recurse(_Callback __func, _Args&&... __args)
    {
        using return_value_t =
            std::invoke_result_t<_Callback&, const recursion_context_probe&, reference, _Args...>;

        assert(not empty());

        auto func = [&__func]<typename... _NextArgs>(const auto& info, _NextArgs&&... args) -> return_value_t
        {
            if (info.is_leaf())
            {
                return __func(info, info.that->tree[info.p], std::forward<_NextArgs>(args)...);
            }

            info.that->push_down(info.p, info.l, info.r);

            if constexpr (std::is_void_v<return_value_t>)
            {
                __func(info, info.that->tree[info.p], std::forward<_NextArgs>(args)...);
                info.that->push_up(info.p);
                return;
            }
            else
            {
                auto&& ret = __func(info, info.that->tree[info.p], std::forward<_NextArgs>(args)...);
                info.that->push_up(info.p);
                return ret;
            }
        };

        recursion_context<decltype(func), _Args...> info(1, 0, size() - 1, this, func);
        return func(info, std::forward<_Args>(__args)...);
    }

    template<typename _Callback, typename... _Args>
    constexpr decltype(auto)
    recurse_readonly(_Callback __func, _Args&&... __args)
    {
        using return_value_t =
            std::invoke_result_t<_Callback&, const recursion_context_probe&, const_reference, _Args...>;

        assert(not empty());

        auto func = [&__func]<typename... _NextArgs>(const auto& info, _NextArgs&&... args) -> return_value_t
        {
            if (not info.is_leaf())
            {
                info.that->push_down(info.p, info.l, info.r);
            }

            return __func(info, std::as_const(info.that->tree[info.p]), std::forward<_NextArgs>(args)...);
        };

        recursion_context<decltype(func), _Args...> info(1, 0, size() - 1, this, func);
        return func(info, std::forward<_Args>(__args)...);
    }


    constexpr void
    range_set(size_type __l, size_type __r, const value_type& __value)
    { for_each(__l, __r, [&](reference __ref) -> bool { __ref = __value; return true; }); }

    constexpr void
    set(size_type __p, const value_type& __value)
    { range_set(__p, __p, __value); }

    template<typename _Func>
    constexpr void
    transform(size_type __l, size_type __r, _Func __func)
    { for_each(__l, __r, [&](reference __ref) -> bool { __func(__ref); return true; }); }

    template<typename _Func>
    constexpr void
    transform(size_type __p, _Func __func)
    { transform(__p, __p, std::move(__func)); }

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

    virtual constexpr void
    push_down(
        [[maybe_unused]] size_type __p, [[maybe_unused]] size_type __l, [[maybe_unused]] size_type __r)
    { }

private:

    template<typename _Callback>
    requires std::invocable<_Callback&, reference>
    constexpr bool
    _M_for_each(
        size_type __p, size_type __l, size_type __r, size_type __x, size_type __y, _Callback&& __func)
    {
        if (__l == __r)
        {
            if constexpr (std::is_void_v<std::invoke_result_t<_Callback&, reference>>)
            {
                return __func(tree[__p]), true;
            }
            else
            {
                return __func(tree[__p]);
            }
        }

        push_down(__p, __l, __r);

        const size_type mid = (__l + __r) >> 1;
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
    requires std::invocable<_Callback&, const_reference>
    constexpr bool
    _M_for_each_cover_node(
        size_type __p, size_type __l, size_type __r, size_type __x, size_type __y, _Callback&& __func)
    {
        if (__x <= __l and __r <= __y)
        {
            if constexpr (std::is_void_v<std::invoke_result_t<_Callback&, const_reference>>)
            {
                return __func(std::as_const(tree[__p])), true;
            }
            else
            {
                return __func(std::as_const(tree[__p]));
            }
        }

        push_down(__p, __l, __r);

        const size_type mid = (__l + __r) >> 1;
        bool continues = true;

        if (__x <= mid)
        {
            continues = _M_for_each_cover_node(ls(__p), __l, mid, __x, __y, std::forward<_Callback>(__func));
        }

        if (__y > mid and continues)
        {
            continues = _M_for_each_cover_node(rs(__p), mid + 1, __r, __x, __y, std::forward<_Callback>(__func));
        }

        return continues;
    }

    [[nodiscard]] constexpr const_reference
    _M_at(size_type __p, size_type __l, size_type __r, size_type __i)
    {
        if (__l == __r)
        {
            return tree[__p];
        }

        push_down(__p, __l, __r);

        const size_type mid = (__l + __r) >> 1;

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
    [[no_unique_address]] _MergeFunc merge;
};

template<
    std::forward_iterator _Iter, std::sentinel_for<_Iter> _Sent, typename _Proj = std::identity,
    typename _MergeFunc = std::plus<>>
SegmentTree(_Iter, _Sent, _Proj = {}, _MergeFunc = {}) ->
    SegmentTree<std::remove_cvref_t<std::invoke_result_t<_Proj&, std::iter_reference_t<_Iter>>>, _MergeFunc>;

template<
    std::ranges::forward_range _Range,
    typename _MergeFunc = std::plus<>>
SegmentTree(_Range&&, _MergeFunc = {}) ->
    SegmentTree<std::ranges::range_value_t<_Range>, _MergeFunc>;
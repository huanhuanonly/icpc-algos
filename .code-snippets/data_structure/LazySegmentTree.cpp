struct LazyOperation
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

            if (that.has_lazy)
                that.lazy = that.merge(that.lazy, value);
            else
                that.lazy = value;
        }
    };
};

template<
    typename _ValueType, typename _MergeFunc = std::plus<_ValueType>,
    typename _LazyType = _ValueType, typename _LazyOperation = LazyOperation::RangeAdd>
class LazySegmentTree : public SegmentTree<_ValueType, _MergeFunc>
{
public:

    using base_type       = SegmentTree<_ValueType, _MergeFunc>;

    using container_type  = base_type::container_type;
    using value_type      = base_type::value_type;
    using lazy_type       = std::conditional_t<std::is_same_v<_LazyType, bool>, std::uint8_t, _LazyType>;
    using reference       = base_type::reference;
    using const_reference = base_type::const_reference;
    using size_type       = base_type::size_type;

    using base_type::size;
    using base_type::storage_size;

    struct lazy_context
    {
        value_type& value;
        lazy_type&  lazy;
        _MergeFunc& merge;

        size_type size;
        bool has_lazy;
    };

protected:

    using base_type::ls;
    using base_type::rs;

    using base_type::push_up;

    using base_type::tree;
    using base_type::merge;

public:

    constexpr explicit
    LazySegmentTree(size_type __n = 0, _MergeFunc __merge = {}, _LazyOperation __applytag = {}) noexcept
        : base_type(__n, std::move(__merge))
        , lazy(tree.size()), has_lazy(tree.size()), apply_tag(std::move(__applytag))
    { }

    template<std::forward_iterator _Iter, std::sentinel_for<_Iter> _Sent, typename _Proj = std::identity>
    constexpr
    LazySegmentTree(
        _Iter __first, _Sent __last, _Proj __proj = {},
        _MergeFunc __merge = {}, _LazyOperation __applytag = {}) noexcept
            : base_type(__first, __last, std::move(__proj), std::move(__merge))
            , lazy(tree.size()), has_lazy(tree.size()), apply_tag(std::move(__applytag))
    { }

    template<std::ranges::forward_range _Range>
    constexpr
    LazySegmentTree(
        _Range&& __r, _MergeFunc __merge = {}, _LazyOperation __applytag = {}) noexcept
            : base_type(std::ranges::begin(__r), std::ranges::end(__r), {}, std::move(__merge))
            , lazy(tree.size()), has_lazy(tree.size()), apply_tag(std::move(__applytag))
    { }

    constexpr
    LazySegmentTree(std::initializer_list<_ValueType> __list) noexcept
        : LazySegmentTree(__list.begin(), __list.end())
    { }


    constexpr void
    range_apply(size_type __l, size_type __r, const lazy_type& __value)
    {
        assert(__l <= __r and 0 <= __l and __r < size());
        _M_range_apply(1, 0, size() - 1, __l, __r, __value);
    }

    constexpr void
    resize(size_type __n) override
    {
        if (size() < __n)
        {
            lazy.resize(storage_size(__n));
            has_lazy.resize(storage_size(__n));
            base_type::resize(__n);
        }
        else
        {
            base_type::resize(__n);
            lazy.resize(tree.size());
            has_lazy.resize(tree.size());
        }
    }

    constexpr void
    reset() override
    {
        base_type::reset();
        std::ranges::fill(lazy, lazy_type{});
        has_lazy.assign(has_lazy.size(), false);
    }

protected:

    constexpr void
    make_lazy(size_type __p, size_type __l, size_type __r, const lazy_type& __value)
    {
        apply_tag(lazy_context{
            .value  = tree[__p],
            .lazy   = lazy[__p],
            .merge  = merge,
            .size   = __r - __l + 1,
            .has_lazy = has_lazy[__p]
        }, __value);

        has_lazy[__p] = true;
    }

    constexpr void
    push_down(size_type __p, size_type __l, size_type __r) override
    {
        if (__l < __r and has_lazy[__p])
        {
            const size_type mid = (__l + __r) >> 1;

            make_lazy(ls(__p), __l, mid, lazy[__p]);
            make_lazy(rs(__p), mid + 1, __r, lazy[__p]);

            lazy[__p] = lazy_type{};
            has_lazy[__p] = false;
        }
    }

private:

    constexpr void
    _M_range_apply(
        size_type __p, size_type __l, size_type __r, size_type __x, size_type __y, const lazy_type& __v)
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
            _M_range_apply(ls(__p), __l, mid, __x, __y, __v);
        }

        if (__y > mid)
        {
            _M_range_apply(rs(__p), mid + 1, __r, __x, __y, __v);
        }

        push_up(__p);
    }

protected:

    std::vector<lazy_type> lazy;
    std::vector<bool> has_lazy;

    [[no_unique_address]] _LazyOperation apply_tag;
};

template<
    std::forward_iterator _Iter, std::sentinel_for<_Iter> _Sent, typename _Proj = std::identity,
    typename _MergeFunc = std::plus<>, typename _LazyOperation = LazyOperation::RangeAdd>
LazySegmentTree(_Iter, _Sent, _Proj = {}, _MergeFunc = {}, _LazyOperation = {}) ->
    LazySegmentTree<
        std::remove_cvref_t<std::invoke_result_t<_Proj&, std::iter_reference_t<_Iter>>>, _MergeFunc,
        std::remove_cvref_t<std::invoke_result_t<_Proj&, std::iter_reference_t<_Iter>>>, _LazyOperation>;

template<
    std::ranges::forward_range _Range,
    typename _MergeFunc = std::plus<>, typename _LazyOperation = LazyOperation::RangeAdd>
LazySegmentTree(_Range&&, _MergeFunc = {}, _LazyOperation = {}) ->
    LazySegmentTree<
        std::ranges::range_value_t<_Range>, _MergeFunc,
        std::ranges::range_value_t<_Range>, _LazyOperation>;
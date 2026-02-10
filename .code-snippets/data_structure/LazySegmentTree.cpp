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
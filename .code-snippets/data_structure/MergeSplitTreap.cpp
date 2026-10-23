template<
    typename _Derived,
    typename _Tp,
    typename _Comp = std::ranges::less,
    typename _MergeFunc = decltype([](const _Tp& lhs, const _Tp&) -> _Tp { return lhs; })>
requires std::convertible_to<std::invoke_result_t<_MergeFunc&, const _Tp&, const _Tp&>, _Tp>
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

    constexpr explicit
    MergeSplitTreapImpl(_Comp __comp = {}, _MergeFunc __merge = {}) noexcept
        : _M_tree(1), _M_root(0), _M_comp(__comp), _M_merge(__merge)
    { }

    constexpr
    MergeSplitTreapImpl(
        std::initializer_list<value_type> __init, _Comp __comp = {}, _MergeFunc __merge = {}) noexcept
            : MergeSplitTreapImpl(__comp, __merge)
    { for (const auto& value : __init) { insert(value); } }

    template<std::input_iterator _Iter, std::sentinel_for<_Iter> _Sent, typename _Proj = std::identity>
    constexpr
    MergeSplitTreapImpl(
        _Iter __first, _Sent __last, _Proj __proj = {}, _Comp __comp = {}, _MergeFunc __merge = {}) noexcept
            : MergeSplitTreapImpl(__comp, __merge)
    { for (; __first != __last; ++__first) { insert(std::invoke(__proj, *__first)); } }

    template<std::ranges::input_range _Range, typename _Proj = std::identity>
    constexpr
    MergeSplitTreapImpl(_Range&& __r, _Proj __proj = {}, _Comp __comp = {}, _MergeFunc __merge = {}) noexcept
        : MergeSplitTreapImpl(__comp, __merge)
    { for (auto&& value : __r) { insert(std::invoke(__proj, value)); } }

    [[nodiscard]] constexpr size_type
    root() const noexcept
    { return _M_root; }

    constexpr void
    update_root(size_type __new_root) noexcept
    { _M_root = __new_root; }

    [[nodiscard]] constexpr size_type
    size() const noexcept
    { return _M_tree[root()].size; }

    constexpr void
    reserve(size_type __n)
    {
        _M_tree.reserve(1 + __n);

        if constexpr (requires() { static_cast<_Derived*>(this)->on_reserve(__n); })
        {
            static_cast<_Derived*>(this)->on_reserve(__n);
        }
    }

    [[nodiscard]] constexpr bool
    empty() const noexcept
    { return size() == 0; }

    constexpr void
    clear()
    {
        _M_tree.resize(1);
        update_root(size_type{});

        if constexpr (requires() { static_cast<_Derived*>(this)->on_clear(); })
        {
            static_cast<_Derived*>(this)->on_clear();
        }
    }

    [[nodiscard]] constexpr const node&
    node_at(size_type __i) const noexcept
    { return _M_tree[__i]; }

    constexpr void
    split_left_by_value(size_type u, const_reference value, size_type& rx, size_type& ry)
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

    constexpr void
    split_right_by_value(size_type u, const_reference value, size_type& rx, size_type& ry)
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

    constexpr void
    split_by_value(size_type u, const_reference value, size_type& rx, size_type& ry)
    { split_right_by_value(u, value, rx, ry); }

    constexpr void
    split_by_size(size_type u, size_type left_size, size_type& rx, size_type& ry)
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

    constexpr size_type
    merge(size_type u, size_type v)
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

    constexpr void
    insert(const_reference __value)
    {
        size_type rx, ry;
        split_left_by_value(root(), __value, rx, ry);
        update_root(merge(merge(rx, create_node(__value)), ry));
    }

    constexpr void
    insert_before(size_type __pos, const_reference __value)
    {
        size_type rx, ry;
        split_by_size(root(), __pos, rx, ry);
        update_root(merge(merge(rx, create_node(__value)), ry));
    }

    constexpr bool
    remove(const_reference __value)
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

    constexpr size_type
    remove_all(const_reference __value)
    {
        size_type rx, rm, ry;
        split_right_by_value(root(), __value, rx, rm);
        split_left_by_value(rm, __value, rm, ry);

        const size_type cnt = _M_tree[rm].size;

        update_root(merge(rx, ry));
        return cnt;
    }

    constexpr size_type
    remove_at(size_type __pos, size_type __n = 1)
    {
        size_type rx, rm, ry;
        split_by_size(root(), __pos, rx, rm);
        split_by_size(rm, __n, rm, ry);

        const size_type cnt = _M_tree[rm].size;

        update_root(merge(rx, ry));
        return cnt;
    }

    [[nodiscard]] constexpr const_reference
    find_by_order(size_type __rank)
    {
        size_type rx, rm, ry;
        split_by_size(root(), __rank, rx, rm);
        split_by_size(rm, 1, rm, ry);

        update_root(merge(merge(rx, rm), ry));
        return _M_tree[rm].value;
    }

    [[nodiscard]] constexpr size_type
    order_of_key(const_reference __value)
    {
        size_type rx, ry;
        split_right_by_value(root(), __value, rx, ry);

        const size_type rank = _M_tree[rx].size;

        update_root(merge(rx, ry));
        return rank;
    }

    [[nodiscard]] constexpr const_reference
    front()
    { return find_by_order(0); }

    [[nodiscard]] constexpr const_reference
    back()
    { return find_by_order(size() - 1); }

    [[nodiscard]] constexpr value_type
    reduce(size_type __pos, size_type __n)
    {
        size_type rx, rm, ry;
        split_by_size(root(), __pos, rx, rm);
        split_by_size(rm, __n, rm, ry);

        const value_type value = _M_tree[rm].reduced_value;

        update_root(merge(merge(rx, rm), ry));
        return value;
    }

    [[nodiscard]] constexpr const_reference
    reduce() const noexcept
    { return _M_tree[root()].reduced_value; }

    [[nodiscard]] constexpr const_reference
    lower_bound(const_reference __value, bool* __found = nullptr)
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

    [[nodiscard]] constexpr const_reference
    upper_bound(const_reference __value, bool* __found = nullptr)
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

    [[nodiscard]] constexpr equal_range_result
    equal_range(const_reference __value)
    {
        size_type rx, rm, ry;
        split_right_by_value(root(), __value, rx, rm);
        split_left_by_value(rm, __value, rm, ry);

        const equal_range_result result{_M_tree[rx].size, _M_tree[rm].size};

        update_root(merge(merge(rx, rm), ry));
        return result;
    }

    [[nodiscard]] constexpr size_type
    count(const_reference __value)
    { return equal_range(__value).len; }

    [[nodiscard]] constexpr bool
    contains(const_reference __value)
    { return static_cast<bool>(equal_range(__value).len); }

    template<typename _Func>
    constexpr void
    for_each(size_type __pos, size_type __n, _Func __func)
    {
        size_type rx, rm, ry;
        split_by_size(root(), __pos, rx, rm);
        split_by_size(rm, __n, rm, ry);

        inorder(rm, __func);
        update_root(merge(merge(rx, rm), ry));
    }

    template<typename _Func>
    constexpr void
    for_each(_Func __func)
    { inorder(root(), __func); }

    template<typename _Container, typename _Proj = std::identity>
    constexpr _Container
    to(_Proj __proj = {})
    {
        _Container result{};
        for_each([&](const_reference value) -> void { result.emplace_back(std::invoke(__proj, value)); });
        return result;
    }

protected:

    [[nodiscard]] static size_type
    generate_priority() noexcept
    {
        static std::mt19937 rng(
            std::random_device{}() ^
            std::chrono::steady_clock::now().time_since_epoch().count());

        return rng();
    }

    constexpr size_type
    create_node(const value_type& __value)
    {
        _M_tree.emplace_back(0, 0, generate_priority(), 1, __value, __value);

        if constexpr (requires() { static_cast<_Derived*>(this)->on_create_node(__value); })
        {
            static_cast<_Derived*>(this)->on_create_node(__value);
        }

        return size_type(_M_tree.size()) - 1;
    }

    [[nodiscard]] constexpr node&
    node_at(size_type __i) noexcept
    { return _M_tree[__i]; }

    constexpr void
    push_up(size_type u)
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

    constexpr void
    push_down(size_type u)
    {
        if constexpr (requires() { static_cast<_Derived*>(this)->on_push_down(u); })
        {
            static_cast<_Derived*>(this)->on_push_down(u);
        }
    }

    template<typename _Func>
    constexpr void
    inorder(size_type u, _Func&& f)
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
requires std::convertible_to<std::invoke_result_t<_MergeFunc&, const _Tp&, const _Tp&>, _Tp>
class MergeSplitTreap :
    public MergeSplitTreapImpl<MergeSplitTreap<_Tp, _Comp, _MergeFunc>, _Tp, _Comp, _MergeFunc>
{
public:
    using base_type = MergeSplitTreapImpl<MergeSplitTreap<_Tp, _Comp, _MergeFunc>, _Tp, _Comp, _MergeFunc>;
    using base_type::base_type;
};
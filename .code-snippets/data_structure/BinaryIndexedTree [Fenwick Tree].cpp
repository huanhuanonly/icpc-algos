template<
    typename _Tp,
    typename _BinaryOperation = std::plus<>,
    typename _InverseBinaryOperation = std::minus<>>
class BinaryIndexedTree
{
public:

    using value_type = _Tp;
    using reference = value_type&;
    using const_reference = const value_type&;
    using size_type = std::size_t;

    explicit constexpr
    BinaryIndexedTree(size_type __n = 0, const value_type& __identity = {}) noexcept
        : _M_BITree(__n + 1, __identity), _M_op{}, _M_inv_op{}
    { }

    constexpr
    BinaryIndexedTree(
        size_type __n, const value_type& __identity,
        _BinaryOperation __op, _InverseBinaryOperation __inv_op) noexcept
            : _M_BITree(__n + 1, __identity), _M_op(__op), _M_inv_op(__inv_op)
    { }

    [[nodiscard]] static constexpr size_type
    lowbit(size_type __x) noexcept
    { return __x & -__x; }

    [[nodiscard]] constexpr const_reference
    identity() const noexcept
    { return _M_BITree.front(); }

    template<typename _Up>
    constexpr void
    add(size_type __i, const _Up& __x) noexcept
    {
        for (++__i; __i < _M_BITree.size(); __i += lowbit(__i))
        {
            _M_BITree[__i] = _M_op(_M_BITree[__i], __x);
        }
    }

    template<typename _Up>
    constexpr void
    subtract(size_type __i, const _Up& __x) noexcept
    {
        for (++__i; __i < _M_BITree.size(); __i += lowbit(__i))
        {
            _M_BITree[__i] = _M_inv_op(_M_BITree[__i], __x);
        }
    }

    [[nodiscard]] constexpr value_type
    prefix_reduce(size_type __r) const noexcept
    {
        value_type result = _M_BITree[++__r];

        for (__r -= lowbit(__r); __r; __r -= lowbit(__r))
        {
            result = _M_op(_M_BITree[__r], result);
        }

        return result;
    }

    [[nodiscard]] constexpr value_type
    reduce(size_type __l, size_type __r) const noexcept
    { return __l ? _M_inv_op(prefix_reduce(__r), prefix_reduce(__l - 1)) : prefix_reduce(__r); }

    [[nodiscard]] constexpr value_type
    reduce() const noexcept
    { return empty() ? identity() : reduce(0, size() - 1); }

    [[nodiscard]] constexpr value_type
    get(size_type __i) const noexcept
    { return reduce(__i, __i); }

    constexpr void
    set(size_type __i, value_type __x) noexcept
    { reset(__i), add(__i, __x); }

    constexpr void
    reset(size_type __i) noexcept
    { subtract(__i, get(__i)); }

    constexpr void
    reset() noexcept
    { for (size_type i = 0; i < size(); reset(i), ++i); }

    [[nodiscard]] constexpr size_type
    size() const noexcept
    { return static_cast<size_type>(_M_BITree.size()) - 1; }

    [[nodiscard]] constexpr bool
    empty() const noexcept
    { return size() == 0; }

    constexpr void
    resize(size_type __n)
    {
        const auto c =
            std::views::iota(size_type{}, size()) |
            std::views::transform([&](size_type i) { return get(i); }) |
            std::ranges::to<std::vector>();

        for (size_type i = 0; i < size(); subtract(i, c[i]), ++i);
        _M_BITree.resize(__n + 1, identity());
        for (size_type i = 0; i < static_cast<size_type>(c.size()); add(i, c[i]), ++i);
    }

private:

    std::vector<value_type> _M_BITree;

    [[no_unique_address]] _BinaryOperation _M_op;
    [[no_unique_address]] _InverseBinaryOperation _M_inv_op;
};
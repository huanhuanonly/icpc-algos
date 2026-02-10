template<typename _Tp>
class BinaryIndexedTree
{
public:

    using value_type = _Tp;

    constexpr BinaryIndexedTree() noexcept = default;

    explicit constexpr BinaryIndexedTree(std::size_t __size) noexcept
        : _M_BITree(__size + 1)
    { }

    [[nodiscard]] static constexpr std::size_t lowbit(std::size_t __x) noexcept
    { return __x & -__x; }

    constexpr void add(std::size_t __i, value_type __value = 1)
    {
        for (++__i; __i < _M_BITree.size(); __i += lowbit(__i))
        {
            _M_BITree[__i] += __value;
        }
    }

    constexpr void subtract(std::size_t __i, value_type __value = 1)
    {
        for (++__i; __i < _M_BITree.size(); __i += lowbit(__i))
        {
            _M_BITree[__i] -= __value;
        }
    }

    [[nodiscard]] constexpr value_type sum(std::size_t __l)
    {
        value_type result{};

        for (++__l; __l; __l -= lowbit(__l))
        {
            result += _M_BITree[__l];
        }

        return result;
    }

    [[nodiscard]] constexpr value_type sum(std::size_t __l, std::size_t __r)
    { return __l ? sum(__r) - sum(__l - 1) : sum(__r); }

    [[nodiscard]] constexpr value_type get(std::size_t __i)
    { return sum(__i, __i); }

    constexpr value_type set(std::size_t __i, value_type __value)
    {
        value_type prev = get(__i);

        prev < __value ? add(__i, __value - prev) : subtract(__i, prev - __value);

        return prev;
    }

    constexpr void reset(std::size_t __size = static_cast<std::size_t>(-1))
    { __size == static_cast<std::size_t>(-1) ? std::ranges::fill(_M_BITree, value_type{}) : _M_BITree.assign(__size + 1, value_type{}); }

private:

    std::vector<value_type> _M_BITree;
};
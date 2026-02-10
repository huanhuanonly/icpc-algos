template<typename _Tp, typename _St = std::size_t, _St _Size = sizeof(_Tp) * 8>
requires requires(_Tp __x, _St __n) {
    {__x ^ __x} -> std::same_as<_Tp>;
    {__x & __x} -> std::same_as<_Tp>;
    {__x >> __n} -> std::same_as<_Tp>;
    {__x == __x} -> std::same_as<bool>;
    {__x ^= __x} -> std::same_as<_Tp&>; }
class XorBasis
{
public:

    using value_type = _Tp;
    using size_type  = _St;

    constexpr
    XorBasis() noexcept
        : _M_basis{}, _M_size(0), _M_zero(false)
    { }

    template<std::input_iterator _Iter, std::sentinel_for<_Iter> _Sent, typename _Proj = std::identity>
    constexpr
    XorBasis(_Iter __first, _Sent __last, _Proj __proj = {}) noexcept
        : XorBasis()
    { insert(__first, __last, __proj); }

    template<std::ranges::input_range _Range, typename _Proj = std::identity>
    constexpr
    XorBasis(_Range&& __r, _Proj __proj = {}) noexcept
        : XorBasis()
    { insert(std::forward<_Range>(__r), __proj); }

    constexpr
    XorBasis(std::initializer_list<value_type> __list) noexcept
        : XorBasis()
    { insert(__list); }


    [[nodiscard]] constexpr bool
    operator==(const XorBasis& __other) const noexcept
    { return _M_zero == __other._M_zero and std::ranges::equal(_M_basis, __other._M_basis, {}, _S_check); }

    [[nodiscard]] constexpr bool
    operator!=(const XorBasis& __other) const noexcept
    { return not (*this == __other); }


    [[nodiscard]] static constexpr size_type
    bit_count() noexcept
    { return _Size; }

    [[nodiscard]] constexpr size_type
    size() const noexcept
    { return _M_size; }

    [[nodiscard]] constexpr bool
    empty() const noexcept
    { return _M_size == size_type{} and _M_zero == false; }

    [[nodiscard]] constexpr bool
    operator not() const noexcept
    { return empty(); }
    
    [[nodiscard]] constexpr
    operator bool() const noexcept
    { return not empty(); }

    [[nodiscard]] constexpr size_type
    count() const noexcept
    { return (1 << _M_size) - not _M_zero; }

    [[nodiscard]] constexpr auto
    view() const noexcept
    { return _M_basis | std::views::filter([](value_type i) -> bool { return static_cast<bool>(i); }); }

    constexpr void
    clear() noexcept
    {
        _M_basis.fill(value_type{});
        _M_size = size_type{};
        _M_zero = false;
    }

    constexpr bool
    insert(value_type __value) noexcept
    {
        for (size_type i = static_cast<size_type>(_M_basis.size()); i--; )
        {
            if (_S_take(__value, i))
            {
                if (_S_check(_M_basis[i]))
                {
                    __value ^= _M_basis[i];
                }
                else
                {
                    _M_basis[i] = __value;
                    ++_M_size;
                    return true;
                }
            }
        }

        _M_zero = true;
        return false;
    }

    template<std::input_iterator _Iter, std::sentinel_for<_Iter> _Sent, typename _Proj = std::identity>
    constexpr size_type
    insert(_Iter __first, _Sent __last, _Proj __proj = {}) noexcept
    {
        size_type n{};

        for (; __first != __last; ++__first)
        {
            n += insert(std::invoke(__proj, *__first));
        }

        return n;
    }

    template<std::ranges::input_range _Range, typename _Proj = std::identity>
    constexpr size_type
    insert(_Range&& __r, _Proj __proj = {})
    { return insert(std::ranges::begin(__r), std::ranges::end(__r), __proj); }

    constexpr void
    normalize() noexcept
    {
        for (size_type i = static_cast<size_type>(_M_basis.size()); i--; )
        {
            if (_S_check(_M_basis[i]))
            {
                for (size_type j = i; j--; )
                {
                    if (_S_check(_M_basis[j]))
                    {
                        _M_basis[i] ^= _M_basis[j];
                    }
                }
            }
        }
    }

    [[nodiscard]] constexpr bool
    contains(value_type __value) const noexcept
    {
        if (not _S_check(__value))
        {
            return _M_zero;
        }

        for (size_type i = static_cast<size_type>(_M_basis.size()); i--; )
        {
            if (_S_take(__value, i))
            {
                if (_S_check(_M_basis[i]))
                {
                    __value ^= _M_basis[i];
                }
                else
                {
                    return false;
                }
            }
        }

        return true;
    }

    [[nodiscard]] constexpr value_type
    find_min_xor_sum() const noexcept
    { return _M_zero ? value_type{} : *std::ranges::find(_M_basis, true, _S_check); }

    [[nodiscard]] constexpr value_type
    find_max_xor_sum() const noexcept
    {
        value_type max{};

        for (size_type i = static_cast<size_type>(_M_basis.size()); i--; )
        {
            if (_S_check(_M_basis[i]) and not _S_take(max, i))
            {
                max ^= _M_basis[i];
            }
        }

        return max;
    }

    [[nodiscard]] constexpr value_type
    find_kth_smallest(size_type __k) const noexcept
    {
        assert(__k >= 0 and __k < count());

        if (_M_zero)
        {
            if (__k == 0)
            {
                return value_type{};
            }
        }
        else
        {
            ++__k;
        }

        value_type result{};
        size_type  cnt = 1 << _M_size - 1;

        for (size_type i = static_cast<size_type>(_M_basis.size()); i--; )
        {
            if (_S_check(_M_basis[i]))
            {
                if (__k >= cnt)
                {
                    if (not _S_take(result, i))
                    {
                        result ^= _M_basis[i];
                    }
                    
                    __k -= cnt;
                }
                else if (_S_take(result, i))
                {
                    result ^= _M_basis[i];
                }

                cnt >>= 1;
            }
        }

        return result;
    }

    [[nodiscard]] constexpr value_type
    find_kth_largest(size_type __k) const noexcept
    {
        assert(count() >= 1 + __k);
        return find_kth_smallest(count() - 1 - __k);
    }

    [[nodiscard]] constexpr value_type
    find_kth_smallest_after_normalization(size_type __k) const noexcept
    {
        assert(__k >= 0 and __k < count());

        if (_M_zero)
        {
            if (__k == 0)
            {
                return value_type{};
            }
        }
        else
        {
            ++__k;
        }

        value_type result{};

        for (size_type i = 0; i < static_cast<size_type>(_M_basis.size()); ++i)
        {
            if (_S_check(_M_basis[i]))
            {
                if (__k & 1)
                {
                    result ^= _M_basis[i];
                }

                __k >>= 1;
            }
        }

        return result;
    }

    [[nodiscard]] constexpr value_type
    find_kth_largest_after_normalization(size_type __k) const noexcept
    {
        assert(count() >= 1 + __k);
        return find_kth_smallest_after_normalization(count() - 1 - __k);
    }

    [[nodiscard]] constexpr size_type
    count_le(const value_type& __value) const noexcept
    {
        if (__value <= 0)
        {
            return size_type{};
        }
        else if (_M_size == 0)
        {
            return _M_zero;
        }

        value_type result{};
        size_type cnt = 1 << _M_size - 1;

        value_type mask{};

        for (size_type i = static_cast<size_type>(_M_basis.size()); i--; )
        {
            if (_S_check(_M_basis[i]))
            {
                if (_S_take(__value, i))
                {
                    result += cnt;

                    if (not _S_take(mask, i))
                    {
                        mask ^= _M_basis[i];
                    }
                }
                else if (_S_take(mask, i))
                {
                    mask ^= _M_basis[i];
                }

                cnt >>= 1;
            }
            else if (const auto lb = _S_take(__value, i), rb = _S_take(mask, i); lb != rb)
            {
                if (lb)
                {
                    result += cnt << 1;
                }

                break;
            }
        }

        return result - not _M_zero;
    }

    [[nodiscard]] constexpr size_type
    count_leq(const value_type& __value) const noexcept
    { return count_le(__value) + contains(__value); }

    [[nodiscard]] constexpr size_type
    count_ge(const value_type& __value) const noexcept
    { return count() - count_leq(__value); }

    [[nodiscard]] constexpr size_type
    count_geq(const value_type& __value) const noexcept
    { return count() - count_le(__value); }


    [[nodiscard]] constexpr std::optional<value_type>
    prev_less(const value_type& __value, size_type __n = 1) const noexcept
    {
        if (__n == 0) [[unlikely]]
        {
            if (contains(__value))
            {
                return __value;
            }
            else
            {
                return std::nullopt;
            }
        }

        if (const size_type cid = count_le(__value); cid >= __n) [[likely]]
        {
            return find_kth_smallest(cid - __n);
        }
        else [[unlikely]]
        {
            return std::nullopt;
        }
    }

    [[nodiscard]] constexpr std::optional<value_type>
    next_greater(const value_type& __value, size_type __n = 1) const noexcept
    {
        if (__n == 0) [[unlikely]]
        {
            if (contains(__value))
            {
                return __value;
            }
            else
            {
                return std::nullopt;
            }
        }

        if (const size_type cid = count_ge(__value); cid >= __n) [[likely]]
        {
            return find_kth_largest(cid - __n);
        }
        else [[unlikely]]
        {
            return std::nullopt;
        }
    }

    [[nodiscard]] constexpr value_type
    operator[](std::make_signed_t<size_type> __n) const noexcept
    { return __n >= 0 ? find_kth_smallest(size_type(__n)) : find_kth_largest(size_type(-__n - 1)); }


    constexpr void
    merge(const XorBasis& __other) noexcept
    {
        for (size_type i = 0; i < static_cast<size_type>(_M_basis.size()); ++i)
        {
            if (_S_check(__other._M_basis[i]))
            {
                insert(__other._M_basis[i]);
            }
        }

        if (__other._M_zero)
        {
            _M_zero = true;
        }
    }

    constexpr XorBasis&
    operator|=(const XorBasis& __other) noexcept
    { return merge(__other), *this; }

    [[nodiscard]] constexpr XorBasis
    operator|(const XorBasis& __other) const noexcept
    { return XorBasis(*this) |= __other; }

protected:

    [[nodiscard]] static constexpr bool
    _S_check(const value_type& __value) noexcept
    {
        if constexpr (std::convertible_to<value_type, bool>)
        {
            return static_cast<bool>(__value);
        }
        else
        {
            return not (__value == value_type{});
        }
    }

    [[nodiscard]] static constexpr bool
    _S_take(const value_type& __value, size_type __i) noexcept
    {
        if constexpr (requires{ {__value[__i] } -> std::convertible_to<bool>; })
        {
            return __value[__i];
        }
        else
        {
            return __value >> __i & 1;
        }
    }

private:

    std::array<value_type, bit_count()> _M_basis;
    size_type _M_size;
    bool _M_zero;
};

template<std::input_iterator _Iter, std::sentinel_for<_Iter> _Sent, typename _Proj = std::identity>
XorBasis(_Iter, _Sent, _Proj = {}) -> XorBasis<std::remove_reference_t<std::invoke_result_t<_Proj, std::iter_reference_t<_Iter>>>>;

template<std::ranges::input_range _Range, typename _Proj = std::identity>
XorBasis(_Range&&, _Proj = {}) -> XorBasis<std::remove_reference_t<std::invoke_result_t<_Proj, std::iter_reference_t<decltype(std::ranges::begin(std::declval<_Range>()))>>>>;

template<std::size_t _Size>
[[nodiscard]] constexpr std::strong_ordering
operator<=>(const std::bitset<_Size>& __lhs, const std::bitset<_Size>& __rhs) noexcept
{
    constexpr auto n = sizeof(std::bitset<_Size>);

    if constexpr (n % sizeof(std::uint64_t) == 0)
    {
        constexpr auto c = n / sizeof(std::uint64_t);

        auto lptr = reinterpret_cast<const std::uint64_t*>(&__lhs) + c - 1;
        auto rptr = reinterpret_cast<const std::uint64_t*>(&__rhs) + c - 1;

        for (auto i = 0; i < c; ++i, --lptr, --rptr)
        {
            if (*lptr != *rptr)
            {
                return *lptr < *rptr ? std::strong_ordering::less : std::strong_ordering::greater;
            }
        }
    }
    else
    {
        constexpr auto c = n / sizeof(std::uint32_t);

        auto lptr = reinterpret_cast<const std::uint32_t*>(&__lhs) + c - 1;
        auto rptr = reinterpret_cast<const std::uint32_t*>(&__rhs) + c - 1;

        for (auto i = 0; i < c; ++i, --lptr, --rptr)
        {
            if (*lptr != *rptr)
            {
                return *lptr < *rptr ? std::strong_ordering::less : std::strong_ordering::greater;
            }
        }
    }

    return std::strong_ordering::equivalent;
}
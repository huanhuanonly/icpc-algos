template<typename _Tp, std::unsigned_integral _St = std::size_t, _St _Bits = sizeof(_Tp) * 8>
requires requires(_Tp __x, _St __n) {
    {__x ^ __x} -> std::convertible_to<_Tp>;
    {__x & __x} -> std::convertible_to<_Tp>;
    {__x >> __n} -> std::convertible_to<_Tp>;
    {__x == __x} -> std::same_as<bool>;
    {__x ^= __x} -> std::same_as<_Tp&>; }
class XorBasis
{
public:

    using value_type = _Tp;
    using size_type  = _St;

    constexpr
    XorBasis() noexcept
        : _M_basis{}, _M_rank(0), _M_zero(false)
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
    {
        if (rank() != __other.rank() or _M_zero != __other._M_zero)
        {
            return false;
        }

        for (const auto& x : _M_basis)
        {
            if (_S_check(x) and not __other.contains(x))
            {
                return false;
            }
        }

        return true;
    }

    [[nodiscard]] static constexpr size_type
    bit_width() noexcept
    { return _Bits; }

    [[nodiscard]] constexpr size_type
    rank() const noexcept
    { return _M_rank; }

    [[nodiscard]] constexpr bool
    empty() const noexcept
    { return not rank() and _M_zero == false; }

    [[nodiscard]] constexpr bool
    operator not() const noexcept
    { return empty(); }

    [[nodiscard]] constexpr explicit
    operator bool() const noexcept
    { return not empty(); }

    [[nodiscard]] constexpr size_type
    count() const noexcept
    { return (size_type{1} << rank()) - not _M_zero; }

    [[nodiscard]] constexpr auto
    view() const noexcept
    { return _M_basis | std::views::filter(&_S_check); }

    constexpr void
    clear() noexcept
    {
        _M_basis.fill(value_type{});
        _M_rank = size_type{};
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
                    ++_M_rank;
                    return true;
                }
            }
        }

        _M_zero = true;
        return false;
    }

    template<std::input_iterator _Iter, std::sentinel_for<_Iter> _Sent, typename _Proj = std::identity>
    constexpr size_type
    insert(_Iter __first, _Sent __last, _Proj __proj = {})
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
                    if (_S_check(_M_basis[j]) and _S_take(_M_basis[i], j))
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
    min_subset_xor() const noexcept
    {
        assert(not empty());
        return _M_zero ? value_type{} : *std::ranges::find(_M_basis, true, _S_check);
    }

    [[nodiscard]] constexpr value_type
    max_subset_xor() const noexcept
    {
        assert(not empty());

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
        size_type  cnt = size_type{1} << rank() - 1;

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
        assert(__k < count());
        return find_kth_smallest(count() - 1 - __k);
    }

    [[nodiscard]] constexpr value_type
    kth_smallest_normalized(size_type __k) const noexcept
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
    kth_largest_normalized(size_type __k) const noexcept
    {
        assert(__k < count());
        return kth_smallest_normalized(count() - 1 - __k);
    }

    [[nodiscard]] constexpr size_type
    count_lt(const value_type& __value) const noexcept
    {
        if (not _S_check(__value))
        {
            return size_type{};
        }
        else if (not rank())
        {
            return _M_zero;
        }

        size_type result{};
        size_type cnt = size_type{1} << rank() - 1;

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
                    result += cnt ? cnt << 1 : size_type{1};
                }

                break;
            }
        }

        return result - not _M_zero;
    }

    [[nodiscard]] constexpr size_type
    count_le(const value_type& __value) const noexcept
    { return count_lt(__value) + contains(__value); }

    [[nodiscard]] constexpr size_type
    count_gt(const value_type& __value) const noexcept
    { return count() - count_le(__value); }

    [[nodiscard]] constexpr size_type
    count_ge(const value_type& __value) const noexcept
    { return count() - count_lt(__value); }


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

        if (const size_type cid = count_lt(__value); cid >= __n) [[likely]]
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

        if (const size_type cid = count_gt(__value); cid >= __n) [[likely]]
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
    { return __n >= 0 ? find_kth_smallest(size_type(__n)) : find_kth_largest(size_type(-(__n + 1))); }


    constexpr void
    merge(const XorBasis& __other) noexcept
    {
        for (const auto& x : __other._M_basis)
        {
            if (_S_check(x))
            {
                insert(x);
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

    std::array<value_type, bit_width()> _M_basis;
    size_type _M_rank;
    bool _M_zero;
};

template<std::input_iterator _Iter, std::sentinel_for<_Iter> _Sent, typename _Proj = std::identity>
XorBasis(_Iter, _Sent, _Proj = {}) ->
    XorBasis<std::remove_cvref_t<std::indirect_result_t<_Proj&, _Iter>>>;

template<std::ranges::input_range _Range, typename _Proj = std::identity>
XorBasis(_Range&&, _Proj = {}) ->
    XorBasis<std::remove_cvref_t<std::indirect_result_t<_Proj&, std::ranges::iterator_t<_Range>>>>;

template<std::size_t _Size>
[[nodiscard]] constexpr std::strong_ordering
operator<=>(const std::bitset<_Size>& __lhs, const std::bitset<_Size>& __rhs) noexcept
{
    for (std::size_t i = _Size; i--; )
    {
        if (const bool a = __lhs.test(i), b = __rhs.test(i); a != b)
        {
            return a ? std::strong_ordering::greater : std::strong_ordering::less;
        }
    }

    return std::strong_ordering::equivalent;
}
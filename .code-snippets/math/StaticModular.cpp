template<typename _Tp, _Tp _Modulus>
class StaticModular
{
public:

    using value_type = _Tp;
    using reference = _Tp&;
    using const_reference = const _Tp&;

    constexpr
    StaticModular(value_type __value = {}) noexcept
        : _M_value(residue(__value))
    { }

    [[nodiscard]] constexpr value_type
    value() const noexcept
    { return _M_value; }

    [[nodiscard]] static constexpr value_type
    modulus() noexcept
    { return _Modulus; }

    template<typename _Ty>
    [[nodiscard]] static constexpr _Ty
    residue(_Ty __x) noexcept
    {
        if constexpr (std::is_unsigned_v<_Ty>)
        {
            return __x % static_cast<_Ty>(modulus());
        }
        else
        {
            if (const auto r = __x % static_cast<_Ty>(modulus()); r < 0)
            {
                return r + static_cast<_Ty>(modulus());
            }
            else
            {
                return r;
            }
        }
    }

    template<typename _Ty>
    [[nodiscard]] constexpr StaticModular
    power(_Ty __x) const noexcept
    {
        assert(__x >= 0);

        StaticModular result(static_cast<value_type>(1));
        auto t = *this;

        for (; __x; t *= t, __x >>= 1)
        {
            (__x & 1) ? void(result *= t) : void();
        }

        return result;
    }

    [[nodiscard]] constexpr StaticModular
    inverse() const noexcept
    {
#if defined(__SIZEOF_INT128__)
        __int128_t x{}, y{};
        const auto gcd = exgcd<__int128_t>(_M_value, x, modulus(), y);

        assert(gcd == 1);
        return static_cast<value_type>(residue(x));
#else
        int64_t x{}, y{};
        const auto gcd = exgcd<int64_t>(_M_value, x, modulus(), y);

        assert(gcd == 1);
        return static_cast<value_type>(residue(x));
#endif
    }

    template<typename _Ty>
    [[nodiscard]] constexpr _Ty
    cast() const noexcept
    { return static_cast<_Ty>(_M_value); }


    constexpr StaticModular&
    operator=(value_type __value) noexcept
    { _M_value = residue(__value); return *this; }

    [[nodiscard]] constexpr
    operator value_type() const noexcept
    { return _M_value; }

    [[nodiscard]] constexpr auto
    operator<=>(value_type __x) const noexcept
    { return _M_value <=> residue(__x); }

    [[nodiscard]] constexpr bool
    operator==(value_type __x) const noexcept
    { return _M_value == residue(__x); }

    [[nodiscard]] constexpr auto
    operator<=>(const StaticModular& __other) const noexcept = default;

    [[nodiscard]] constexpr bool
    operator==(const StaticModular& __other) const noexcept = default;

    [[nodiscard]] constexpr const_reference
    operator*() const noexcept
    { return _M_value; }

    [[nodiscard]] constexpr bool
    operator!() const noexcept
    { return !_M_value; }

    [[nodiscard]] constexpr StaticModular
    operator~() const noexcept
    { return ~_M_value; }

    [[nodiscard]] constexpr StaticModular
    operator+() const noexcept
    { return +_M_value; }

    [[nodiscard]] constexpr StaticModular
    operator-() const noexcept
    { return modulus() - _M_value; }

    constexpr StaticModular&
    operator++() noexcept
    { _M_value = residue(++_M_value); return *this; }

    constexpr StaticModular&
    operator--() noexcept
    { _M_value = _M_value ? _M_value - 1 : modulus() - 1; return *this; }

    [[nodiscard]] constexpr StaticModular
    operator++(int) noexcept
    { auto t = *this; ++*this; return t; }

    [[nodiscard]] constexpr StaticModular
    operator--(int) noexcept
    { auto t = *this; --*this; return t; }

    [[nodiscard]] constexpr StaticModular
    operator+(value_type __x) const noexcept
    {
        __x = residue(__x);

        if (_M_value < modulus() - __x)
        {
            return _M_value + __x;
        }
        else
        {
            return _M_value - (modulus() - __x);
        }
    }

    [[nodiscard]] constexpr StaticModular
    operator-(value_type __x) const noexcept
    {
        __x = residue(__x);

        if (_M_value >= __x)
        {
            return _M_value - __x;
        }
        else
        {
            return _M_value + (modulus() - __x);
        }
    }

    [[nodiscard]] constexpr StaticModular
    operator*(value_type __x) const noexcept
    { auto t = *this; t *= __x; return t; }

    [[nodiscard]] constexpr StaticModular
    operator/(value_type __x) const noexcept
    { return *this * StaticModular(__x).inverse(); }

    [[nodiscard]] constexpr StaticModular
    operator%(value_type __x) const noexcept
    { assert(__x); return _M_value % __x; }

    constexpr StaticModular&
    operator+=(value_type __x) noexcept
    { return *this = *this + __x; }

    constexpr StaticModular&
    operator-=(value_type __x) noexcept
    { return *this = *this - __x; }

    constexpr StaticModular&
    operator*=(value_type __x) noexcept
    {
        if constexpr (std::numeric_limits<value_type>::max() / modulus() >= modulus())
        {
            _M_value = residue(_M_value * residue(__x));
            return *this;
        }
#if defined(__SIZEOF_INT128__)
        else if constexpr (sizeof(value_type) <= 8U)
        {
            _M_value = static_cast<value_type>(residue(
                static_cast<__uint128_t>(_M_value) * residue(__x)));

            return *this;
        }
#endif
        else
        {
            __x = residue(__x);

            StaticModular result;

            for (; __x; *this += *this, __x >>= 1)
            {
                (__x & 1) ? void(result += *this) : void();
            }

            return *this = result;
        }
    }

    constexpr StaticModular&
    operator/=(value_type __x) noexcept
    { return *this = *this / __x; }

    constexpr StaticModular&
    operator%=(value_type __x) noexcept
    { return *this = *this % __x; }

    [[nodiscard]] constexpr StaticModular
    operator<<(value_type __x) const noexcept
    { return *this * StaticModular(2).power(__x); }

    [[nodiscard]] constexpr StaticModular
    operator>>(value_type __x) const noexcept
    { return *this / StaticModular(2).power(__x); }

    constexpr StaticModular&
    operator<<=(value_type __x) noexcept
    { return *this *= StaticModular(2).power(__x); }

    constexpr StaticModular&
    operator>>=(value_type __x) noexcept
    { return *this /= StaticModular(2).power(__x); }

    [[nodiscard]] constexpr StaticModular
    operator^(value_type __x) const noexcept
    { return _M_value ^ __x; }

    [[nodiscard]] constexpr StaticModular
    operator&(value_type __x) const noexcept
    { return _M_value & __x; }

    [[nodiscard]] constexpr StaticModular
    operator|(value_type __x) const noexcept
    { return _M_value | __x; }

    constexpr StaticModular&
    operator^=(value_type __x) noexcept
    { return *this = *this ^ __x; }

    constexpr StaticModular&
    operator&=(value_type __x) noexcept
    { return *this = *this & __x; }

    constexpr StaticModular&
    operator|=(value_type __x) noexcept
    { return *this = *this | __x; }

    friend inline std::istream&
    operator>>(std::istream& __is, StaticModular& __that)
    {
        decltype(auto) result = __is >> __that._M_value;
        __that._M_value = __that.residue(__that._M_value);
        return result;
    }

    friend inline std::ostream&
    operator<<(std::ostream& __os, const StaticModular& __that)
    { return __os << __that._M_value; }

private:

    value_type _M_value;
};
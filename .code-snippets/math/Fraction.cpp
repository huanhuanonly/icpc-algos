template<typename _Tp>
struct Fraction
{
    using value_type = _Tp;

    mutable value_type numerator = 0;
    mutable value_type denominator = 1;

    constexpr Fraction() noexcept = default;

    constexpr Fraction(value_type numerator, value_type denominator = 1) noexcept
        : numerator(numerator), denominator(denominator)
    { simplify(); }

    template<typename _Ty>
    constexpr Fraction(const Fraction<_Ty>& other) noexcept
        : numerator(static_cast<value_type>(other.numerator)), denominator(static_cast<value_type>(other.denominator))
    { }

    constexpr Fraction reciprocal() const noexcept
    { return Fraction(denominator, numerator); }

    static constexpr void unify(const Fraction& first, const Fraction& second) noexcept
    {
#if true
        first.numerator *= second.denominator;
        second.numerator *= first.denominator;

        first.denominator = second.denominator = first.denominator * second.denominator;
#else
        const auto lcm = std::lcm(first.denominator, second.denominator);

        first.numerator *= lcm;
        second.numerator *= lcm;

        first.denominator = second.denominator = lcm;
#endif
    }

    static constexpr void simplify(const Fraction& that) noexcept
    {
        const auto gcd = std::gcd(that.numerator, that.denominator);

        that.numerator /= gcd;
        that.denominator /= gcd;
    }

    constexpr Fraction& simplify() noexcept
    { simplify(*this); return *this; }

    constexpr const Fraction& simplify() const noexcept
    { simplify(*this); return *this; }

    /**
     * @returns Fraction(1) - *this.
     */
    constexpr Fraction operator~() const noexcept
    { return Fraction(denominator - numerator, denominator); }

    constexpr Fraction operator-() const noexcept
    { return Fraction(-numerator, denominator); }

    constexpr Fraction operator+() const noexcept
    { return *this; }

    constexpr std::strong_ordering operator<=>(const Fraction& other) const noexcept
    {
        unify(*this, other);
        auto result = numerator <=> other.numerator;

        simplify(), other.simplify();
        return result;
    }

    constexpr operator bool() const noexcept
    { return *this != 0; }

    constexpr bool operator!() const noexcept
    { return *this == 0; }

    constexpr Fraction& operator+=(const Fraction& other) noexcept
    {
        unify(*this, other);
        numerator += other.numerator;

        simplify(), other.simplify();
        return *this;
    }

    constexpr Fraction& operator-=(const Fraction& other) noexcept
    {
        unify(*this, other);
        numerator -= other.numerator;

        simplify(), other.simplify();
        return *this;
    }

    constexpr Fraction& operator*=(const Fraction& other) noexcept
    {
        numerator *= other.numerator;
        denominator *= other.denominator;

        simplify();
        return *this;
    }

    constexpr Fraction& operator/=(const Fraction& other) noexcept
    { return *this *= other.reciprocal(); }

    constexpr Fraction& operator++() noexcept
    {
        ++numerator;

        simplify();
        return *this;
    }

    constexpr Fraction& operator--() noexcept
    {
        --numerator;
        
        simplify();
        return *this;
    }

    constexpr Fraction operator++(int) noexcept
    { auto t = *this; ++*this; return t; }

    constexpr Fraction operator--(int) noexcept
    { auto t = *this; --*this; return t; }

    constexpr Fraction operator+(const Fraction& other) const noexcept
    { auto t = *this; return t += other; }

    constexpr Fraction operator-(const Fraction& other) const noexcept
    { auto t = *this; return t -= other; }

    constexpr Fraction operator*(const Fraction& other) const noexcept
    { auto t = *this; return t *= other; }

    constexpr Fraction operator/(const Fraction& other) const noexcept
    { auto t = *this; return t /= other; }

    template<typename _Ty>
    constexpr _Ty cast() const noexcept
    { return static_cast<_Ty>(numerator) / denominator; }

    template<typename _Ty>
    constexpr _Ty cast(_Ty mod) const noexcept
    { return _Ty(numerator) * binary_exponentiation(_Ty(denominator), mod - 2, mod) % mod; }
};

template<typename _Tp>
constexpr auto make_fraction(_Tp numerator, _Tp denominator = 1)
{ return Fraction<_Tp>(numerator, denominator); }
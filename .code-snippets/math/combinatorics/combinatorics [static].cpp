using comb_value_type = uint64_t;

constexpr auto
comb_nmod = static_cast<comb_value_type>(0);

constexpr auto
factorial_max_length = static_cast<std::size_t>(2e5 + 1);

template<comb_value_type _Mod = comb_nmod>
constexpr auto
factorial{ []() constexpr
{
    std::array<comb_value_type, factorial_max_length> a{1};

    for (std::size_t i = 1; i < a.size(); ++i)
    {
        if constexpr (_Mod != comb_nmod)
        {
            a[i] = a[i - 1] * i % _Mod;
        }
        else
        {
            a[i] = a[i - 1] * i;
        }
    }

    return a;
}() };

template<comb_value_type _Mod = comb_nmod>
[[nodiscard]] constexpr comb_value_type
C(comb_value_type n, comb_value_type k) noexcept
{
    assert(n < factorial_max_length);

    if (n < k)
    {
        return 0;
    }

    if constexpr (_Mod != comb_nmod)
    {
        return
            factorial<_Mod>[n] *
            binary_exponentiation(factorial<_Mod>[n - k] * factorial<_Mod>[k] % _Mod, _Mod - 2, _Mod) %
            _Mod;
    }
    else
    {
        return factorial<_Mod>[n] / (factorial<_Mod>[n - k] * factorial<_Mod>[k]);
    }
}

template<comb_value_type _Mod>
[[nodiscard]] constexpr comb_value_type
lucas(comb_value_type n, comb_value_type k) noexcept
{
    static_assert(_Mod != comb_nmod and _Mod > 1, "_Mod is required and must be a prime number.");

    if (k == 0)
    {
        return 1;
    }
    else
    {
        return C<_Mod>(n % _Mod, k % _Mod) * lucas<_Mod>(n / _Mod, k / _Mod) % _Mod;
    }
}

template<comb_value_type _Mod = comb_nmod>
[[nodiscard]] constexpr comb_value_type
P(comb_value_type n, comb_value_type k) noexcept
{
    if (n < k)
    {
        return 0;
    }

    if constexpr (_Mod != comb_nmod)
    {
        assert(n < factorial_max_length);
        return factorial<_Mod>[n] * binary_exponentiation(factorial<_Mod>[n - k], _Mod - 2, _Mod) % _Mod;
    }
    else
    {
        assert(n < factorial_max_length);
        return factorial<_Mod>[n] / factorial<_Mod>[n - k];
    }
}

template<comb_value_type _Mod = comb_nmod>
[[nodiscard]] constexpr comb_value_type
P(comb_value_type n) noexcept
{ return P<_Mod>(n, n); }

template<comb_value_type _Mod = comb_nmod>
[[nodiscard]] constexpr comb_value_type
A(comb_value_type n, comb_value_type k) noexcept
{ return P<_Mod>(n, k); }

template<comb_value_type _Mod = comb_nmod>
[[nodiscard]] constexpr comb_value_type
A(comb_value_type n) noexcept
{ return P<_Mod>(n, n); }

template<comb_value_type _MaxN, comb_value_type _MaxK, comb_value_type _Mod = comb_nmod>
[[nodiscard]] constexpr auto
comb_table() noexcept
{
    static_assert(_MaxN >= 0 and _MaxK >= 0);

    using table_type = std::array<std::array<comb_value_type, _MaxK + 1>, _MaxN + 1>;

    static constexpr table_type table{
        []() constexpr
        {
            table_type a{};

            for (comb_value_type i = 0; i <= _MaxN; ++i)
            {
                a[i][0] = 1;

                for (comb_value_type j = 1, e = std::min(i, _MaxK + 1); j < e; ++j)
                {
                    if constexpr (_Mod != comb_nmod)
                    {
                        a[i][j] = (a[i - 1][j] + a[i - 1][j - 1]) % _Mod;
                    }
                    else
                    {
                        a[i][j] = a[i - 1][j] + a[i - 1][j - 1];
                    }
                }

                if (i <= _MaxK)
                {
                    a[i][i] = 1;
                }
            }

            return a;
        }()
    };

    return [](comb_value_type n, comb_value_type k) constexpr -> comb_value_type
        {
            assert(n <= _MaxN and k <= _MaxK);
            return table[n][k];
        };
}
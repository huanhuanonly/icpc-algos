/**
 * The 4th Universal Cup. Extra Stage 4: Chongqing
 * 第十一届中国大学生程序设计竞赛 重庆站（CCPC 2025 Chongqing Site）
 *
 * => B. Abstract Portal
 *
 * -> https://qoj.ac/contest/3387/problem/15420
 *
 * Submissions ~> https://qoj.ac/submission/3444467 By huanhuanonly
 *
 * @b Matrix-exponentiation
 *
 * ----November 12, 2026 [20h:52m:52s]----
*/

#include <bits/stdc++.h>

using int8 = signed char;
using int16 = short;
using int32 = int;
using int64 = long long;

using uint8 = unsigned char;
using uint16 = unsigned short;
using uint32 = unsigned int;
using uint64 = unsigned long long;

#if defined(__SIZEOF_INT128__)
using int128 = __int128;
using uint128 = unsigned __int128;
#endif

using real32 = float;
using real64 = double;

#if defined(__SIZEOF_FLOAT80__)
using real80 = __float80;
#endif

#if defined(__SIZEOF_FLOAT128__)
using real128 = __float128;
#endif

inline namespace huanhuanonly {
    inline namespace math
{
template<
    typename _Tp, std::unsigned_integral _Up, typename _Mp,
    typename _MulOp = std::multiplies<_Tp>, typename _ModOp = std::modulus<void>>
requires
    requires(_MulOp __op, _Tp __x) { { __op(__x, __x) } -> std::convertible_to<_Tp>; } and
    requires(_ModOp __op, _Tp __lhs, _Mp __rhs) { { __op(__lhs, __rhs) } -> std::convertible_to<_Tp>; }
[[nodiscard]] constexpr _Tp
binary_exponentiation(_Tp __lhs, _Up __rhs, _Mp __mod, _MulOp __mul_op = {}, _ModOp __mod_op = {})
{
    if (__mod == 1)
    {
        return 0;
    }

    auto result = static_cast<_Tp>(1);

    for (__lhs = __mod_op(__lhs, __mod); __rhs; __lhs = __mod_op(__mul_op(__lhs, __lhs), __mod), __rhs >>= 1)
    {
        if (__rhs & 1)
        {
            result = __mod_op(__mul_op(result, __lhs), __mod);
        }
    }

    return result;
}

template<typename _Tp, std::unsigned_integral _Up, typename _MulOp = std::multiplies<_Tp>>
requires requires(_MulOp __op, _Tp __x) { { __op(__x, __x) } -> std::convertible_to<_Tp>; }
[[nodiscard]] constexpr _Tp
binary_exponentiation(_Tp __lhs, _Up __rhs, _MulOp __mul_op = {})
{
    auto result = static_cast<_Tp>(1);

    for (; __rhs; __lhs = __mul_op(__lhs, __lhs), __rhs >>= 1)
    {
        if (__rhs & 1)
        {
            result = __mul_op(result, __lhs);
        }
    }

    return result;
}
}} // namespace huanhuanonly::math

inline namespace huanhuanonly {
    inline namespace math
{
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
}} // namespace huanhuanonly::math

inline namespace huanhuanonly {
    inline namespace math
{
template<typename _Tp, int _Ln, int _Cn, typename _DefaultVal = _Tp>
class Matrix
{
    static_assert(_Ln > 0 and _Cn > 0);

public:

    using value_type = _Tp;
    using reference = _Tp&;
    using const_reference = const _Tp&;
    using size_type = int;

    using container_type = std::array<std::array<value_type, _Cn>, _Ln>;

    constexpr
    Matrix()
    {
        for (size_type i = 0; i < row(); ++i)
        {
            for (size_type j = 0; j < column(); ++j)
            {
                _M_m[i][j] = default_value();
            }
        }
    }

    constexpr
    Matrix(const value_type& __value)
    {
        for (size_type i = 0; i < row(); ++i)
        {
            for (size_type j = 0; j < column(); ++j)
            {
                if (i != j) [[likely]]
                {
                    _M_m[i][j] = default_value();
                }
                else [[unlikely]]
                {
                    _M_m[i][j] = __value;
                }
            }
        }
    }

    constexpr
    Matrix(std::initializer_list<std::initializer_list<_Tp>> __init)
    {
        if (static_cast<std::size_t>(row()) != __init.size())
        {
            throw std::invalid_argument("Matrix: invalid row count");
        }

        for (const auto& __row : __init)
        {
            if (static_cast<std::size_t>(column()) != __row.size())
            {
                throw std::invalid_argument("Matrix: invalid column count");
            }
        }

        auto lit = _M_m.begin();
        auto rit = __init.begin();

        for (; lit != _M_m.end(); ++lit, ++rit)
        {
            auto lit2 = lit->begin();
            auto rit2 = rit->begin();

            for (; lit2 != lit->end(); ++lit2, ++rit2)
            {
                *lit2 = *rit2;
            }
        }
    }

    template<typename _Tp2, typename _DefaultVal2>
    requires requires(_Tp& __dst, const _Tp2& __src)
    { __dst = __src; }
    constexpr
    Matrix(const Matrix<_Tp2, _Ln, _Cn, _DefaultVal2>& __other)
    {
        for (size_type i = 0; i < row(); ++i)
        {
            for (size_type j = 0; j < column(); ++j)
            {
                _M_m[i][j] = __other._M_m[i][j];
            }
        }
    }

    template<typename _Tp2, typename _DefaultVal2>
    requires requires(_Tp& __dst, const _Tp2& __src)
    { __dst = __src; }
    constexpr Matrix&
    operator=(const Matrix<_Tp2, _Ln, _Cn, _DefaultVal2>& __other)
    {
        for (size_type i = 0; i < row(); ++i)
        {
            for (size_type j = 0; j < column(); ++j)
            {
                _M_m[i][j] = __other._M_m[i][j];
            }
        }

        return *this;
    }

    template<typename _Tp2, typename _DefaultVal2>
    requires requires(_Tp& __dst, _Tp2&& __src)
    { __dst = std::move(__src); }
    constexpr
    Matrix(Matrix<_Tp2, _Ln, _Cn, _DefaultVal2>&& __other)
    {
        for (size_type i = 0; i < row(); ++i)
        {
            for (size_type j = 0; j < column(); ++j)
            {
                _M_m[i][j] = std::move(__other._M_m[i][j]);
            }
        }
    }

    template<typename _Tp2, typename _DefaultVal2>
    requires requires(_Tp& __dst, _Tp2&& __src)
    { __dst = std::move(__src); }
    constexpr Matrix&
    operator=(Matrix<_Tp2, _Ln, _Cn, _DefaultVal2>&& __other)
    {
        for (size_type i = 0; i < row(); ++i)
        {
            for (size_type j = 0; j < column(); ++j)
            {
                _M_m[i][j] = std::move(__other._M_m[i][j]);
            }
        }

        return *this;
    }

    static constexpr struct uninitialized_t { } uninitialized{};

    constexpr explicit
    Matrix(uninitialized_t)
    { }

    [[nodiscard]] static constexpr size_type
    row() noexcept
    { return _Ln; }

    [[nodiscard]] static constexpr size_type
    column() noexcept
    { return _Cn; }

    [[nodiscard]] static constexpr value_type
    default_value()
    { return static_cast<value_type>(_DefaultVal()); }

    [[nodiscard]] constexpr container_type&
    data() noexcept
    { return _M_m; }

    [[nodiscard]] constexpr const container_type&
    data() const noexcept
    { return _M_m; }

    [[nodiscard]] constexpr reference
    at(size_type __i, size_type __j)
    { return _M_m.at(__i).at(__j); }

    [[nodiscard]] constexpr const_reference
    at(size_type __i, size_type __j) const
    { return _M_m.at(__i).at(__j); }

    [[nodiscard]] constexpr decltype(auto)
    operator[](size_type __i) noexcept
    { return _M_m[__i]; }

    [[nodiscard]] constexpr decltype(auto)
    operator[](size_type __i) const noexcept
    { return _M_m[__i]; }

    constexpr void
    fill(const value_type& __value)
    {
        for (size_type i = 0; i < row(); ++i)
        {
            for (size_type j = 0; j < column(); ++j)
            {
                _M_m[i][j] = __value;
            }
        }
    }

    template<typename, size_type, size_type, typename>
    friend class Matrix;

    template<typename _UnaryOperation>
    requires requires(_UnaryOperation& __op, const _Tp& __x)
    { __op(__x); }
    [[nodiscard]] constexpr auto
    elementwise_transform(_UnaryOperation __unary_op = {}) const
    {
        using unary_operation_result_t =
            std::remove_cvref_t<std::invoke_result_t<_UnaryOperation&, const _Tp&>>;

        using default_value_t = std::conditional_t<
            std::is_same_v<unary_operation_result_t, _Tp>,
            _DefaultVal,
            unary_operation_result_t>;

        using result_type = Matrix<unary_operation_result_t, _Ln, _Cn, default_value_t>;
        result_type result(result_type::uninitialized);

        for (size_type i = 0; i < row(); ++i)
        {
            for (size_type j = 0; j < column(); ++j)
            {
                result._M_m[i][j] = __unary_op(_M_m[i][j]);
            }
        }

        return result;
    }

    template<typename _UnaryOperation>
    requires requires(_UnaryOperation& __op, _Tp& __x)
    { __x = __op(__x); }
    constexpr Matrix&
    elementwise_transform_inplace(_UnaryOperation __unary_op = {})
    {
        for (size_type i = 0; i < row(); ++i)
        {
            for (size_type j = 0; j < column(); ++j)
            {
                _M_m[i][j] = __unary_op(_M_m[i][j]);
            }
        }

        return *this;
    }

    template<typename _BinaryOperation, typename _Tp2, typename _DefaultVal2>
    requires requires(_BinaryOperation& __op, const _Tp& __lhs, const _Tp2& __rhs)
    { __op(__lhs, __rhs); }
    [[nodiscard]] constexpr auto
    elementwise_transform(
        const Matrix<_Tp2, _Ln, _Cn, _DefaultVal2>& __rhs,
        _BinaryOperation __binary_op = {}) const
    {
        using binary_operation_result_t =
            std::remove_cvref_t<std::invoke_result_t<
                _BinaryOperation&,
                const _Tp&,
                const _Tp2&>>;

        using default_value_t =
            std::conditional_t<
                std::is_same_v<binary_operation_result_t, _Tp>,
                _DefaultVal,
                std::conditional_t<
                    std::is_same_v<binary_operation_result_t, _Tp2>,
                    _DefaultVal2,
                    binary_operation_result_t>>;

        using result_type = Matrix<binary_operation_result_t, _Ln, _Cn, default_value_t>;
        result_type result(result_type::uninitialized);

        for (size_type i = 0; i < row(); ++i)
        {
            for (size_type j = 0; j < column(); ++j)
            {
                result._M_m[i][j] = __binary_op(_M_m[i][j], __rhs._M_m[i][j]);
            }
        }

        return result;
    }

    template<typename _BinaryOperation, typename _Tp2, typename _DefaultVal2>
    requires requires(_BinaryOperation& __op, _Tp& __lhs, const _Tp2& __rhs)
    { __lhs = __op(__lhs, __rhs); }
    constexpr Matrix&
    elementwise_transform_inplace(
        const Matrix<_Tp2, _Ln, _Cn, _DefaultVal2>& __rhs,
        _BinaryOperation __binary_op = {})
    {
        for (size_type i = 0; i < row(); ++i)
        {
            for (size_type j = 0; j < column(); ++j)
            {
                _M_m[i][j] = __binary_op(_M_m[i][j], __rhs._M_m[i][j]);
            }
        }

        return *this;
    }

    template<typename _Tp2, typename _DefaultVal2>
    [[nodiscard]] constexpr auto
    operator+(const Matrix<_Tp2, _Ln, _Cn, _DefaultVal2>& __rhs) const
    { return elementwise_transform(__rhs, std::plus{}); }

    template<typename _Tp2, typename _DefaultVal2>
    [[nodiscard]] constexpr auto
    operator-(const Matrix<_Tp2, _Ln, _Cn, _DefaultVal2>& __rhs) const
    { return elementwise_transform(__rhs, std::minus{}); }

    template<typename _Tp2, typename _DefaultVal2>
    constexpr Matrix&
    operator+=(const Matrix<_Tp2, _Ln, _Cn, _DefaultVal2>& __rhs)
    { return elementwise_transform_inplace(__rhs, std::plus{}); }

    template<typename _Tp2, typename _DefaultVal2>
    constexpr Matrix&
    operator-=(const Matrix<_Tp2, _Ln, _Cn, _DefaultVal2>& __rhs)
    { return elementwise_transform_inplace(__rhs, std::minus{}); }

    template<
        typename _BinaryOperation1, typename _BinaryOperation2,
        typename _Tp2, size_type _Cn2, typename _DefaultVal2>
    requires requires(_BinaryOperation2& __op, const _Tp& __lhs, const _Tp2& __rhs)
    { __op(__lhs, __rhs); }
    [[nodiscard]] constexpr auto
    semiring_multiply(
        const Matrix<_Tp2, _Cn, _Cn2, _DefaultVal2>& __rhs,
        _BinaryOperation1 __binary_op1 = {},
        _BinaryOperation2 __binary_op2 = {}) const
    {
        using binary_operation2_result_t =
            std::remove_cvref_t<std::invoke_result_t<
                _BinaryOperation2&,
                const _Tp&,
                const _Tp2&>>;

        static_assert(
            requires(
                _BinaryOperation1& __op1, _BinaryOperation2& __op2,
                binary_operation2_result_t& __result,
                const _Tp& __lhs, const _Tp2& __rhs)
            {
                __result = __op2(__lhs, __rhs);
                __result = __op1(__result, __op2(__lhs, __rhs));
            });

        using default_value_t = std::conditional_t<
            std::is_same_v<binary_operation2_result_t, _Tp>,
            _DefaultVal,
            std::conditional_t<
                std::is_same_v<binary_operation2_result_t, _Tp2>,
                _DefaultVal2,
                binary_operation2_result_t>>;

        using result_type = Matrix<binary_operation2_result_t, _Ln, _Cn2, default_value_t>;

        result_type result(result_type::uninitialized);

        for (size_type i = 0; i < row(); ++i)
        {
            for (size_type j = 0; j < __rhs.column(); ++j)
            {
                result._M_m[i][j] = __binary_op2(_M_m[i][0], __rhs._M_m[0][j]);
            }

            for (size_type k = 1; k < column(); ++k)
            {
                for (size_type j = 0; j < __rhs.column(); ++j)
                {
                    result._M_m[i][j] =
                        __binary_op1(result._M_m[i][j], __binary_op2(_M_m[i][k], __rhs._M_m[k][j]));
                }
            }
        }

        return result;
    }

    template<
        typename _BinaryOperation1, typename _BinaryOperation2,
        typename _Tp2, typename _DefaultVal2>
    constexpr Matrix&
    semiring_multiply_inplace(
        const Matrix<_Tp2, _Cn, _Cn, _DefaultVal2>& __rhs,
        _BinaryOperation1 __binary_op1 = {},
        _BinaryOperation2 __binary_op2 = {})
    {
        auto result = semiring_multiply(
            __rhs, std::move(__binary_op1), std::move(__binary_op2));

        return *this = std::move(result);
    }

    template<typename _Tp2, size_type _Cn2, typename _DefaultVal2>
    [[nodiscard]] constexpr auto
    operator*(const Matrix<_Tp2, _Cn, _Cn2, _DefaultVal2>& __rhs) const
    { return semiring_multiply(__rhs, std::plus{}, std::multiplies{}); }

    template<typename _Tp2, typename _DefaultVal2>
    constexpr Matrix&
    operator*=(const Matrix<_Tp2, _Cn, _Cn, _DefaultVal2>& __rhs)
    { return semiring_multiply_inplace(__rhs, std::plus{}, std::multiplies{}); }

private:

    container_type _M_m;
};
}} // namespace huanhuanonly::math

int main(void)
{
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);

#ifdef __huanhuanonly_localhost
    ::freopen("in", "r", stdin);
    ::freopen("out", "w", stdout);
#endif

    do
    {
        uint32 n, k;
        std::cin >> n >> k;

        std::vector<int> t(k, -1);

        for (int i = 1; i < k; ++i)
        {
            std::cin >> t[i];
        }

        constexpr uint64 mod = 1e9 + 7;
        using mint64 = StaticModular<uint64, mod>;

        Matrix<mint64, 1, 102> a;
        a[0][101] = k;

        for (int i = 0; i <= 100; ++i)
        {
            a[0][i] = (i ? a[0][i - 1] : mint64{}) + mint64(1);

            for (int j = 1; j < k; ++j)
            {
                if (t[j] == 0)
                {
                    ++a[0][i];
                }
                else if (i - t[j] >= 0)
                {
                    ++a[0][i];
                    a[0][i] += (i ? a[0][i - 1] : mint64{}) - (i - t[j] - 1 >= 0 ? a[0][i - t[j] - 1] : mint64{});
                }
            }
        }

        if (n - 1 <= 100)
        {
            std::cout << a[0][n - 1] << '\n';
            break;
        }

        Matrix<mint64, 102, 102> b;
        b[101][101] = 1;
        b[101][100] = 1;

        b[100][100] = k;

        for (int i = 0; i <= 100 - 1; ++i)
        {
            b[i + 1][i] = 1;
        }

        for (int i = 1; i < k; ++i)
        {
            --b[101 - t[i] - 1][100];
        }

        a *= binary_exponentiation(b, n - 101);
        std::cout << a[0][100] << '\n';
    } while (false);

    return 0;
}
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
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
    Matrix() noexcept
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
    Matrix(const value_type& __value) noexcept
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
    Matrix(std::initializer_list<std::initializer_list<_Tp>> __init) noexcept
    {
        assert(static_cast<std::size_t>(row()) == __init.size());

        auto lit = _M_m.begin();
        auto rit = __init.begin();

        for (; lit != _M_m.end(); ++lit, ++rit)
        {
            assert(static_cast<std::size_t>(column()) == rit->size());

            auto lit2 = lit->begin();
            auto rit2 = rit->begin();

            for (; lit2 != lit->end(); ++lit2, ++rit2)
            {
                *lit2 = *rit2;
            }
        }
    }

    template<std::convertible_to<_Tp> _Tp2, typename _DefaultVal2>
    constexpr
    Matrix(const Matrix<_Tp2, _Ln, _Cn, _DefaultVal2>& __other) noexcept
    {
        for (size_type i = 0; i < row(); ++i)
        {
            for (size_type j = 0; j < column(); ++j)
            {
                _M_m[i][j] = __other._M_m[i][j];
            }
        }
    }

    template<std::convertible_to<_Tp> _Tp2, typename _DefaultVal2>
    constexpr Matrix&
    operator=(const Matrix<_Tp2, _Ln, _Cn, _DefaultVal2>& __other) noexcept
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

    template<std::convertible_to<_Tp> _Tp2, typename _DefaultVal2>
    constexpr
    Matrix(Matrix<_Tp2, _Ln, _Cn, _DefaultVal2>&& __other) noexcept
    {
        for (size_type i = 0; i < row(); ++i)
        {
            for (size_type j = 0; j < column(); ++j)
            {
                _M_m[i][j] = std::move(__other._M_m[i][j]);
            }
        }
    }

    template<std::convertible_to<_Tp> _Tp2, typename _DefaultVal2>
    constexpr Matrix&
    operator=(Matrix<_Tp2, _Ln, _Cn, _DefaultVal2>&& __other) noexcept
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
    Matrix(uninitialized_t) noexcept
    { }

    [[nodiscard]] static constexpr size_type
    row() noexcept
    { return _Ln; }

    [[nodiscard]] static constexpr size_type
    column() noexcept
    { return _Cn; }

    [[nodiscard]] static constexpr value_type
    default_value() noexcept
    { return static_cast<value_type>(_DefaultVal{}); }

    [[nodiscard]] constexpr container_type&
    data() noexcept
    { return _M_m; }

    [[nodiscard]] constexpr const container_type&
    data() const noexcept
    { return _M_m; }

    [[nodiscard]] constexpr reference
    at(size_type __i, size_type __j) noexcept
    { return _M_m[__i][__j]; }

    [[nodiscard]] constexpr const_reference
    at(size_type __i, size_type __j) const noexcept
    { return _M_m[__i][__j]; }

    [[nodiscard]] constexpr decltype(auto)
    operator[](size_type __i) noexcept
    { return _M_m[__i]; }

    [[nodiscard]] constexpr decltype(auto)
    operator[](size_type __i) const noexcept
    { return _M_m[__i]; }

    constexpr void
    fill(const value_type& __value) noexcept
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
    requires requires(_UnaryOperation __op, _Tp __x) { __op(__x); }
    [[nodiscard]] constexpr auto
    elementwise_transform(_UnaryOperation __unary_op = {}) const noexcept
    {
        using unary_operation_result_t = std::remove_cvref_t<std::invoke_result_t<_UnaryOperation, _Tp>>;

        Matrix<unary_operation_result_t, _Ln, _Cn, _DefaultVal> result(uninitialized);

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
    requires requires(_UnaryOperation __op, _Tp __x) { { __op(__x) } -> std::convertible_to<_Tp>; }
    [[nodiscard]] constexpr Matrix&
    elementwise_transform_inplace(_UnaryOperation __unary_op = {}) noexcept
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
    requires requires(_BinaryOperation __op, _Tp __lhs, _Tp2 __rhs) { __op(__lhs, __rhs); }
    [[nodiscard]] constexpr auto
    elementwise_transform(const Matrix<_Tp2, _Ln, _Cn, _DefaultVal2>& __rhs, _BinaryOperation __binary_op = {}) const noexcept
    {
        using binary_operation_result_t = std::remove_cvref_t<std::invoke_result_t<_BinaryOperation, _Tp, _Tp2>>;
        using default_value_t =
            std::conditional_t<
                std::is_same_v<binary_operation_result_t, _Tp>,
                _DefaultVal,
                std::conditional_t<
                    std::is_same_v<binary_operation_result_t, _Tp2>,
                    _DefaultVal2,
                    binary_operation_result_t>>;

        Matrix<binary_operation_result_t, _Ln, _Cn, default_value_t> result(uninitialized);

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
    requires requires(_BinaryOperation __op, _Tp __lhs, _Tp2 __rhs) { { __op(__lhs, __rhs) } -> std::convertible_to<_Tp>; }
    constexpr Matrix&
    elementwise_transform_inplace(const Matrix<_Tp2, _Ln, _Cn, _DefaultVal2>& __rhs, _BinaryOperation __binary_op = {}) noexcept
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
    operator+(const Matrix<_Tp2, _Ln, _Cn, _DefaultVal2>& __rhs) const noexcept
    { return elementwise_transform(__rhs, std::plus{}); }

    template<typename _Tp2, typename _DefaultVal2>
    [[nodiscard]] constexpr auto
    operator-(const Matrix<_Tp2, _Ln, _Cn, _DefaultVal2>& __rhs) const noexcept
    { return elementwise_transform(__rhs, std::minus{}); }

    template<typename _Tp2, typename _DefaultVal2>
    constexpr Matrix&
    operator+=(const Matrix<_Tp2, _Ln, _Cn, _DefaultVal2>& __rhs) noexcept
    { return elementwise_transform_inplace(__rhs, std::plus{}); }

    template<typename _Tp2, typename _DefaultVal2>
    constexpr Matrix&
    operator-=(const Matrix<_Tp2, _Ln, _Cn, _DefaultVal2>& __rhs) noexcept
    { return elementwise_transform_inplace(__rhs, std::minus{}); }

    template<typename _BinaryOperation1, typename _BinaryOperation2, typename _Tp2, size_type _Cn2, typename _DefaultVal2>
    requires requires(_BinaryOperation2 __op2, _Tp __lhs, _Tp2 __rhs) { __op2(__lhs, __rhs); }
    [[nodiscard]] constexpr auto
    semiring_multiply(const Matrix<_Tp2, _Cn, _Cn2, _DefaultVal2>& __rhs, _BinaryOperation1 __binary_op1 = {}, _BinaryOperation2 __binary_op2 = {}) const noexcept
    {
        using binary_operation2_result_t = std::remove_cvref_t<std::invoke_result_t<_BinaryOperation2, _Tp, _Tp2>>;

        static_assert(requires(_BinaryOperation1 __op1, binary_operation2_result_t __x) { { __op1(__x, __x) } -> std::convertible_to<binary_operation2_result_t>; });

        Matrix<binary_operation2_result_t, _Ln, _Cn2, _DefaultVal> result{};

        for (size_type i = 0; i < row(); ++i)
        {
            for (size_type k = 0; k < column(); ++k)
            {
                for (size_type j = 0; j < __rhs.column(); ++j)
                {
                    result._M_m[i][j] = __binary_op1(result._M_m[i][j], __binary_op2(_M_m[i][k], __rhs._M_m[k][j]));
                }
            }
        }

        return result;
    }

    template<typename _BinaryOperation1, typename _BinaryOperation2, typename _Tp2, typename _DefaultVal2>
    requires requires(_BinaryOperation2 __op2, _Tp __lhs, _Tp2 __rhs) { { __op2(__lhs, __rhs) } -> std::convertible_to<_Tp>; }
    constexpr Matrix&
    semiring_multiply_inplace(const Matrix<_Tp2, _Cn, _Cn, _DefaultVal2>& __rhs, _BinaryOperation1 __binary_op1 = {}, _BinaryOperation2 __binary_op2 = {}) noexcept
    {
        static_assert(requires(_BinaryOperation1 __op1, _Tp __x) { { __op1(__x, __x) } -> std::convertible_to<_Tp>; });

        Matrix result{};

        for (size_type i = 0; i < row(); ++i)
        {
            for (size_type k = 0; k < column(); ++k)
            {
                for (size_type j = 0; j < __rhs.column(); ++j)
                {
                    result._M_m[i][j] = __binary_op1(result._M_m[i][j], __binary_op2(_M_m[i][k], __rhs._M_m[k][j]));
                }
            }
        }

        return *this = std::move(result);
    }

    template<typename _Tp2, size_type _Cn2, typename _DefaultVal2>
    [[nodiscard]] constexpr auto
    operator*(const Matrix<_Tp2, _Cn, _Cn2, _DefaultVal2>& __rhs) const noexcept
    { return semiring_multiply(__rhs, std::plus{}, std::multiplies{}); }

    template<typename _Tp2, typename _DefaultVal2>
    constexpr Matrix&
    operator*=(const Matrix<_Tp2, _Cn, _Cn, _DefaultVal2>& __rhs) noexcept
    { return semiring_multiply_inplace(__rhs, std::plus{}, std::multiplies{}); }

private:

    container_type _M_m;
};
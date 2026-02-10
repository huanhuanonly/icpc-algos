template<typename _Tp, uint32 _RowCount, uint32 _ColumnCount>
class Matrix
{
public:
    
    using value_type = _Tp;
    using pointer = _Tp*;
    using const_pointer = const _Tp*;
    using reference = _Tp&;
    using const_reference = const _Tp&;

    // Do nothing
    Matrix(std::nullptr_t) noexcept
    { }

    Matrix(_Tp __value = _Tp{}) noexcept : Matrix(nullptr)
    { fill(__value); }

    template<typename _Generator = _Tp (*)(uint32, uint32)>
    Matrix(_Generator __er) : Matrix(nullptr)
    { fill(__er); }

    Matrix(std::initializer_list<std::initializer_list<value_type>> __init) : Matrix(nullptr)
    {
        for_each([this, &__init](uint32 i, uint32 j) -> void
        {
            _M_matrix[i][j] = (
                i < __init.size() and j < (__init.begin() + i)->size()
                ? *((__init.begin() + i)->begin() + j)
                : value_type(0));
        });
    }

    void fill(value_type __value) noexcept
    {
        for_each([this, &__value](uint32 i, uint32 j) -> void
        {
            _M_matrix[i][j] = __value;
        });
    }

    template<typename _Generator = value_type (*)(uint32, uint32)>
    void fill(_Generator __er)
    {
        for_each([this, &__er](uint32 i, uint32 j) -> void
        {
            _M_matrix[i][j] = __er(i, j);
        });
    }

    Matrix operator+(const Matrix& __it) const noexcept
    {
        Matrix res(nullptr);

        for_each([this, &__it, &res](uint32 i, uint32 j) -> void
        {
            res[i][j] = _M_matrix[i][j] + __it._M_matrix[i][j];
        });

        return res;
    }

    Matrix& operator+=(const Matrix& __it) noexcept
    {
        for_each([this, &__it](uint32 i, uint32 j) -> void
        {
            _M_matrix[i][j] += __it._M_matrix[i][j];
        });
    }

    Matrix operator-(const Matrix& __it) const noexcept
    {
        Matrix res(nullptr);

        for_each([this, &__it, &res](uint32 i, uint32 j) -> void
        {
            res[i][j] = _M_matrix[i][j] - __it._M_matrix[i][j];
        });

        return res;
    }

    Matrix& operator-=(const Matrix& __it) noexcept
    {
        for_each([this, &__it](uint32 i, uint32 j) -> void
        {
            _M_matrix[i][j] -= __it._M_matrix[i][j];
        });
    }

    template<uint32 _ItsColumnCount>
    Matrix operator*(const Matrix<_Tp, _ColumnCount, _ItsColumnCount>& __it) const
    {
        Matrix res;

        for (uint32 i = 0; i < _RowCount; ++i)
        {
            for (uint32 j = 0; j < _ItsColumnCount; ++j)
            {
                for (uint32 k = 0; k < _ColumnCount; ++k)
                {
                    res._M_matrix[i][j] += _M_matrix[i][k] * __it._M_matrix[k][j];
                }
            }
        }

        return res;
    }


    template<uint32 _ItsColumnCount>
    Matrix& operator*=(const Matrix<_Tp, _ColumnCount, _ItsColumnCount>& __it)
    {
        swap(*this * __it);
        return *this;
    }

    template<typename _ValueType>
    std::enable_if_t<std::is_integral_v<_ValueType>, Matrix&> operator^=(_ValueType __pow)
    {
        Matrix res([](uint32 i, uint32 j) -> _Tp { return static_cast<_Tp>(i == j); });

        for (; __pow; __pow >>= 1, *this *= *this)
        {
            if (__pow & 1)
            {
                res *= *this;
            }
        }

        swap(std::move(res));
        return *this;
    }

    constexpr reference at(uint32 __rowNumber, uint32 __colNumber) noexcept
    { return _M_matrix[__rowNumber][__colNumber]; }

    constexpr value_type at(uint32 __rowNumber, uint32 __colNumber) const noexcept
    { return _M_matrix[__rowNumber][__colNumber]; }

    void swap(Matrix& __it) noexcept
    {
        for_each([this, &__it](uint32 i, uint32 j) -> void
        {
            _M_matrix[i][j] ^= __it._M_matrix[i][j];
            __it._M_matrix[i][j] ^= _M_matrix[i][j];
            _M_matrix[i][j] ^= __it._M_matrix[i][j];
        });
    }

    void swap(Matrix&& __it) noexcept
    {
        for_each([this, &__it](uint32 i, uint32 j) -> void
        {
            _M_matrix[i][j] = __it._M_matrix[i][j];
        });
    }

    constexpr uint32 row_count() const noexcept
    { return _RowCount; }

    constexpr uint32 column_count() const noexcept
    { return _ColumnCount; }

    template<typename _Function = void (*)(uint32, uint32)>
    constexpr void for_each(_Function __func)
    {
        for (uint32 i = 0; i < _RowCount; ++i)
        {
            for (uint32 j = 0; j < _ColumnCount; ++j)
            {
                __func(i, j);
            }
        }
    }

    template<typename _ItsTp, uint32 _ItsRowCount, uint32 _ItsColumnCount>
    friend class Matrix;

protected:

    value_type _M_matrix[_RowCount][_ColumnCount];
};
template<
    typename _Tp, std::unsigned_integral _Up, typename _Mp,
    typename _PlusOp = std::plus<_Tp>, typename _ModOp = std::modulus<void>>
requires
    requires(_PlusOp __op, _Tp __x) { { __op(__x, __x) } -> std::convertible_to<_Tp>; } and
    requires(_ModOp __op, _Tp __lhs, _Mp __rhs) { { __op(__lhs, __rhs) } -> std::convertible_to<_Tp>; }
[[nodiscard]] constexpr _Tp
binary_multiplication(_Tp __lhs, _Up __rhs, _Mp __mod, _PlusOp __plus_op = {}, _ModOp __mod_op = {})
{
    _Tp result{};

    if constexpr (requires(_Up __x, _Mp __m) { __x %= __m; })
    {
        __rhs %= __mod;
    }

    for (__lhs = __mod_op(__lhs, __mod); __rhs; __lhs = __mod_op(__plus_op(__lhs, __lhs), __mod), __rhs >>= 1)
    {
        if (__rhs & 1)
        {
            result = __mod_op(__plus_op(result, __lhs), __mod);
        }
    }

    return result;
}

template<typename _Tp, std::unsigned_integral _Up, typename _PlusOp = std::plus<_Tp>>
requires requires(_PlusOp __op, _Tp __x) { { __op(__x, __x) } -> std::convertible_to<_Tp>; }
[[nodiscard]] constexpr _Tp
binary_multiplication(_Tp __lhs, _Up __rhs, _PlusOp __plus_op = {})
{
    _Tp result{};

    for (; __rhs; __lhs = __plus_op(__lhs, __lhs), __rhs >>= 1)
    {
        if (__rhs & 1)
        {
            result = __plus_op(result, __lhs);
        }
    }

    return result;
}
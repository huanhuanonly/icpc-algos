template<typename _Tp>
[[nodiscard]] constexpr _Tp
euler_phi(_Tp __n) noexcept
{
    assert(__n > 0);

    _Tp result = __n;

    for (_Tp i = 2; i <= __n / i; ++i)
    {
        if (__n % i == 0)
        {
            for (; __n % i == 0; __n /= i);
            result -= result / i;
        }
    }

    if (__n > 1)
    {
        result -= result / __n;
    }

    return result;
}
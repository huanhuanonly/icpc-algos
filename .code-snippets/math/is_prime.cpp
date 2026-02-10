template<typename _Tp>
[[nodiscard]] constexpr bool is_prime(_Tp __n)
{
    if (__n <= 3)
    {
        return __n > 1;
    }
    else if (__n % 6 != 1 and __n % 6 != 5)
    {
        return false;
    }

    for (_Tp i = 5; i * i <= __n; i += 6)
    {
        if (__n % i == 0 or __n % (i + 2) == 0)
        {
            return false;
        }
    }

    return true;
}
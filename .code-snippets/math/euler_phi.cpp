template<typename _Tp>
[[nodiscard]] _Tp euler_phi(_Tp __n)
{
    _Tp result = __n;
    for (_Tp i = 2; i * i <= __n; ++i)
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
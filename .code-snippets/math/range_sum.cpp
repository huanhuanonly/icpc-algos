template <typename _Tp>
[[nodiscard]] constexpr _Tp
range_sum(_Tp __s, _Tp __e, _Tp __step = 1) noexcept
{
    static_assert(not std::is_floating_point_v<_Tp>);

    if (not __step or (__step > 0 ? __s > __e : __s < __e))
    {
        return 0;
    }

    _Tp n = (__e - __s) / __step + 1;

    __e = __s + (n - 1) * __step;

    if (n & 1)
    {
        return n * (__s + (n / 2) * __step);
    }
    else
    {
        return (n / 2) * (__s + __e)
    }
}
template<typename _Tp>
[[nodiscard]] constexpr _Tp exgcd(_Tp __a, _Tp& __x, _Tp __b, _Tp& __y)
{
    if (__b)
    {
        _Tp nx, ny;
        const _Tp gcd = exgcd(__b, nx, __a % __b, ny);
        
        __x = ny;
        __y = nx - __a / __b * ny;
        
        return gcd;
    }
    else
    {
        __x = 1, __y = 0;
        return __a;
    }
}
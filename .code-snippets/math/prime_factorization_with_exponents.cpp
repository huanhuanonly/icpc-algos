template<typename _Tp>
[[nodiscard]] constexpr std::vector<std::pair<_Tp, int>>
prime_factorization_with_exponents(_Tp __n)
{
    std::vector<std::pair<_Tp, int>> result;

    for (_Tp i = 2; i <= __n / i; ++i)
    {
        if (__n % i == 0)
        {
            int cnt = 0;
            for (; __n % i == 0; __n /= i, ++cnt);

            result.emplace_back(i, cnt);
        }
    }

    if (__n > 1)
    {
        result.emplace_back(__n, 1);
    }

    return result;
}
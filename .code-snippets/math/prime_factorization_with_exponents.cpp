template<typename _Tp>
[[nodiscard]] std::map<_Tp, int>
prime_factorization_with_exponents(_Tp __n)
{
    std::map<_Tp, int> res;

    for (_Tp i = 2; i * i <= __n; ++i)
    {
        if (__n % i == 0)
        {
            for (auto& c = res[i]; __n % i == 0; __n /= i, ++c);
        }

    }

    if (__n != 1)
    {
        ++res[__n];
    }

    return res;
}
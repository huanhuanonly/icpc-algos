template<typename _Tp>
[[nodiscard]] constexpr std::vector<_Tp>
prime_factorization(_Tp __n, bool __unique = false)
{
    std::vector<_Tp> res;

    if (__unique)
    {
        for (_Tp i = 2; i <= __n / i; ++i)
        {
            if (__n % i == 0)
            {
                res.push_back(i);
                for (__n /= i; __n % i == 0; __n /= i);
            }

        }
    }
    else
    {
        for (_Tp i = 2; i <= __n / i; ++i)
        {
            for (; __n % i == 0; __n /= i)
            {
                res.push_back(i);
            }
        }
    }

    if (__n > 1)
    {
        res.push_back(__n);
    }

    return res;
}
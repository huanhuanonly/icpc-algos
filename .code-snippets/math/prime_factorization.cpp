template<typename _Tp>
[[nodiscard]] std::vector<_Tp> prime_factorization(_Tp __n)
{
    std::vector<_Tp> res;

    for (_Tp i = 2; i * i <= __n; ++i)
    {
        for (; __n % i == 0; __n /= i)
        {
            res.push_back(i);
        }
    }

    if (__n != 1)
    {
        res.push_back(__n);
    }

    return res;
}
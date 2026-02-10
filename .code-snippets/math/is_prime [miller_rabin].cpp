template<typename _Tp>
[[nodiscard]] constexpr bool is_prime(_Tp __n)
{
    constexpr std::array<_Tp, 7> primes{2, 3, 5, 7, 11, 13, 17};

    if (__n <= 1)
    {
        return false;
    }

    _Tp t = __n - 1, k = 0;

    for (; (t & 1) == 0; t >>= 1, ++k);

    for (_Tp i = 0; i < primes.size(); ++i)
    {
        if (__n == primes[i])
        {
            return true;
        }

        _Tp x = binary_exponentiation(primes[i], t, __n);
        _Tp next = x;

        for (_Tp j = 1; j <= k; ++j)
        {
            next = (x * x) % __n;

            if (next == 1 and x != 1 and x != __n - 1)
            {
                return false;
            }

            x = next;
        }

        if (x != 1)
        {
            return false;
        }
    }

    return true;
}
template <std::integral _Tp>
[[nodiscard]] constexpr bool
is_prime(_Tp __n)
{
    static_assert(sizeof(_Tp) <= sizeof(uint64_t));

    constexpr std::array<uint64_t, 7> primes{
        2, 325, 9375, 28178, 450775, 9780504, 1795265022
    };

    if (__n <= 1)
    {
        return false;
    }
    else if (not (__n & 1))
    {
        return __n == 2;
    }

    const auto n = static_cast<uint64_t>(__n);

    uint64_t t = n - 1, k = 0;
    for (; not (t & 1); t >>= 1, ++k);

    for (const auto& p : primes)
    {
        const uint64_t a = p % n;

        if (a == 0)
        {
            continue;
        }

        uint64_t x = static_cast<uint64_t>(binary_exponentiation(
            static_cast<__uint128_t>(a), static_cast<__uint128_t>(t), static_cast<__uint128_t>(n)));

        if (x == 1 || x == n - 1)
        {
            continue;
        }

        bool ok = false;

        for (uint64_t j = 1; j < k; ++j)
        {
            x = static_cast<uint64_t>(static_cast<__uint128_t>(x) * x % n);

            if (x == n - 1)
            {
                ok = true;
                break;
            }
        }

        if (!ok)
        {
            return false;
        }
    }

    return true;
}
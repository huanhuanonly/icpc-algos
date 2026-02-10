template<typename _Container = std::vector<int>>
[[nodiscard]] constexpr _Container primes_in_range(std::size_t __n)
{
    _Container primes;

    std::vector<bool> vis(__n + 1);

    vis[0] = vis[1] = true;

    for (std::size_t i = 2; i <= __n; ++i)
    {
        if (not vis[i])
        {
            primes.push_back(static_cast<_Container::value_type>(i));
        }

        for (const auto p : primes | std::views::take_while([__n, i](auto p) -> bool { return i * p <= __n; }))
        {
            vis[i * p] = true;

            if (i % p == 0)
            {
                break;
            }
        }
    }

    return primes;
}
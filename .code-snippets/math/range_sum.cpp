template <typename _Integer>
[[nodiscard]] constexpr _Integer
range_sum(_Integer a, _Integer b, _Integer c = 1)
{
    if (a == b or c == 0)
    {
        return 0;
    }

    _Integer x{};

    if (c > 0)
    {
        --b;

        if (a > b)
        {
            return 0;
        }

        x = (b - a) / c;
        b = a + x * c;
    }
    else
    {
        ++b;

        if (a < b)
        {
            return 0;
        }

        x = -(b - a) / -c;
        b = a + x * c;
    }

    const _Integer n = x + 1;
    _Integer s = (a + b) * (n / 2);

    if (n & 1)
    {
        s += a + c * (n / 2);
    }

    return s;
}
class Manacher
{
public:

    using size_type = int;

    Manacher() = default;

    template<
        std::random_access_iterator _Iter,
        std::sized_sentinel_for<_Iter> _Sent,
        typename _Comp = std::ranges::equal_to,
        typename _Proj = std::identity>
    requires
        std::indirect_equivalence_relation<_Comp, std::projected<_Iter, _Proj>>
    Manacher(_Iter __first, _Sent __last, _Comp __comp = {}, _Proj __proj = {})
    { build(__first, __last, __comp, __proj); }

    template<
        std::ranges::sized_range _Range,
        typename _Comp = std::ranges::equal_to,
        typename _Proj = std::identity>
    Manacher(_Range&& __r, _Comp __comp = {}, _Proj __proj = {})
    { build(std::forward<_Range>(__r), __comp, __proj); }


    template<
        std::random_access_iterator _Iter,
        std::sized_sentinel_for<_Iter> _Sent,
        typename _Comp = std::ranges::equal_to,
        typename _Proj = std::identity>
    requires
        std::indirect_equivalence_relation<_Comp, std::projected<_Iter, _Proj>>
    void
    build(_Iter __first, _Sent __last, _Comp __comp = {}, _Proj __proj = {})
    {
        const size_type n = static_cast<size_type>(std::ranges::distance(__first, __last));

        odd.resize(n);
        even.resize(n);

        for (size_type i = 0, l = 0, r = -1; i < n; ++i)
        {
            odd[i] = r < i ? 1 : std::min(odd[l + r - i], r - i + 1);

            for (; odd[i] <= i and i + odd[i] < n and __comp(__proj(*(__first + (i - odd[i]))), __proj(*(__first + (i + odd[i])))); ++odd[i]);

            if (r < i + (odd[i] - 1))
            {
                l = i - (odd[i] - 1);
                r = i + (odd[i] - 1);
            }
        }

        for (size_type i = 0, l = 0, r = -1; i < n; ++i)
        {
            even[i] = r < i ? 0 : std::min(even[l + r - i - 1], r - i);

            for (; even[i] <= i and i + 1 + even[i] < n and __comp(__proj(*(__first + (i - even[i]))), __proj(*(__first + (i + 1 + even[i])))); ++even[i]);

            if (r < i + even[i])
            {
                l = i - (even[i] - 1);
                r = i + even[i];
            }
        }
    }

    template<
        std::ranges::sized_range _Range,
        typename _Comp = std::ranges::equal_to,
        typename _Proj = std::identity>
    void
    build(_Range&& __r, _Comp __comp = {}, _Proj __proj = {})
    { build(std::ranges::begin(__r), std::ranges::end(__r), __comp, __proj); }


    [[nodiscard]] size_type
    odd_radius(size_type __center) const noexcept(noexcept(odd[__center]))
    { return odd[__center]; }

    [[nodiscard]] size_type
    even_radius(size_type __center) const noexcept(noexcept(even[__center]))
    { return even[__center]; }

    [[nodiscard]] size_type
    odd_length(size_type __center) const noexcept(noexcept(odd_radius(__center)))
    { return odd_radius(__center) * 2 - 1; }

    [[nodiscard]] size_type
    even_length(size_type __center) const noexcept(noexcept(even_radius(__center)))
    { return even_radius(__center) * 2; }


    [[nodiscard]] bool
    is_palindrome(size_type __l, size_type __r) const noexcept(noexcept(odd_radius(size_type{})))
    {
        if (__r < __l)
        {
            std::swap(__l, __r);
        }

        if (const size_type len = __r - __l + 1; len <= 1)
        {
            return true;
        }
        else if (len & 1)
        {
            return (__l + __r) / 2 + odd_radius((__l + __r) / 2) - 1 >= __r;
        }
        else
        {
            return (__l + __r) / 2 + even_radius((__l + __r) / 2) >= __r;
        }
    }

    /**
     * @returns [start, length]
     */
    [[nodiscard]] std::pair<size_type, size_type>
    longest_odd_palindrome() const noexcept
    {
        if (empty())
        {
            return {};
        }

        const auto oit = std::ranges::max_element(odd);
        const size_type olen = *oit * 2 - 1;

        return {static_cast<size_type>(oit - odd.begin() - (*oit - 1)), olen};
    }

    /**
     * @returns [start, length]
     */
    [[nodiscard]] std::pair<size_type, size_type>
    longest_even_palindrome() const noexcept
    {
        if (empty())
        {
            return {};
        }

        const auto eit = std::ranges::max_element(even);
        const size_type elen = *eit * 2;

        return {static_cast<size_type>(eit - even.begin() - (*eit - 1)), elen};
    }

    /**
     * @returns [start, length]
     */
    [[nodiscard]] std::pair<size_type, size_type>
    longest_palindrome() const noexcept
    { return std::ranges::max(longest_odd_palindrome(), longest_even_palindrome(), {}, &std::pair<size_type, size_type>::second); }

    template<typename _Result = size_type>
    [[nodiscard]] _Result
    count() const noexcept
    { return std::reduce(odd.begin(), odd.end(), std::reduce(even.begin(), even.end(), _Result{})); }

    [[nodiscard]] bool
    empty() const noexcept(noexcept(odd.empty()))
    { return odd.empty(); }

    [[nodiscard]] size_type
    size() const noexcept(noexcept(odd.size()))
    { return static_cast<size_type>(odd.size()); }

    [[nodiscard]] void
    clear() noexcept(noexcept(odd.clear()))
    { odd.clear(), even.clear(); }

private:

    std::vector<size_type> odd;
    std::vector<size_type> even;
};
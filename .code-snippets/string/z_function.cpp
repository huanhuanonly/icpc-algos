template<
    std::random_access_iterator _Iter,
    std::sized_sentinel_for<_Iter> _Sent,
    std::random_access_iterator _Out,
    typename _Comp = std::ranges::equal_to,
    typename _Proj = std::identity>
constexpr void z_function(_Iter __first, _Sent __last, _Out __result, _Comp __comp = {}, _Proj __proj = {})
{
    if (__first == __last)
    {
        return;
    }

    auto l = __first, r = __first;

    *__result = std::ranges::distance(__first, __last);

    auto oit = __result + 1;

    for (auto it = __first + 1; it != __last; ++it, ++oit)
    {
        if (it <= r)
        {
            *oit = std::min(__result[it - l], static_cast<std::remove_reference_t<std::iter_reference_t<_Out>>>(r - it + 1));
        }
        else
        {
            *oit = 0;
        }

        for (; it + *oit != __last and
            __comp(std::invoke(__proj, __first[*oit]), std::invoke(__proj, it[*oit])); ++*oit);

        if (const auto cr = it + *oit - 1; r < cr)
        {
            l = it;
            r = cr;
        }
    }
}

template<
    std::ranges::random_access_range _Range,
    std::random_access_iterator _Out,
    typename _Comp = std::ranges::equal_to,
    typename _Proj = std::identity>
constexpr void z_function(_Range&& __r, _Out __out, _Comp __comp = {}, _Proj __proj = {})
{ z_function(std::ranges::begin(__r), std::ranges::end(__r), std::move(__out), std::move(__comp), std::move(__proj)); }
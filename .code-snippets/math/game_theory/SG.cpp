template<std::integral _Tp = int>
class SG
{
public:

    using value_type = _Tp;

    SG() noexcept = default;

    template<std::ranges::input_range _Range>
    SG(_Range&& __r)
        : _M_set(__r | std::ranges::to<std::vector>())
    { assert(std::ranges::all_of(_M_set, [](const auto& i) -> bool { return i > 0; })); }

    template<std::input_iterator _Iter, std::sentinel_for<_Iter> _Sent>
    SG(_Iter __first, _Sent __last)
        : SG(std::ranges::subrange(std::move(__first), std::move(__last)))
    { }

    value_type
    operator()(value_type __x)
    {
        assert(__x > 0);

        if (not __x)
        {
            return value_type{};
        }

        if (const auto it = _M_sg.find(__x); it != _M_sg.end())
        {
            return it->second;
        }

        std::vector<bool> vis(_M_set.size() + 1);

        for (const auto& i : _M_set)
        {
            if (__x >= i)
            {
                vis[(*this)(__x - i)] = true;
            }
        }

        return _M_sg[__x] = std::ranges::find(vis, false) - vis.begin();
    }

private:

    std::vector<value_type> _M_set;
    std::unordered_map<value_type, value_type> _M_sg;
};

template<std::input_iterator _Iter, std::sentinel_for<_Iter> _Sent>
SG(_Iter, _Sent) -> SG<std::iter_value_t<_Iter>>;

template<std::ranges::input_range _Range>
SG(_Range&&) -> SG<std::ranges::range_value_t<_Range>>;